# cest
A traditional unit testing library for C.

[![cest's automated build and test.](https://travis-ci.com/hadichahine/cest.svg?branch=master)](https://travis-ci.com/hadichahine/cest)

cest's current features:
- Single test execution.
- Test suite creation and execution.
- Before suite startup and after finishing hooks.

## Dependencies
- **make**
- **libc**

## Developer Extra Dependencies
- **gdb**
- **valgrind**

## Installation
**cest** works for now only on **GNU/Linux** based operating systems.
```
user@machine$ make
user@machine$ make check
user@machine$ make install INSTALL_DIR=/usr/
```
**INSTALL_DIR** is **/usr/** by default.

All executed make tasks should complete successfully. 

## Test Compilation
- Compile against libcest.so.
```
user@machine$ gcc test.c -lcest -o CestSampleTest
```

## Create and execute a single test
- Include **cest**'s test header.
```C
#include <cest/cutest.h>
```

- Create test function globally.
```C
void test_function(Assert *assert){
  Assert_assertTrue(assert, 1+1 == 2);
}
```
- Create single test.
```C
CUTest *test = CUTest_create("Test name is here", test_function);
```
- Execute test.
```C
CUTest_execute(test);
CUTest_didTestPass(test); //returns 1 if test passed; 0 otherwise.
```
## Create and execute test suite
- Include **cest**'s test suite header.
```C
#include <cest/cutestsuite.h>
```
- Create single test (as described previously).
```C
CUTest *passingTest = ...;
```

- Create test suite.
```C
CUTestSuite *testSuite = CUTestSuite_create("Passing Test Suite");
CUTestSuite_addTest(testSuite,CUTest_create("passing test", passingTest));
```

- Execute test suite.
```C
CUTestSuite_execute(testSuite);
CUTestSuite_didPass(testSuite); //returns 1 if test passed; 0 otherwise.
```

## Add Before Startup and After Finishing Hooks
```C
void beforeStartHook() {
  // Setup suite
}

void afterFinishtHook() {
  // Teardown suite
}

CUTestSuite_runHookBeforeStartingSuite(testSuite, beforeStartHook);
CUTestSuite_runHookAfterFinishingSuite(testSuite, afterFinishHook);
```
