BUILD_DIR := build
SRC_DIR := src
TESTS_DIR := tests

build: $(patsubst $(TESTS_DIR)/%.c, $(BUILD_DIR)/%, $(wildcard $(TESTS_DIR)/*.c))

$(BUILD_DIR)/%: $(TESTS_DIR)/%.c primitive_testing/primitive_testing_enviroment.c $(SRC_DIR)/*.c ./headers/* ./primitive_testing/*
	mkdir -p $(BUILD_DIR)
	gcc -std=gnu99 $< primitive_testing/primitive_testing_enviroment.c $(SRC_DIR)/*.c -I./headers -I./primitive_testing -o $@

check: build
	run-parts --report $(BUILD_DIR)

clean:
	rm $(BUILD_DIR) -R
