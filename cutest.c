#include <stdlib.h>
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
}

char *testName(CUTest *test){
	return test->name;
}

void CUTest_execute(CUTest *test){
	test->testFunction(test->assert);
}

int didTestPass(CUTest *test){
	return Assert_result(test->assert);
}
