#include "TestHarness.h"

#define DEBUG 0

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

    return 0;
}
