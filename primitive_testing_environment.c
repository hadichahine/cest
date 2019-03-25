#include <stdio.h>
#include "cutest.h"
#include "cutest_assert.h"

int testResult;

void runPrimitiveTest(char* testName,void (*testFunction)()){
	testResult = 1;
	testFunction();
	printf("%s : ",testName);	
	if(testResult)
		puts("Passed");
	else puts("Failed");
		
}

void primititiveAssertTrue(int statement){
	testResult = testResult && statement;
}

void testThatIsAlwaysTrue(Assert *assert){
	assertTrue(assert,5 == 5);
}

void testThatAnAlwaysTrueTest(){
	CUTest *test = CUTest_create("Testo Trutouto",testThatIsAlwaysTrue);
	CUTest_execute(test);
	primititiveAssertTrue(didTestPass(test));
}

void testThatIsAlwaysFalse(Assert *assert){
	assertTrue(assert,1 == 2);
}

void testThatAnAlwaysFalseTest(){
	CUTest *test = CUTest_create("Testo Failouto",testThatIsAlwaysFalse);
	CUTest_execute(test);
	primititiveAssertTrue(!didTestPass(test));
}

int main(){
	runPrimitiveTest("Check if test passes for always true test.",testThatAnAlwaysTrueTest);
	runPrimitiveTest("Check if test fails for always false test.",testThatAnAlwaysFalseTest);
	return 0;
}
