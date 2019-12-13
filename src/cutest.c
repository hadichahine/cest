#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <setjmp.h>
#include "cutest_assert.h"

typedef struct CUTest {
	void (*testFunction)(Assert *assert);
	Assert *assert;
	char* name;
}CUTest;

CUTest *CUTest_create(char *name,void (*testFunction)(Assert *assert)){
	CUTest *test = (CUTest*)malloc(sizeof(CUTest));
	test->name = name;
	test->testFunction = testFunction;
	test->assert = Assert_create();
	return test;
}

char *CUTest_testName(CUTest *test){
	return test->name;
}

jmp_buf flow_control_state_before_running_function;

void handleSignalProblem(int signum){
	longjmp(flow_control_state_before_running_function, 1);
}

typedef struct __quarantine_execution_request
{
	void (*quarantined_function)(struct __quarantine_execution_request *request);
	void (*crash_handler)(struct __quarantine_execution_request *request);
} quarantine_execution_request;

void quarantine_execution(quarantine_execution_request *request){
	struct sigaction sa;
    sa.sa_handler = handleSignalProblem;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);
	if(!setjmp(flow_control_state_before_running_function))
		request->quarantined_function(request);
	else request->crash_handler(request);
}

typedef struct test_function_execution {
	void (*quarantined_function)(struct test_function_execution request);
	void (*crash_handler)(struct test_function_execution request);
	CUTest *correspondingCUTest;
}test_function_execution_request;

void execute_test_function(test_function_execution_request *request){
	request->correspondingCUTest->testFunction(request->correspondingCUTest->assert);
}

void handle_test_function_failure(test_function_execution_request *request){
	Assert_assertTrue(request->correspondingCUTest->assert, 0);
}

void CUTest_execute(CUTest *test){
	test_function_execution_request request = {
		execute_test_function,
		handle_test_function_failure,
		test
	};
	quarantine_execution(&request);
}

int CUTest_didTestPass(CUTest *test){
	return Assert_result(test->assert);
}
