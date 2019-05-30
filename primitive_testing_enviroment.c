#include <stdio.h>

int testResult;

void runPrimitiveTest(char* testName,void (*testFunction)()){
	testResult = -1;
	testFunction();
	printf("%s : ",testName);
	switch(testResult) {
		case -1: printf("No assertions.");break;
		case 0: printf("Failed");break;
		default: printf("Passed.");break;
	}
	printf("\n");
}

void primititiveAssertTrue(int statement){
	testResult = testResult && statement;
}