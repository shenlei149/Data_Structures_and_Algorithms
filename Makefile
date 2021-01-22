CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -Werror=vla -pedantic -std=c11
BUILD_TEST_ARG=-Ilib/criterion/include -lcriterion -Llib/criterion/lib
RUN_TEST_ENV=LD_LIBRARY_PATH=lib/criterion/lib

OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src
TEST_DIR=test

INFRA_PREFIX=infra
INFRA_CODE_DIR=$(SRC_DIR)/$(INFRA_PREFIX)
INFRA_SRC_FILE=\
$(INFRA_CODE_DIR)/infra_assert.c\
$(INFRA_CODE_DIR)/infra_memory.c\
$(INFRA_CODE_DIR)/infra_arena.c
INFRA_HEADER_FILE=\
$(INFRA_CODE_DIR)/infra_assert.h\
$(INFRA_CODE_DIR)/infra_memory.h\
$(INFRA_CODE_DIR)/infra_arena.h
INFRA_OBJ=$(OBJ_DIR)/infra.a

INFRA_MEMORY_TEST_FILE=$(TEST_DIR)/$(INFRA_PREFIX)/infra_memory_test.c
INFRA_MEMORY_TEST=$(BIN_DIR)/infra_memory_test
INFRA_ARENA_TEST_FILE=$(TEST_DIR)/$(INFRA_PREFIX)/infra_arena_test.c
INFRA_ARENA_TEST=$(BIN_DIR)/infra_arena_test

MATH_DIR=math
MATH_SRC_FILE=$(SRC_DIR)/$(MATH_DIR)/math_arith.c
MATH_HEADER_FILE=$(SRC_DIR)/$(MATH_DIR)/math_arith.h
MATH_OBJ=$(OBJ_DIR)/math.o

MATH_ARITH_TEST_FILE=$(TEST_DIR)/$(MATH_DIR)/math_arith_test.c
MATH_ARITH_TEST=$(BIN_DIR)/math_arith_test

all: allobj alltest runtest

allobj: makeobjdir $(INFRA_OBJ) $(MATH_OBJ)

alltest: makebindir $(MATH_ARITH_TEST) $(INFRA_MEMORY_TEST)\
$(INFRA_ARENA_TEST)

runtest: run_math_test run_infra_test

$(INFRA_OBJ): $(INFRA_SRC_FILE) $(INFRA_HEADER_FILE)
	$(CC) $(CFLAGS) -c $(INFRA_SRC_FILE)
	ar cr $(INFRA_OBJ) $(INFRA_PREFIX)*
	rm $(INFRA_PREFIX)*

$(INFRA_MEMORY_TEST): $(INFRA_OBJ) $(INFRA_MEMORY_TEST_FILE)
	$(CC) $(CFLAGS) -o $(INFRA_MEMORY_TEST) $(INFRA_MEMORY_TEST_FILE) $(INFRA_OBJ) $(BUILD_TEST_ARG)

$(INFRA_ARENA_TEST): $(INFRA_OBJ) $(INFRA_ARENA_TEST_FILE)
	$(CC) $(CFLAGS) -o $(INFRA_ARENA_TEST) $(INFRA_ARENA_TEST_FILE) $(INFRA_OBJ) $(BUILD_TEST_ARG)

$(MATH_OBJ): $(MATH_SRC_FILE) $(MATH_HEADER_FILE)
	$(CC) $(CFLAGS) -c -o $(MATH_OBJ) $(MATH_SRC_FILE)

$(MATH_ARITH_TEST): $(MATH_OBJ) $(MATH_ARITH_TEST_FILE)
	$(CC) $(CFLAGS) -o $(MATH_ARITH_TEST) $(MATH_ARITH_TEST_FILE) $(MATH_OBJ) $(BUILD_TEST_ARG)

run_math_test:
	$(RUN_TEST_ENV) ./$(MATH_ARITH_TEST)

run_infra_test:
	$(RUN_TEST_ENV) ./$(INFRA_MEMORY_TEST)
	$(RUN_TEST_ENV) ./$(INFRA_ARENA_TEST)

makeobjdir:
	mkdir -p $(OBJ_DIR)

makebindir:
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR) 
	rm -rf $(OBJ_DIR)
