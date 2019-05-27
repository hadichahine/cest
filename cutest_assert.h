#ifndef CUTEST_ASSERT_Header

typedef struct Assert Assert;
Assert *Assert_create();
void Assert_assertTrue(Assert *assert,int boolean);
int Assert_result(Assert *assert);

#define CUTEST_ASSERT_Header
#endif
