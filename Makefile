build: build/test_single_test_execution build/test_test_suite_execution build/test_linked_list

check: build
	run-parts --report build

build/%: tests/%.c primitive_testing/primitive_testing_enviroment.c src/*.c ./headers/* ./primitive_testing/*
	mkdir -p build
	gcc -std=gnu99 $< primitive_testing/primitive_testing_enviroment.c src/*.c -I./headers -I./primitive_testing -o $@


clean:
	rm build -R
