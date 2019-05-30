#include <string.h>
#include "cutest.h"
#include "cutest_assert.h"
#include "primitive_testing_environment.h"

void testThatIsAlwaysTrue(Assert *assert){
	Assert_assertTrue(assert,5 == 5);
}

void testThatAnAlwaysTrueTest(){
	CUTest *test = CUTest_create("Testo Trutouto",testThatIsAlwaysTrue);
	CUTest_execute(test);
	primititiveAssertTrue(CUTest_didTestPass(test));
}

void testThatIsAlwaysFalse(Assert *assert){
	Assert_assertTrue(assert,1 == 2);
}

void testThatAnAlwaysFalseTest(){
	CUTest *test = CUTest_create("Testo Failouto",testThatIsAlwaysFalse);
	CUTest_execute(test);
	primititiveAssertTrue(!CUTest_didTestPass(test));
}


void dummyTest(Assert *assert){}

void testRetrievingTestName(){
	CUTest *test = CUTest_create("This is my name.",dummyTest);
	primititiveAssertTrue(!strcmp("This is my name.",CUTest_testName(test)));
}

void multipleAssertionTestWithSecondFailing(Assert *assert){
	Assert_assertTrue(assert,5 == 4);
	Assert_assertTrue(assert,5 == 5);
}

void testThatTestTakesAllAsssertionsIntoConsideration(){
	CUTest *test = CUTest_create("Testo.",multipleAssertionTestWithSecondFailing);
	CUTest_execute(test);
	primititiveAssertTrue(!CUTest_didTestPass(test));
}

int main(){
	runPrimitiveTest("Check if test passes for always true test.",testThatAnAlwaysTrueTest);
	runPrimitiveTest("Check if test fails for always false test.",testThatAnAlwaysFalseTest);
	runPrimitiveTest("Test that test return its name.",testRetrievingTestName);
	runPrimitiveTest("Test that test takes all asssertions into consideration.",testThatTestTakesAllAsssertionsIntoConsideration);
	return 0;
}
