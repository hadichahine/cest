BUILD_DIR := build
SRC_DIR := src
TESTS_DIR := tests
OBJ_DIR := $(BUILD_DIR)/obj

all: $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c primitive_testing/primitive_testing_enviroment.c $(SRC_DIR)/*.c ./headers/* ./primitive_testing/*
	mkdir -p $(OBJ_DIR)
	$(CC) -std=gnu99 -fPIC -c $< -I./headers -o $@

buildtests: $(patsubst $(TESTS_DIR)/%.c, $(BUILD_DIR)/tests/%, $(wildcard $(TESTS_DIR)/*.c))

$(BUILD_DIR)/tests/%: $(TESTS_DIR)/%.c primitive_testing/primitive_testing_enviroment.c $(OBJ_DIR)/*.o ./headers/* ./primitive_testing/*
	mkdir -p $(BUILD_DIR)/tests
	$(CC) -std=gnu99 $< primitive_testing/primitive_testing_enviroment.c $(OBJ_DIR)/*.o -I./headers -I./primitive_testing -o $@

check: buildtests
	run-parts --report $(BUILD_DIR)/tests

clean:
	rm $(BUILD_DIR) -R
