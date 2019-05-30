test:
	gcc test_single_test_execution.c primitive_testing_enviroment.c src/*.c -I./headers -o Test && ./Test