NAME := libmalloc.so
TEST := test

CC = gcc

HFLAGS := -MMD -MP
CFLAGS := -Wall -Wextra -Wpedantic -Werror

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

export DEBUG := 1

ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -g 
endif

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(LIBFT) -shared $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -fPIC $(CFLAGS) $(HFLAGS) $(INCLUDE) -o $@ 

$(OBJ_DIR):
	mkdir -p $@

test: all $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(INCLUDE) -Wl,-rpath,. test/main.c -L. -lmalloc

clean:
	make -C $(LIB_DIR)/libft clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	make -C $(LIB_DIR)/libft fclean
	$(RM) $(NAME)

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

.PHONY: all test clean fclean re run files print format

-include $(OBJECTS:.o=.d)
