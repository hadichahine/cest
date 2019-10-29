# cest
A traditional unit testing library for C.

[![cest's automated build and test.](https://travis-ci.com/hadichahine/cest.svg?branch=master)](https://travis-ci.com/hadichahine/cest)

cest's current features:
- Single test execution

## Dependencies
- **libc**

## Installation
**cest** works for now only on **GNU/Linux** based operating systems.
```
user@machine$ make
user@machine$ make check
user@machine$ make install INSTALL_DIR=/usr/
```
**INSTALL_DIR** is **/usr/** by default.

All executed make tasks should complete successfully. 

## Creating and executing a single test
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
- Initialize test.
```C
CUTest *test = CUTest_create("Test name is here", test_function);
```
- Execute test.
```C
CUTest_execute(test);
CUTest_didTestPass(test); //returns 1 if test passed; 0 otherwise.
```
- Compile against libcest.so.
```
user@machine$ gcc test.c -lcest -o CestSampleTest
```
