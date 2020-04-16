#include "cutest.h"

#ifndef CUTESTSUITE_Header

typedef struct CUTestSuite CUTestSuite;
CUTestSuite *CUTestSuite_create(char *name);
char *CUTestSuite_name(CUTestSuite *testSuite);
void CUTestSuite_addTest(CUTestSuite *testSuite, char *name, void (*testFunction)(Assert *assert));
void CUTestSuite_runHookBeforeStartingSuite(CUTestSuite *testSuite, void (*hook)());
void CUTestSuite_runHookAfterFinishingSuite(CUTestSuite *testSuite, void (*hook)());
void CUTestSuite_execute(CUTestSuite *testSuite);
int CUTestSuite_didPass(CUTestSuite *testSuite);
void CUTestSuite_destroy(CUTestSuite *testSuite);

#define CUTESTSUITE_Header
#endif