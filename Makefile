build/test_single_test_execution: test_single_test_execution.c primitive_testing_enviroment.c src/*.c ./headers/*
	gcc test_single_test_execution.c primitive_testing_enviroment.c src/*.c -I./headers -o build/test_single_test_execution
test: build/test_single_test_execution
	build/test_single_test_execution