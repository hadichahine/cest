BUILD_DIR := build
STAT_DEPEND := $(BUILD_DIR)/stat_depends
SRC_DIR := src
TESTS_DIR := tests
OBJ_DIR := $(BUILD_DIR)/obj
DIST_DIR := $(BUILD_DIR)/dist
INSTALL_DIR := /usr/
LIBNAME := libcest

all: static_dependencies $(DIST_DIR)/lib/$(LIBNAME).so $(DIST_DIR)/include/cest

static_dependencies: exceptions4c

exceptions4c: $(STAT_DEPEND)/libexceptions4c.a

$(STAT_DEPEND)/libexceptions4c.a: $(OBJ_DIR)/e4c.o
	mkdir -p $(STAT_DEPEND)
	ar rcs $(STAT_DEPEND)/libexceptions4c.a $(OBJ_DIR)/e4c.o

$(OBJ_DIR)/e4c.o: static_dependencies/exceptions4c/e4c.c static_dependencies/exceptions4c/e4c.h
	mkdir -p $(OBJ_DIR)
	$(CC) -std=gnu99 -fPIC -c static_dependencies/exceptions4c/e4c.c -o $(OBJ_DIR)/e4c.o

TEST := test

test-debug: all $(BUILD_DIR)/tests/$(TEST)
	LD_LIBRARY_PATH=$(DIST_DIR)/lib gdb $(BUILD_DIR)/tests/$(TEST)

check: all $(patsubst $(TESTS_DIR)/%.c, $(BUILD_DIR)/tests/%, $(wildcard $(TESTS_DIR)/*.c))
	LD_LIBRARY_PATH=$(DIST_DIR)/lib run-parts --report $(BUILD_DIR)/tests	

install: all
	cp $(DIST_DIR)/* $(INSTALL_DIR) -R

clean:
	rm $(BUILD_DIR) -R

INCREMENT := 1
NAME := unspecified
CURRENT_VERSION := $(shell cat version)

add=$(shell echo $$(( $(1) + $(2) )))
major=$(shell printf $(CURRENT_VERSION) | cut - --delimiter="." -f1)
minor=$(shell printf $(CURRENT_VERSION) | cut - --delimiter="." -f2)
patch=$(shell printf $(CURRENT_VERSION) | cut - --delimiter="." -f3)
nextmajor=$(call add, $(call major), $(INCREMENT)).$(call minor).$(call patch)
nextminor=$(call major).$(call add, $(call minor), $(INCREMENT)).$(call patch)
nextpatch=$(call major).$(call minor).$(call add, $(call patch), $(INCREMENT))

release-major: check
	printf $(call nextmajor) > version

release-minor: check
	printf $(call nextminor) > version

release-patch: check
	printf $(call nextpatch) > version

archive: check
	git archive --format=tar.gz master -o $(BUILD_DIR)/cest-$(CURRENT_VERSION)-$(NAME).tar.gz

$(DIST_DIR)/lib/$(LIBNAME).so: $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
	mkdir -p $(DIST_DIR)/lib
	$(CC) -s -shared $(OBJ_DIR)/*.o -L$(STAT_DEPEND) -lexceptions4c -o $(DIST_DIR)/lib/$(LIBNAME).so

$(DIST_DIR)/include/cest: headers/*
	mkdir -p $(DIST_DIR)/include/cest
	cp headers/* $(DIST_DIR)/include/cest -R

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c primitive_testing/primitive_testing_enviroment.c $(SRC_DIR)/*.c ./headers/* ./primitive_testing/*
	mkdir -p $(OBJ_DIR)
	$(CC) -ggdb -std=gnu99 -fPIC -c $< -I./headers -I./static_dependencies/exceptions4c -o $@

$(BUILD_DIR)/tests/%: $(TESTS_DIR)/%.c $(DIST_DIR)/lib/$(LIBNAME).so $(DIST_DIR)/include/cest primitive_testing/*
	mkdir -p $(BUILD_DIR)/tests
	$(CC) -ggdb -std=gnu99 $< primitive_testing/primitive_testing_enviroment.c -lcest -L$(DIST_DIR)/lib -I$(DIST_DIR)/include/cest -I./primitive_testing -I./static_dependencies -o $@

