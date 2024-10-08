NAME = libft_malloc.so
HOST = libft_malloc_$(HOSTTYPE).so

CC = gcc

HFLAGS = -MMD -MP
CFLAGS = -Wall -Wextra -Werror -fvisibility=hidden

OS := $(shell uname -s)

ifeq ($(OS), Linux)
	LDFLAGS += -Wl,--exclude-libs,ALL
endif

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

LIBFT = $(LIB_DIR)/libft/libft.a

export MAKEFLAGS = "-j 8"

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

include make/sources.mk
include make/headers.mk
include make/include.mk

INCLUDE += -I lib/libft/include

OBJECTS = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.c=.o))

DEBUG ?= 0
VERBOSE ?= 0

ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g
endif

ifeq ($(VERBOSE), 1)
	CFLAGS += -DVERBOSE
endif

all: $(NAME)

$(NAME): $(HOST)
	ln -fs $^ $@
	
$(HOST): $(OBJECTS) $(LIBFT)
	$(CC) $(LIBFT) -shared $(LDFLAGS) $^ -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC $(HFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

F ?= random

test: all
	$(CC) $(CFLAGS) $(LIBFT) $(INCLUDE) -Wl,-rpath,. test/$(F).c -L. -lft_malloc -o $(F)

clean:
	make -C $(LIB_DIR)/libft clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make -C $(LIB_DIR)/libft fclean
	$(RM) $(NAME) $(HOST)

re:
	make fclean
	make all

$(LIBFT):
	make -C $(LIB_DIR)/libft

files:
	./make/make_sources.sh

print: 
	@echo "---SOURCES: $(SOURCES)" | xargs -n1
	@echo "---HEADERS: $(HEADERS)" | xargs -n1
	@echo "---OBJECTS: $(OBJECTS)" | xargs -n1

format: files
	clang-format -i $(SOURCES) $(HEADERS)

scan: clean
	scan-build make

N ?= 0

faults:
	@/usr/bin/time -v ./test$N.out 2>&1 | sed -n '13p' | cut -d ' ' -f6-
	@/usr/bin/time -v ./run.sh ./test$N.out 2>&1 | sed -n '13p' | cut -d ' ' -f6-

.PHONY: all test clean fclean re run files print format scan

-include $(OBJECTS:.o=.d)
