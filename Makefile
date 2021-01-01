CC=gcc
CFLAGS=-g -Wall -Wextra -Werror -Werror=vla -pedantic -std=c11
BUILD_TEST_ARG=-Ilib/criterion/include -lcriterion -Llib/criterion/lib
RUN_TEST_ENV=LD_LIBRARY_PATH=lib/criterion/lib

OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src
TEST_DIR=test

MATH_DIR=math
MATH_SRC_FILE=$(SRC_DIR)/$(MATH_DIR)/math_arith.c
MATH_HEADER_FILE=$(SRC_DIR)/$(MATH_DIR)/math_arith.h
MATH_OBJ=$(OBJ_DIR)/math.o

MATH_ARITH_TEST_FILE=$(TEST_DIR)/$(MATH_DIR)/math_arith_test.c
MATH_ARITH_TEST=$(BIN_DIR)/math_arith_test

all: allobj alltest runtest

allobj: makeobjdir $(MATH_OBJ)

alltest: makebindir $(MATH_ARITH_TEST)

runtest: run_math_test

$(MATH_OBJ): $(MATH_SRC_FILE) $(MATH_HEADER_FILE)
	$(CC) $(CFLAGS) -c -o $(MATH_OBJ) $(MATH_SRC_FILE)

$(MATH_ARITH_TEST): $(MATH_OBJ) $(MATH_ARITH_TEST_FILE)
	$(CC) $(CFLAGS) -o $(MATH_ARITH_TEST) $(MATH_OBJ) $(MATH_ARITH_TEST_FILE) $(BUILD_TEST_ARG)

run_math_test:
	$(RUN_TEST_ENV) ./$(MATH_ARITH_TEST)

makeobjdir:
	mkdir -p $(OBJ_DIR)

makebindir:
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR) 
	rm -rf $(OBJ_DIR)
