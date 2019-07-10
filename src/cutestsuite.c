#include "cutest.h"
#include "linkedlist.h"
#include <stdlib.h>

typedef struct {
    CUTest *test;
    CUTest *secondTest;
    CUTest *thirdTest;
    LinkedList *testsList;
} CUTestSuite;

CUTestSuite *CUTestSuite_create(char *name){
    CUTestSuite *testSuite = (CUTestSuite*)malloc(sizeof(CUTestSuite));
    testSuite->test = NULL;
    testSuite->secondTest = NULL;
    testSuite->thirdTest = NULL;
    testSuite->testsList = createLinkedList();
    return testSuite;
}

void CUTestSuite_addTest(CUTestSuite *testSuite,CUTest *test){
    addItemToLinkedList(testSuite->testsList,test);
    if(!testSuite->test)
        testSuite->test = test;
    else if(!testSuite->secondTest)
            testSuite->secondTest = test;
        else testSuite->thirdTest = test;
}

void CUTestSuite_execute(CUTestSuite *testSuite){
    while(!reachedEnd(testSuite->testsList))
        CUTest_execute(next(testSuite->testsList));
    reset(testSuite->testsList);
}

int CUTestSuite_didPass(CUTestSuite *testSuite){
    int didPass = 1;
    while(!reachedEnd(testSuite->testsList))
        didPass = CUTest_didTestPass(next(testSuite->testsList)) && didPass;
    reset(testSuite->testsList);
    return didPass;
}