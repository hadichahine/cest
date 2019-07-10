#ifndef PRIMITIVE_TESTING

void runPrimitiveTest(char* testName,void (*testFunction)());
void primitiveAssertTrue(int statement);

#define PRIMITIVE_TESTING
#endif