#ifndef PRIMITIVE_TESTING

int runPrimitiveTest(char* testName,void (*testFunction)());
void primitiveAssertTrue(int statement);

#define PRIMITIVE_TESTING
#endif
