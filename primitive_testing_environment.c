#include <stdio.h>

int testResult;

void runTest(char* testName,void (*testFunction)()){
	testResult = 1;
	testFunction();
	printf("%s : ",testName);	
	if(testResult)
		puts("Passed");
	else puts("Failed");
		
}

void assertTrue(int statement){
	testResult = testResult && statement;
}

void assertIntegerEquals(int a,int b){
	assertTrue(a == b);
}
