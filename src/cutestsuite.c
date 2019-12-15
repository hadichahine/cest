#include "cutest.h"
#include "linkedlist.h"
#include <stdlib.h>

typedef struct {
    char *name;
    LinkedList *testsList;
    void (*beforeStartFunction)();
    void (*afterFinishFunction)();
} CUTestSuite;

void emptyFunction(){}

CUTestSuite *CUTestSuite_create(char *name){
    CUTestSuite *testSuite = (CUTestSuite*)malloc(sizeof(CUTestSuite));
    testSuite->name = name;
    testSuite->testsList = createLinkedList();
    testSuite->beforeStartFunction = emptyFunction;
    testSuite->afterFinishFunction = emptyFunction;
    return testSuite;
}

char *CUTestSuite_name(CUTestSuite *testSuite){
    return testSuite->name;
}

void CUTestSuite_addTest(CUTestSuite *testSuite,CUTest *test){
    addItemToLinkedList(testSuite->testsList,test);
}

void CUTestSuite_runHookBeforeStartingSuite(CUTestSuite *testSuite, void (*hook)()){
    testSuite->beforeStartFunction = hook;
}

void CUTestSuite_runHookAfterFinishingSuite(CUTestSuite *testSuite, void (*hook)()){
    testSuite->afterFinishFunction = hook;
}

void CUTestSuite_execute(CUTestSuite *testSuite){
    testSuite->beforeStartFunction();
    while(!reachedEnd(testSuite->testsList))
        CUTest_execute(next(testSuite->testsList));
    reset(testSuite->testsList);
    testSuite->afterFinishFunction();
}

int CUTestSuite_didPass(CUTestSuite *testSuite){
    int didPass = 1;
    while(!reachedEnd(testSuite->testsList))
        didPass = CUTest_didTestPass(next(testSuite->testsList)) && didPass;
    reset(testSuite->testsList);
    return didPass;
}