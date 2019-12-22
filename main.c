#include <stdio.h>
#include "test/test.h"
#include "test/testGroups/example_testgroup.h"

int main(int argc, char** argv){
    
    #define  NUM_NAMES 1
    char* TEST_GROUP_NAMES[NUM_NAMES] = { 
        "Example Test Group" 
    };

    FILE* TEST_LOG = stdout;

    /* This will run individual test groups: */

    /* runTestGroup(&STRUCTURES_TESTS,TEST_LOG); */

    /* 
        This will run all test groups for the project that are listed 
        in 'test/manifest.h' 
    */
    runManifestTestGroups(TEST_LOG);

    /* This will run specific test groups from the manifest by name */

    /* runSpecifiedManifestTestGroups(NUM_NAMES, TEST_GROUP_NAMES, TEST_LOG); */

}