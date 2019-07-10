#include "cutest.h"
#include "cutest_assert.h"
#include "cutestsuite.h"
#include "primitive_testing_environment.h"
#define TRUE 1
#define FALSE 0

void passingTest(Assert *assert){
    Assert_assertTrue(assert,TRUE);
}

void failingTest(Assert *assert){
    Assert_assertTrue(assert,FALSE);
}

void testThatTestSuitePassesWhenAPassingTestIsTheOnlyTestAddedToIt(){
    CUTestSuite *testSuite = CUTestSuite_create("Passing Test Suite");
    CUTestSuite_addTest(testSuite,CUTest_create("passing test",passingTest));
    CUTestSuite_execute(testSuite);
    primitiveAssertTrue(CUTestSuite_didPass(testSuite));
}

void testThatTestSuiteFailsWhenAFailingTestIsTheOnlyTestAddedToIt(){
    CUTestSuite *testSuite = CUTestSuite_create("Failing Test Suite");
    CUTestSuite_addTest(testSuite,CUTest_create("failing",failingTest));
    CUTestSuite_execute(testSuite);
    primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
}

int main(){
    runPrimitiveTest("testThatTestSuitePassesWhenAPassingTestIsTheOnlyTestAddedToIt",testThatTestSuitePassesWhenAPassingTestIsTheOnlyTestAddedToIt);
    runPrimitiveTest("testThatTestSuiteFailsWhenAFailingTestIsTheOnlyTestAddedToIt",testThatTestSuiteFailsWhenAFailingTestIsTheOnlyTestAddedToIt);
    return 0;
}
