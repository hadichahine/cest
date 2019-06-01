build/test_single_test_execution: tests/test_single_test_execution.c primitive_testing_enviroment.c src/*.c ./headers/*
	gcc tests/test_single_test_execution.c primitive_testing_enviroment.c src/*.c -I./headers -o build/test_single_test_execution
build/test_test_suite_execution: tests/test_test_suite_execution.c primitive_testing_enviroment.c src/*.c ./headers/*
	gcc tests/test_test_suite_execution.c primitive_testing_enviroment.c src/*.c -I./headers -o build/test_test_suite_execution
test: build/test_single_test_execution build/test_test_suite_execution
	build/test_single_test_execution && build/test_test_suite_execution