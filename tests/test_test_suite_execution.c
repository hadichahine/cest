#include "cutest.h"
#include "cutest_assert.h"
#include "cutestsuite.h"
#include "primitive_testing_environment.h"
#include <string.h>

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

void testThatTestSuiteFailsWhenFirstAFailingTestThenASucceedingTestAreAddedToIt(){
    CUTestSuite *testSuite = CUTestSuite_create("Failing Test Suite");
    CUTestSuite_addTest(testSuite,CUTest_create("failing",failingTest));
    CUTestSuite_addTest(testSuite,CUTest_create("passing test",passingTest));
    CUTestSuite_execute(testSuite);
    primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
}

void testThatTestSuiteFailsWhenFirstASucceedingTestThenAFailingTestAreAddedToIt(){
    CUTestSuite *testSuite = CUTestSuite_create("Failing Test Suite");
    CUTestSuite_addTest(testSuite,CUTest_create("passing test",passingTest));
    CUTestSuite_addTest(testSuite,CUTest_create("failing test",failingTest));
    CUTestSuite_execute(testSuite);
    primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
}

void testThatTestSuiteFailsWhenFirstASucceedingTestThenAFailingTestThenASucceedingTestAreAddedToIt(){
    CUTestSuite *testSuite = CUTestSuite_create("Failing Test Suite");
    CUTestSuite_addTest(testSuite,CUTest_create("passing test",passingTest));
    CUTestSuite_addTest(testSuite,CUTest_create("failing test",failingTest));
    CUTestSuite_addTest(testSuite,CUTest_create("passing test",passingTest));
    CUTestSuite_execute(testSuite);
    primitiveAssertTrue(!CUTestSuite_didPass(testSuite));
}

void testAccessingTestSuiteName(){
    CUTestSuite *testSuite = CUTestSuite_create("testo");
    primitiveAssertTrue(!strcmp("testo",CUTestSuite_name(testSuite)));
}

int isPreSuiteHookRun = 0;

void preSuiteHook(){
    isPreSuiteHookRun = 1;
}

void testThatPreStartHookIsRunOnceBeforeAnyTest(){
    CUTestSuite *testSuite = CUTestSuite_create("test suite with prestart hook");
    CUTestSuite_runHookBeforeStartingSuite(testSuite, preSuiteHook);
    CUTestSuite_execute(testSuite);
    primitiveAssertTrue(isPreSuiteHookRun);
}

int isPostSuiteHookRun = 0;

void postSuiteHook(){
    isPostSuiteHookRun = 1;
}

void testThatPostStartHookIsRunOnceBeforeAnyTest(){
    CUTestSuite *testSuite = CUTestSuite_create("test suite with poststart hook");
    CUTestSuite_runHookAfterFinishingSuite(testSuite, postSuiteHook);
    CUTestSuite_execute(testSuite);
    primitiveAssertTrue(isPostSuiteHookRun);
}

int main(){
	return !(
    runPrimitiveTest("Test that test suite passes when only a passing test is added to it.",
		testThatTestSuitePassesWhenAPassingTestIsTheOnlyTestAddedToIt) &&
	runPrimitiveTest("Test that test suite fails when only a failing test is added to it.",
		testThatTestSuiteFailsWhenAFailingTestIsTheOnlyTestAddedToIt) &&
	runPrimitiveTest("Test that test suite fails when first a failing test then a passing test are added to it.",
		testThatTestSuiteFailsWhenFirstAFailingTestThenASucceedingTestAreAddedToIt) &&
	runPrimitiveTest("Test that test suite fails when first a passing test then a failing test are added to it.",
		testThatTestSuiteFailsWhenFirstASucceedingTestThenAFailingTestAreAddedToIt) &&
	runPrimitiveTest("Test that test suite fails when first a passing test then a failing test then a passing test are added to it.",
		testThatTestSuiteFailsWhenFirstASucceedingTestThenAFailingTestThenASucceedingTestAreAddedToIt) &&
	runPrimitiveTest("Test accessing test suite name.",
		testAccessingTestSuiteName) && 
    runPrimitiveTest("Test that PreStart hook is run once before any test.",
        testThatPreStartHookIsRunOnceBeforeAnyTest) && 
    runPrimitiveTest("Test that PostStart hook is run once before any test.",
        testThatPostStartHookIsRunOnceBeforeAnyTest));
    return 0;
}
