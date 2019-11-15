BUILD_DIR := build
SRC_DIR := src
TESTS_DIR := tests
OBJ_DIR := $(BUILD_DIR)/obj
DIST_DIR := $(BUILD_DIR)/dist
INSTALL_DIR := /usr/
LIBNAME := libcest

all: $(DIST_DIR)/lib/$(LIBNAME).so $(DIST_DIR)/include/cest

check: $(patsubst $(TESTS_DIR)/%.c, $(BUILD_DIR)/tests/%, $(wildcard $(TESTS_DIR)/*.c))
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
	git archive --format=tar.gz master -o $(BUILD_DIR)/cest-$(call nextmajor)-$(NAME).tar.gz

release-minor: check
	printf $(call nextminor) > version
	git archive --format=tar.gz master -o $(BUILD_DIR)/cest-$(call nextminor)-$(NAME).tar.gz

release-patch: check
	printf $(call nextpatch) > version
	git archive --format=tar.gz master -o $(BUILD_DIR)/cest-$(call nextpatch)-$(NAME).tar.gz

$(DIST_DIR)/lib/$(LIBNAME).so: $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
	mkdir -p $(DIST_DIR)/lib
	$(CC) -s -shared $(OBJ_DIR)/*.o -o $(DIST_DIR)/lib/$(LIBNAME).so

$(DIST_DIR)/include/cest: headers/*
	mkdir -p $(DIST_DIR)/include/cest
	cp headers/* $(DIST_DIR)/include/cest -R

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c primitive_testing/primitive_testing_enviroment.c $(SRC_DIR)/*.c ./headers/* ./primitive_testing/*
	mkdir -p $(OBJ_DIR)
	$(CC) -std=gnu99 -fPIC -c $< -I./headers -o $@

$(BUILD_DIR)/tests/%: $(TESTS_DIR)/%.c $(DIST_DIR)/lib/$(LIBNAME).so $(DIST_DIR)/include/cest primitive_testing/*
	mkdir -p $(BUILD_DIR)/tests
	$(CC) -std=gnu99 $< primitive_testing/primitive_testing_enviroment.c -lcest -L$(DIST_DIR)/lib -I$(DIST_DIR)/include/cest -I./primitive_testing -o $@

