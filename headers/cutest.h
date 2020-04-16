#include "cutest_assert.h"

#ifndef CUTEST_Header

typedef struct CUTest CUTest;
CUTest *CUTest_create(char *name,void (*testFunction)(Assert *assert));
char* CUTest_testName(CUTest *test);
void CUTest_execute(CUTest *test);
int CUTest_didTestPass(CUTest *test);
void CUTest_destroy(CUTest *test);

#define CUTEST_HEADER
#endif
