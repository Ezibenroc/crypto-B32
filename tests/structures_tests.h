#ifndef STRUCTURES_TESTS_H
#define STRUCTURES_TESTS_H

#include <cppunit/TestFixture.h>
class StructuresTests : public CppUnit::TestFixture {
    private:
        void testAddition();
    public:
        static CppUnit::Test* suite();
};

#endif