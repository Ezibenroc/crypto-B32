#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cassert>
#include <string>

#include "../src/structures.h"

#include "structures_tests.h"

void StructuresTests::testAddition() {
    Key k(7) ;        // 0...00111
    Block b(12) ;   // 0...01100
    b.addition(k) ;         // 0...01011
    CPPUNIT_ASSERT(b.getBits() == 11) ;
}

CppUnit::Test* StructuresTests::suite() {
    CppUnit::TestSuite *suite = new CppUnit::TestSuite("StructuresTests");
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testAddition",
                &StructuresTests::testAddition));
    return suite;
}
