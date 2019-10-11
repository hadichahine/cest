#include <stdio.h>

int testResult;

int runPrimitiveTest(char* testName,void (*testFunction)()){
	testResult = -1;
	testFunction();
	printf("%s : ",testName);
	switch(testResult) {
		case -1: printf("No assertions.\n");return 0;
		case 0: printf("Failed.\n");return 0;
		default: printf("Passed.\n");return 1;
	}
}

void primitiveAssertTrue(int statement){
	testResult = testResult && statement;
}
