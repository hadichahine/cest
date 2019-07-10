#include "cutest.h"
#include <stdlib.h>

typedef struct {
    CUTest *test;
    CUTest *secondTest;
} CUTestSuite;

CUTestSuite *CUTestSuite_create(char *name){
    CUTestSuite *testSuite = (CUTestSuite*)malloc(sizeof(CUTestSuite));
    testSuite->test = NULL;
    testSuite->secondTest = NULL;
    return testSuite;
}

void CUTestSuite_addTest(CUTestSuite *testSuite,CUTest *test){
    if(!testSuite->test)
        testSuite->test = test;
    else testSuite->secondTest = test;
}

void CUTestSuite_execute(CUTestSuite *testSuite){
    CUTest_execute(testSuite->test);
    if(testSuite->secondTest != NULL)
        CUTest_execute(testSuite->secondTest);
}

int CUTestSuite_didPass(CUTestSuite *testSuite){
    int didPass = 1;
    didPass = didPass && CUTest_didTestPass(testSuite->test);
    if(testSuite->secondTest)
        didPass = didPass && CUTest_didTestPass(testSuite->secondTest);
    return didPass;
}