TEST_SUITE = graphic
TEST_NAME = adjacent_multiple_list_graphic

CC = gcc 
CFLAGS = -Wall -g -I. -L$(LIB)

LIB = lib
INCLUDE = include
BIN = bin

SRC = src
TEST_DIR = $(TEST_SUITE)
TEST_PATH = $(TEST_DIR)/$(TEST_NAME)
TEST_SRC = test

SOURCES = $(foreach dir,$(TEST_DIR),$(wildcard $(SRC)/$(dir)/*.c))
OBJS = $(patsubst %.c,%.o,$(SOURCES))

TEST_SOURCES = $(foreach dir,$(TEST_DIR),$(wildcard $(TEST_SRC)/$(dir)/*.c))
TEST_SOURCES := $(subst $(TEST_SRC)/list/list_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/stack/stack_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/queue/queue_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/string/string_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/array/sparse_matrix_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/array/generalized_list_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/tree/binary_tree_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/tree/tree_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/graphic/graphic_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/graphic/directed_graphic_test.c,,$(TEST_SOURCES)) 
TEST_SOURCES := $(subst $(TEST_SRC)/graphic/undirected_graphic_test.c,,$(TEST_SOURCES)) 

TEST_OBJS = $(patsubst %.c,%.o,$(TEST_SOURCES))
TEST_EXES = $(patsubst %.c,%.exe,$(TEST_SOURCES))

DELETE_TARGETS = $(foreach dir,$(TEST_DIR),$(BIN)\$(dir)\*)

%.o: %.c
	mkdir -p ./bin/$(TEST_PATH)
	rm -rf ./bin/$(TEST_PATH)
	$(CC) $(CFLAGS) -c $< -o $(patsubst $(TEST_SRC)/%, $(BIN)/%, $(patsubst $(SRC)/%, $(BIN)/%, $@))

%.exe: %.o
	$(CC) $(CFLAGS) $(patsubst $(TEST_SRC)/%,$(BIN)/%,$<) $(subst _test,,$(patsubst $(TEST_SRC)/%, $(BIN)/%, $<)) -lcunit -o  $(patsubst $(TEST_SRC)/%, $(BIN)/%, $@)

all: $(OBJS) $(TEST_OBJS) $(TEST_EXES) 
	$(BIN)/$(TEST_PATH)_test.exe
	
clean:
	rm -f $(DELETE_TARGETS)
