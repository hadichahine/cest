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
}CUTest;

CUTest *CUTest_create(char *name,void (*testFunction)(Assert *assert)){
	CUTest *test = (CUTest*)malloc(sizeof(CUTest));
	test->testFunction = testFunction;
	test->assert = (Assert*)malloc(sizeof(Assert));
}

void CUTest_execute(CUTest *test){
	test->testFunction(test->assert);	
}
int didTestPass(CUTest *test){
	return test->assert->result;
}
