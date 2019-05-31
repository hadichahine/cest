test_single_test_execution: test_single_test_execution.c primitive_testing_enviroment.c src/*.c ./headers/*
	gcc test_single_test_execution.c primitive_testing_enviroment.c src/*.c -I./headers -o test_single_test_execution && ./test_single_test_execution
test: test_single_test_execution