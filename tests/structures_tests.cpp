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

void StructuresTests::testSimpleSubstitution() {
    Block b(7) ; // 0...00111
    std::vector<int> subst = {3, 15, 10, 5, 12, 0, 7, 4, 2, 6, 13, 11, 14, 1, 9, 8} ;
    b.substitution(0, subst) ;
    CPPUNIT_ASSERT(b.getBits() == 4) ;
    b.substitution(0, subst) ;
    CPPUNIT_ASSERT(b.getBits() == 12) ;
    b.substitution(0, subst) ;
    CPPUNIT_ASSERT(b.getBits() == 14) ;
    b = Block(208) ; // 0...011010000
    b.substitution(1, subst) ;
    CPPUNIT_ASSERT(b.getBits() == 16) ;
    b.substitution(1, subst) ;
    CPPUNIT_ASSERT(b.getBits() == 240) ;
    b.substitution(1, subst) ;
    CPPUNIT_ASSERT(b.getBits() == 128) ;
}

CppUnit::Test* StructuresTests::suite() {
    CppUnit::TestSuite *suite = new CppUnit::TestSuite("StructuresTests");
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testAddition",
                &StructuresTests::testAddition));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testSimpleSubstitution",
                &StructuresTests::testSimpleSubstitution));
    return suite;
}
