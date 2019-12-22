# C-unit-tests
A simple unit testing framework for C projects.


## Testing Framework Overview
Since gcc and other popular C compilers do not come equipped by default with unit testing capabilities, this project is intended to supply a lightweight and simple unit testing interface that can be copied directly into a project repository. This framework is designed with smaller projects in mind, and is intended to reduce the amount of time spent writing testing interfaces and unit tests themselves.

Unit tests in this testing framework are called *TestCases*, which consist of a test name and a test function, such as the one below:
```
int exampleIntTestCase(FILE* testLog){

    int x = 42, y = 43;

    /* This assertion will fail */
    ASSERT_INT_GREATER_EQUAL_TO(x,y);
    
    return PASS;
}
```

TestCases are grouped together in *TestGroups*. Each TestGroup corresponds to a single '.h' file in the 'test/testGroups' directory which contains all of the TestCases in that TestGroup. For an example, see 'test/testGroups/example_test.h'.

While a specific TestGroup can be run by including its corresponding header file and calling
```
runTestGroup(TestGroup* tGroup, FILE* testLog)
``` 
(for an example see main.c), this framework provides a better way of organizing TestGroups. 

Ideally, all TestGroups for a project should be listed in the TestGroup manifest in 'test/manifest.h'. That way, the testGroups can be run in batches using: 
```
runManifestTestGroups(FILE* testLog)
```
 or 
```
runSpecifiedManifestTestGroups(int groupNameCount, char** groupNames, FILE* testLog)
```
For more information, see the examples in 'main.c'.

---

## Installation

The easiest way to install this framework is to copy the 'test' directory and all of its contents into an existing project's directory. The programmer is expected to supply a testing driver (such as the example driver 'main.c' in this repository). This driver must include 'test/test.h'.
Another simple example that prints test data to stdout is provided below:
```
#include <stdio.h>
#include "test.h"

int main(int argc, char** argv){
    runManifestTestGroups(stdout);
}
```

This framework is guaranteed to compiled with the C99 standard. It may also compile with the ansi/c89 standard with warnings due to potentialy unsupported large integer types, but this framework provides no guarantees in that respect. 

To compile the framework and example driver, go to the directory of this project and run the ``make`` command, assuming that GNU make is installed and the gcc C compiler is installed. Otherwise, this project can be compiled with the gcc compiler using the following:
```
gcc -std=c99 -o bin/testExample main.c
```
(Some adjustments of the above may need to be made for Windows users)

