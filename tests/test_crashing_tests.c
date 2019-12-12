#include "primitive_testing_environment.h"
#include <string.h>
#include "cutest.h"
#include "cutest_assert.h"

void testThatAccessesANullPointer(Assert *assert){
    int *test = NULL;
    *test = 3;
}

void testThatTestFailsWhenTestFunctionAccessesANullPointer(){
	CUTest *test = CUTest_create("Null test pointer",testThatAccessesANullPointer);
	CUTest_execute(test);
	primitiveAssertTrue(!CUTest_didTestPass(test));
}

void testThatTestsFailsWhenDividingByZero(Assert *assert){
    int z = 0;
    int x = 3/z;
}

void testThatTestFailsWhenTestFunctionDividesByZero(){
	CUTest *test = CUTest_create("Divide by zero",testThatTestsFailsWhenDividingByZero);
	CUTest_execute(test);
	primitiveAssertTrue(!CUTest_didTestPass(test));
}

int main(){
    return !(runPrimitiveTest("Test that test fails when test function accesses a null pointer.",
             testThatTestFailsWhenTestFunctionAccessesANullPointer) && 
             runPrimitiveTest("Test that test fails when test function divides by zero.",
             testThatTestFailsWhenTestFunctionDividesByZero));
}