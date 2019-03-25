#include <stdlib.h>

typedef struct Assert {
	int result;
}Assert;

void assertTrue(Assert *assert,int boolean){
	assert->result = boolean;
}

typedef struct CUTest {
	void (*testFunction)(Assert *assert);
	Assert *assert;
	char* name;
}CUTest;

CUTest *CUTest_create(char *name,void (*testFunction)(Assert *assert)){
	CUTest *test = (CUTest*)malloc(sizeof(CUTest));
	test->testFunction = testFunction;
	test->name = name;
	test->assert = (Assert*)malloc(sizeof(Assert));
}

char *testName(CUTest *test){
	return test->name;
}

void CUTest_execute(CUTest *test){
	test->testFunction(test->assert);	
}
int didTestPass(CUTest *test){
	return test->assert->result;
}
