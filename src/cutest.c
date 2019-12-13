#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <setjmp.h>
#include "e4c.h"
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
	e4c_context_begin(E4C_TRUE);
	e4c_context_end();
	return test;
}

char *CUTest_testName(CUTest *test){
	return test->name;
}

void CUTest_execute(CUTest *test){
	e4c_using_context(E4C_TRUE){
		try{
			test->testFunction(test->assert);
		}catch(BadPointerException){
			Assert_assertTrue(test->assert, 0);
		}catch(ArithmeticException){
			Assert_assertTrue(test->assert, 0);
		}
	}
}

int CUTest_didTestPass(CUTest *test){
	return Assert_result(test->assert);
}
