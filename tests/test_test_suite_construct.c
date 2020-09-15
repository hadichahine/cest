#include "create_test_suite.h"

START_TEST_SUITE("Test that test is test")

TEST("Test that 1+1 = 2",(Assert *assert){
    Assert_assertTrue(assert,1 + 1 == 2);
});

TEST("Test that 2 - 1 = 0",(Assert *assert){
    Assert_assertTrue(assert,2 - 1 == 1);
});

END_TEST_SUITE
