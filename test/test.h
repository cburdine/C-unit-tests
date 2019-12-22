#ifndef C_UNIT_TEST_H
#define C_UNIT_TEST_H

#include <stdio.h>
#include "manifest.h"
#include "test_types.h"
#include "test_assert.h"

int runTestGroup(TestGroup* tGroup, FILE* testLog){
    int tind, result, numPassed;
    FILE* assertLogTemp;
    
    if(tGroup == NULL){
        fputs("Test Group undefined; tests cannot be run.", testLog);
        return FAIL;
    }

    numPassed = 0;
    result = PASS;

    fprintf(testLog, "Running testgroup \'%s\':\n", tGroup->groupName);

    for(tind = 0; 
        tGroup->testCases[tind].name != NULL || 
        tGroup->testCases[tind].testCase != NULL;
        ++tind){

        result = tGroup->testCases[tind].testCase(testLog);

        fprintf(testLog, "[%s] %s::%s\n", 
            (result == PASS)? "PASS" : "FAIL",
             *(tGroup->groupName)? tGroup->groupName : "NULL", 
             *(tGroup->testCases[tind].name)? tGroup->testCases[tind].name : "UNNAMED"
        );

        if(result){ 
            ++numPassed; 
        } else {
            fprintf(testLog,"    %s\n", getAssertMessage());
        }
    }
    fprintf(testLog, "Testgroup \'%s\' finished; [%d/%d] tests passed.\n\n",
        tGroup->groupName, numPassed, tind);

    return (numPassed == tind)? PASS : FAIL;
}

int runManifestTestGroups(FILE* testLog){
    int tgInd, allPassed;

    allPassed = PASS;
    for(tgInd = 0; TEST_GROUP_MANIFEST[tgInd] != END_OF_MANIFEST; ++tgInd){
        allPassed &= runTestGroup(TEST_GROUP_MANIFEST[tgInd], testLog);
    }
}

int runSpecifiedManifestTestGroups(int groupNameCount, char** groupNames, FILE* testLog){
    int tgInd, gnInd, allPassed, numTestGroups;
    char foundMatch;

    allPassed = PASS;
    for(gnInd = 0; gnInd < groupNameCount; ++gnInd){
        foundMatch = 0;
        for(tgInd = 0; TEST_GROUP_MANIFEST[tgInd] != END_OF_MANIFEST; ++tgInd){
            if(TEST_GROUP_MANIFEST[tgInd]->groupName == groupNames[gnInd]){
                allPassed &= runTestGroup(TEST_GROUP_MANIFEST[tgInd], testLog);
                foundMatch = 1;
                break;
            }
        }
        if(!foundMatch){
            fprintf(testLog, 
                "ERROR- found no match for test group name '%s'\n\n", 
                groupNames[gnInd]
            );
        }
    }
}

#endif /* C_UNIT_TEST_H */
