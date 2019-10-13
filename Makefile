check: $(patsubst tests/%.c, build/%, $(wildcard tests/*.c))
	run-parts --report build

build/%: tests/%.c primitive_testing/primitive_testing_enviroment.c src/*.c ./headers/* ./primitive_testing/*
	mkdir -p build/tests
	gcc -std=gnu99 $< primitive_testing/primitive_testing_enviroment.c src/*.c -I./headers -I./primitive_testing -o $@

clean:
	rm build -R
