NAME := libmalloc.so
TEST := test

CC = gcc

CFLAGS := -fPIC -Wall -Werror -Wextra -MMD -MP -Wpedantic

SRC_DIR = src
OBJ_DIR = obj

export MAKEFLAGS = "-j 8"

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

include make/sources.mk
include make/headers.mk
include make/include.mk

OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(SOURCES:.c=.o))

DEBUG := 0

ifeq ($(DEBUG), 1)
	CFLAGS += -O0 -D DEBUG -g3 -fsanitize=address,undefined
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -shared $^ -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	mkdir -p $(@D)
	$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@ 

$(OBJ_DIR):
	mkdir -p $@

test:
	$(CC) $(CFLAGS) test/main.c -I inc -L. -lmalloc

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all

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
