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

jmp_buf flow_control_state_before_running_test_function;

CUTest *currentlyExecutingTest;

void handleSignalProblem(int signum){
	Assert_assertTrue(currentlyExecutingTest->assert, 0);
	longjmp(flow_control_state_before_running_test_function, 1);
}

void CUTest_execute(CUTest *test){
	currentlyExecutingTest = test;
	struct sigaction sa;
    sa.sa_handler = handleSignalProblem;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);
	if(!setjmp(flow_control_state_before_running_test_function))
		test->testFunction(test->assert);
}

int CUTest_didTestPass(CUTest *test){
	return Assert_result(test->assert);
}
