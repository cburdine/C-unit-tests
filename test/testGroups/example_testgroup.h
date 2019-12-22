#ifndef C_UNIT_TEST_EXAMPLE_TESTGROUP_H
#define C_UNIT_TEST_EXAMPLE_TESTGROUP_H

#include <stdio.h>
#include "../test_types.h"
#include "../test_assert.h"
#include <string.h>

int trivialTestCase(FILE*);
int exampleTestCase(FILE*);
int exampleIntTestCase(FILE*);
int trivialFailingTestCase(FILE*);

/*
    This is an array of the test cases in this test group.
    The struct syntax for each TestCase can be found in
    'test_types.h'. It can be initialized as shown below,
    consisting of a name followed by a pointer to the test
    function itself. 
    
    The array must be terminated by the value END_OF_TEST_CASES.

*/
static TestCase STRUCTURES_TEST_CASE_ARR[] = {
    {"Trivial Test Case", trivialTestCase},
    {"Example Test Case", exampleTestCase},
    {"Example Test Case with Integers", exampleIntTestCase},
    {"Trivial Failing Test Case", trivialFailingTestCase},
    END_OF_TEST_CASES
};

/* 
    This is an example TestGroup struct
    which is added to the project's test manifest
    in manifest.h
*/
static TestGroup STRUCTURES_TESTS = {
    "Example Test Group",
    STRUCTURES_TEST_CASE_ARR
};

int trivialTestCase(FILE* testLog){
    
    /* 
        Every test case must explicitly return PASS or FAIL: 
    */
    return PASS;
}

int exampleTestCase(FILE* testLog){

    char *myStr  = "Hello",
    *myOtherStr = "World";

    /*
        by including '../test_assert.h', you have access
        to several assertion functions:
    */
    ASSERT(strlen(myStr) == strlen(myOtherStr));

    return PASS;
}

int exampleIntTestCase(FILE* testLog){

    int x = 42, y = 43;

    /* 
        Asserts x >= y, while allowing for
        the values to be printed in the case
        of failure.
    */
    ASSERT_INT_GREATER_EQUAL_TO(x,y);
    
    return PASS;
}

int trivialFailingTestCase(FILE* testLog){

    /*  
        Print information to the 'testLog' parameter to 
        handle more complicated PASS/FAIL criterion.
        While printing directly to the test log is not
        recommended, it is supplied nonetheless to allow
        for handling of more difficult test cases.
    */
    fputs("This test will always fail:\n", testLog);

    /*
        To explicitly faila test, simply return FAIL
    */
    return FAIL;
}

#endif /* C_UNIT_TEST_EXAMPLE_TESTGROUP_H */
