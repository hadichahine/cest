tests := test_single_test_execution \
		 test_test_suite_execution \
		 test_linked_list

build:
	mkdir build

define template
build/$(1): build tests/$(1).c primitive_testing/primitive_testing_enviroment.c src/*.c ./headers/* ./primitive_testing/*
	gcc tests/$(1).c primitive_testing/primitive_testing_enviroment.c src/*.c -I./headers -I./primitive_testing -o build/$(1)
endef

#Initialize each test binary's build rule.
$(foreach test,$(tests), \
	$(eval $(call template,$(test))) \
)

#Construct build files names
$(foreach test_name,$(tests), \
	$(eval buildexecutioncommand += build/$(test_name)) \
)

test: $(patsubst %,build/%,$(tests))
	run-parts --report build