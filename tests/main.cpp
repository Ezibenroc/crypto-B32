#include <cppunit/ui/text/TestRunner.h>
#include "structures_tests.h"
#include <time.h>
#include <stdlib.h>

int main(void) {
    srand(static_cast<unsigned int>(time(NULL)));
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(StructuresTests::suite());
    runner.run();
    return 0;
}
