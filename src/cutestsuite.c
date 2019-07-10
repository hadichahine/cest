#include "cutest.h"
#include <stdlib.h>

typedef struct {
    CUTest *test;
} CUTestSuite;

CUTestSuite *CUTestSuite_create(char *name){
    return (CUTestSuite*)malloc(sizeof(CUTestSuite));
}

void CUTestSuite_addTest(CUTestSuite *testSuite,CUTest *test){
    testSuite->test = test;
}

void CUTestSuite_execute(CUTestSuite *testSuite){
    CUTest_execute(testSuite->test);
}

int CUTestSuite_didPass(CUTestSuite *testSuite){
    return CUTest_didTestPass(testSuite->test);
}