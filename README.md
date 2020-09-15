# cest
A traditional unit testing library for C.

[![cest's automated build and test.](https://travis-ci.com/hadichahine/cest.svg?branch=master)](https://travis-ci.com/hadichahine/cest)

cest's current features:
- Single test execution.
- Test suite creation and execution.
- Before suite startup and after finishing hooks.

## Packages
- [cest-git](https://aur.archlinux.org/packages/cest-git/) on AUR

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
## Using Test Suite Constructor

The test suite conctructor is in its early stages with extremely small and basic features. Using the API is the way to go if you're going to use test hooks.
```
#include <cest/create_test_suite.h>

START_TEST_SUITE("Test that test is test")

int pow(int x){
	return x*x;
}

TEST("Test that pow(0) is zero",(Assert *assert){
    Assert_assertTrue(assert,pow(0) == 0);
});

TEST("Test that pow(2) == 4",(Assert *assert){
    Assert_assertTrue(assert,pow(2) == 4);
});

END_TEST_SUITE
```

## Using the Inner API
### Create and execute a single test
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
### Create and execute a test suite
- Include **cest**'s test suite header.
```C
#include <cest/cutestsuite.h>
```

- Create test suite.
```C
CUTestSuite *testSuite = CUTestSuite_create("Passing Test Suite");
CUTestSuite_addTest(testSuite, "passing test", passingTest);
```

- Execute test suite.
```C
CUTestSuite_execute(testSuite);
CUTestSuite_didPass(testSuite); //returns 1 if test passed; 0 otherwise.
```

### Add Before Startup and After Finishing Hooks
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

### Test & Test Suite Destruction
To Destroy test suite:
```C
CUTestSuite_destroy(testSuite);
```
similarly for any destroying a lone test:
```C
CUTest_destroy(test);
```
Test Suites (or single tests) are better destroyed if execution of the test suite (or test) has finished and it's not used again.

## Test Debugging

To debug any test from the test suite use the following command:
```C
[user@machine ~]$ make test-debug TEST=test_name
```
This command launches gdb on the target test.
