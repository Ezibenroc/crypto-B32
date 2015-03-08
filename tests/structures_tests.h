#ifndef STRUCTURES_TESTS_H
#define STRUCTURES_TESTS_H

#include <cppunit/TestFixture.h>
class StructuresTests : public CppUnit::TestFixture {
    private:
        void testConstructor() ;
        void testXor() ;
        void testProduct() ;
        void testAddition() ;
        void testSetBox() ;
        void testSimpleSubstitution() ;
        void testWholeSubstitution() ;
        void testPermutation() ;
        void testTurn() ;
        void testEncryption() ;
        void testDecryption() ;
        void testEncryptDecrypt() ;
    public:
        static CppUnit::Test* suite() ;
} ;

#endif
