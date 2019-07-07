tests := test_single_test_execution \
		 test_test_suite_execution

define template
build/$(1): tests/$(1).c primitive_testing_enviroment.c src/*.c ./headers/*
	gcc tests/$(1).c primitive_testing_enviroment.c src/*.c -I./headers -o build/$(1)
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