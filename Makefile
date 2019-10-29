BUILD_DIR := build
SRC_DIR := src
TESTS_DIR := tests
OBJ_DIR := $(BUILD_DIR)/obj
DIST_DIR := $(BUILD_DIR)/dist
INSTALL_DIR := /usr/
LIBNAME := libcest

all: $(DIST_DIR)/lib/$(LIBNAME).so

check: $(patsubst $(TESTS_DIR)/%.c, $(BUILD_DIR)/tests/%, $(wildcard $(TESTS_DIR)/*.c))
	LD_LIBRARY_PATH=$(DIST_DIR)/lib run-parts --report $(BUILD_DIR)/tests	

install: all
	cp $(DIST_DIR)/* $(INSTALL_DIR) -R

clean:
	rm $(BUILD_DIR) -R

$(DIST_DIR)/lib/$(LIBNAME).so: $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
	mkdir -p $(DIST_DIR)/lib
	$(CC) -s -shared $(OBJ_DIR)/*.o -o $(DIST_DIR)/lib/$(LIBNAME).so

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c primitive_testing/primitive_testing_enviroment.c $(SRC_DIR)/*.c ./headers/* ./primitive_testing/*
	mkdir -p $(OBJ_DIR)
	$(CC) -std=gnu99 -fPIC -c $< -I./headers -o $@

$(BUILD_DIR)/tests/%: $(TESTS_DIR)/%.c primitive_testing/primitive_testing_enviroment.c all ./headers/* ./primitive_testing/*
	mkdir -p $(BUILD_DIR)/tests
	$(CC) -std=gnu99 $< primitive_testing/primitive_testing_enviroment.c -lcest -L$(DIST_DIR)/lib -I./headers -I./primitive_testing -o $@

