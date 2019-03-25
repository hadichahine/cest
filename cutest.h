#include "cutest_assert.h"

#ifndef CUTEST_Header

typedef struct CUTest CUTest;
CUTest *CUTest_create(char *name,void (*testFunction)(Assert *assert));
void CUTest_execute(CUTest *test);
int didTestPass(CUTest *test);

#define CUTEST_HEADER
#endif
