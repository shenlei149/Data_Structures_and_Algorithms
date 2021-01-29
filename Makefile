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
$(INFRA_CODE_DIR)/infra_color.h\
$(INFRA_CODE_DIR)/infra_assert.h\
$(INFRA_CODE_DIR)/infra_memory.h\
$(INFRA_CODE_DIR)/infra_arena.h
INFRA_OBJ=$(OBJ_DIR)/infra.a

INFRA_MEMORY_TEST_FILE=$(TEST_DIR)/$(INFRA_PREFIX)/infra_memory_test.c
INFRA_MEMORY_TEST=$(BIN_DIR)/infra_memory_test
INFRA_ARENA_TEST_FILE=$(TEST_DIR)/$(INFRA_PREFIX)/infra_arena_test.c
INFRA_ARENA_TEST=$(BIN_DIR)/infra_arena_test

ELEMENTARY_PREFIX=elementary
ELEMENTARY_CODE_DIR=$(SRC_DIR)/$(ELEMENTARY_PREFIX)
ELEMENTARY_SRC_FILE=\
$(ELEMENTARY_CODE_DIR)/elementary_singlylinkedlist.c
ELEMENTARY_HEADER_FILE=\
$(ELEMENTARY_CODE_DIR)/elementary_singlylinkedlist.h
ELEMENTARY_OBJ=$(OBJ_DIR)/elementary.a

ELEMENTARY_SSL_TEST_FILE=$(TEST_DIR)/$(ELEMENTARY_PREFIX)/elementary_singlylinkedlist_test.c
ELEMENTARY_SSL_TEST=$(BIN_DIR)/elementary_singlylinkedlist_test

MATH_DIR=math
MATH_SRC_FILE=$(SRC_DIR)/$(MATH_DIR)/math_arith.c
MATH_HEADER_FILE=$(SRC_DIR)/$(MATH_DIR)/math_arith.h
MATH_OBJ=$(OBJ_DIR)/math.o

MATH_ARITH_TEST_FILE=$(TEST_DIR)/$(MATH_DIR)/math_arith_test.c
MATH_ARITH_TEST=$(BIN_DIR)/math_arith_test

all: allobj alltest runtest

allobj: makeobjdir $(INFRA_OBJ) $(ELEMENTARY_OBJ) $(MATH_OBJ)

alltest: makebindir $(MATH_ARITH_TEST) $(INFRA_MEMORY_TEST)\
$(INFRA_ARENA_TEST) $(ELEMENTARY_SSL_TEST)

runtest: run_math_test run_infra_test run_elementary_test

$(INFRA_OBJ): $(INFRA_SRC_FILE) $(INFRA_HEADER_FILE)
	$(CC) $(CFLAGS) -c $(INFRA_SRC_FILE)
	ar cr $(INFRA_OBJ) $(INFRA_PREFIX)*
	mv $(INFRA_PREFIX)* $(OBJ_DIR)

$(INFRA_MEMORY_TEST): $(INFRA_OBJ) $(INFRA_MEMORY_TEST_FILE)
	$(CC) $(CFLAGS) -o $(INFRA_MEMORY_TEST) $(INFRA_MEMORY_TEST_FILE) $(INFRA_OBJ) $(BUILD_TEST_ARG)

$(INFRA_ARENA_TEST): $(INFRA_OBJ) $(INFRA_ARENA_TEST_FILE)
	$(CC) $(CFLAGS) -o $(INFRA_ARENA_TEST) $(INFRA_ARENA_TEST_FILE) $(INFRA_OBJ) $(BUILD_TEST_ARG)

$(ELEMENTARY_OBJ): $(INFRA_OBJ) $(ELEMENTARY_SRC_FILE) $(ELEMENTARY_HEADER_FILE)
	$(CC) $(CFLAGS) -c $(ELEMENTARY_SRC_FILE)
	ld -r $(OBJ_DIR)/$(INFRA_PREFIX)* $(ELEMENTARY_PREFIX)* -o $(ELEMENTARY_OBJ)
	mv $(ELEMENTARY_PREFIX)* $(OBJ_DIR)

$(ELEMENTARY_SSL_TEST): $(ELEMENTARY_OBJ) $(ELEMENTARY_SSL_TEST_FILE)
	$(CC) $(CFLAGS) -o $(ELEMENTARY_SSL_TEST) $(ELEMENTARY_SSL_TEST_FILE) $(ELEMENTARY_OBJ) $(BUILD_TEST_ARG)

$(MATH_OBJ): $(MATH_SRC_FILE) $(MATH_HEADER_FILE)
	$(CC) $(CFLAGS) -c -o $(MATH_OBJ) $(MATH_SRC_FILE)

$(MATH_ARITH_TEST): $(MATH_OBJ) $(MATH_ARITH_TEST_FILE)
	$(CC) $(CFLAGS) -o $(MATH_ARITH_TEST) $(MATH_ARITH_TEST_FILE) $(MATH_OBJ) $(BUILD_TEST_ARG)

run_math_test:
	$(RUN_TEST_ENV) ./$(MATH_ARITH_TEST)

run_infra_test:
	$(RUN_TEST_ENV) ./$(INFRA_MEMORY_TEST)
	$(RUN_TEST_ENV) ./$(INFRA_ARENA_TEST)

run_elementary_test:
	$(RUN_TEST_ENV) ./$(ELEMENTARY_SSL_TEST)

makeobjdir:
	mkdir -p $(OBJ_DIR)

makebindir:
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR) 
	rm -rf $(OBJ_DIR)
