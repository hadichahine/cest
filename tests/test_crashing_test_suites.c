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
	CUTest *test = CUTest_create("True test",passingTestFunction);
    CUTestSuite_addTest(testSuite,test);
	CUTestSuite_execute(testSuite);
	primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
}

void functionThatDividesByZero(Assert *assert){
    int z = 0;
    int x = 3/z;
}

void testThatTestFailsWhenBeforeTestSuiteHookDividesByZero(){
    CUTestSuite *testSuite = CUTestSuite_create("Test suite");
    CUTestSuite_runHookBeforeStartingSuite(testSuite,functionThatDividesByZero);
	CUTest *test = CUTest_create("True test",passingTestFunction);
    CUTestSuite_addTest(testSuite,test);
	CUTestSuite_execute(testSuite);
	primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
}

int main(){
    return !(runPrimitiveTest("Test that test fails when before test suite hook accesses a null pointer.",
             testThatTestFailsWhenBeforeTestSuiteHookAccessesANullPointer) &&
             runPrimitiveTest("Test that test fails when before test suite hook divides by zero.",
             testThatTestFailsWhenBeforeTestSuiteHookDividesByZero));
}