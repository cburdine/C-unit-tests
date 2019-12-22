#include <stdio.h>
#include "test/test.h"
#include "test/testGroups/example_testgroup.h"

int main(int argc, char** argv){
    
    FILE* TEST_LOG = stdout;

    /* this will run individual test groups: */
    runTestGroup(&STRUCTURES_TESTS,TEST_LOG);

    /* 
        this will run all test groups for the project that are listed 
        in 'test/manifest.h' 
    */
    runManifestTestGroups(TEST_LOG);

}