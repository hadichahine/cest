#include "cutest.h"

#ifndef CUTESTSUITE_Header

typedef struct CUTestSuite CUTestSuite;
CUTestSuite *CUTestSuite_create(char *name);
void CUTestSuite_addTest(CUTestSuite *testSuite,CUTest *test);
void CUTestSuite_execute(CUTestSuite *testSuite);
int CUTestSuite_didPass(CUTestSuite *testSuite);

#define CUTESTSUITE_Header
#endif