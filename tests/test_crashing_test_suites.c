#include "primitive_testing_environment.h"
#include <string.h>
#include "cutest.h"
#include "cutestsuite.h"
#include "cutest_assert.h"

void passingTestFunction(Assert *assert){
    Assert_assertTrue(assert, 1);
}

void functionThatAccessesNullPointer(Assert *assert){
    int *test = NULL;
    *test = 3;
}

void testThatTestFailsWhenBeforeTestSuiteHookAccessesANullPointer(){
    CUTestSuite *testSuite = CUTestSuite_create("Test suite");
    CUTestSuite_runHookBeforeStartingSuite(testSuite,functionThatAccessesNullPointer);
    CUTestSuite_addTest(testSuite, "True test",passingTestFunction);
	CUTestSuite_execute(testSuite);
	primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
    CUTestSuite_destroy(testSuite);
}

void functionThatDividesByZero(Assert *assert){
    int z = 0;
    int x = 3/z;
}

void testThatTestFailsWhenBeforeTestSuiteHookDividesByZero(){
    CUTestSuite *testSuite = CUTestSuite_create("Test suite");
    CUTestSuite_runHookBeforeStartingSuite(testSuite,functionThatDividesByZero);
    CUTestSuite_addTest(testSuite, "True test",passingTestFunction);
	CUTestSuite_execute(testSuite);
	primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
    CUTestSuite_destroy(testSuite);
}

void testThatTestFailsWhenAfterTestSuiteHookAccessesANullPointer(){
    CUTestSuite *testSuite = CUTestSuite_create("Test suite");
    CUTestSuite_runHookAfterFinishingSuite(testSuite,functionThatAccessesNullPointer);
    CUTestSuite_addTest(testSuite, "True test",passingTestFunction);
	CUTestSuite_execute(testSuite);
	primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
    CUTestSuite_destroy(testSuite);
}

void testThatTestFailsWhenAfterTestSuiteHookDividesByZero(){
    CUTestSuite *testSuite = CUTestSuite_create("Test suite");
    CUTestSuite_runHookAfterFinishingSuite(testSuite,functionThatDividesByZero);
    CUTestSuite_addTest(testSuite, "True test",passingTestFunction);
	CUTestSuite_execute(testSuite);
	primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
    CUTestSuite_destroy(testSuite);
}

int main(){
    return !(runPrimitiveTest("Test that test fails when before test suite hook accesses a null pointer.",
             testThatTestFailsWhenBeforeTestSuiteHookAccessesANullPointer) &&
             runPrimitiveTest("Test that test fails when before test suite hook divides by zero.",
             testThatTestFailsWhenBeforeTestSuiteHookDividesByZero) &&
             runPrimitiveTest("Test that test fails when after test suite hook accesses a null pointer.",
             testThatTestFailsWhenAfterTestSuiteHookAccessesANullPointer) &&
             runPrimitiveTest("Test that test fails when after test suite hook divides by zero.",
             testThatTestFailsWhenAfterTestSuiteHookDividesByZero));
}