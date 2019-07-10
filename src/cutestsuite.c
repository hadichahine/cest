#include "cutest.h"
#include "linkedlist.h"
#include <stdlib.h>

typedef struct {
    LinkedList *testsList;
} CUTestSuite;

CUTestSuite *CUTestSuite_create(char *name){
    CUTestSuite *testSuite = (CUTestSuite*)malloc(sizeof(CUTestSuite));
    testSuite->testsList = createLinkedList();
    return testSuite;
}

void CUTestSuite_addTest(CUTestSuite *testSuite,CUTest *test){
    addItemToLinkedList(testSuite->testsList,test);
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