#include <stdio.h>
#include "cutestsuite.h"
#include "cutest_assert.h"
#include "cutest.h"

#define START_TEST_SUITE(name) CUTestSuite *testSuite;void fillAndExecuteTestSuite(){testSuite = CUTestSuite_create(name);
#define TEST(name,exp) CUTestSuite_addTest(testSuite, name, ({void closure exp closure; }));
#define END_TEST_SUITE CUTestSuite_execute(testSuite);}int main(){fillAndExecuteTestSuite();printf("%s: %s\n", CUTestSuite_name(testSuite), CUTestSuite_didPass(testSuite) == 1 ? "Passed" : "Failed"); return !CUTestSuite_didPass(testSuite);}
