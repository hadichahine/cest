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

int main(){
	return !(
    runPrimitiveTest("testThatTestSuitePassesWhenAPassingTestIsTheOnlyTestAddedToIt",
		testThatTestSuitePassesWhenAPassingTestIsTheOnlyTestAddedToIt) &&
	runPrimitiveTest("testThatTestSuiteFailsWhenAFailingTestIsTheOnlyTestAddedToIt",
		testThatTestSuiteFailsWhenAFailingTestIsTheOnlyTestAddedToIt) &&
	runPrimitiveTest("testThatTestSuiteFailsWhenFirstAFailingTestThenASucceedingTestAreAddedToIt",
		testThatTestSuiteFailsWhenFirstAFailingTestThenASucceedingTestAreAddedToIt) &&
	runPrimitiveTest("testThatTestSuiteFailsWhenFirstASucceedingTestThenAFailingTestAreAddedToIt",
		testThatTestSuiteFailsWhenFirstASucceedingTestThenAFailingTestAreAddedToIt) &&
	runPrimitiveTest("testThatTestSuiteFailsWhenFirstASucceedingTestThenAFailingTestThenASucceedingTestAreAddedToIt",
		testThatTestSuiteFailsWhenFirstASucceedingTestThenAFailingTestThenASucceedingTestAreAddedToIt) &&
	runPrimitiveTest("testAccessingTestSuiteName",
		testAccessingTestSuiteName));
    return 0;
}
