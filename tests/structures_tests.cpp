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

#include <random>
#include <time.h>

#include "../src/structures.h"

#include "structures_tests.h"

void StructuresTests::testConstructor() {
    srand((unsigned int)time(NULL)) ;
    for(int i = 0 ; i < 10 ; i++) {
        uint32_t r = rand() ;
        Block b(r) ;
        CPPUNIT_ASSERT_EQUAL(b.getBits(), r) ;
        Block c(r) ;
        CPPUNIT_ASSERT_EQUAL(c.getBits(), r) ;
    }
    Block b(std::vector<int>({
        0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0,\
        0, 1, 0, 0, 1, 0, 0, 0
    })) ;
    CPPUNIT_ASSERT_EQUAL(b.getBits(), (uint32_t)0b01101001100000101011111001001000) ;
}

void StructuresTests::testXor() {
    CPPUNIT_ASSERT_EQUAL(Block(0b1110101101).bitsXor(), 1) ;
    CPPUNIT_ASSERT_EQUAL(Block(0b11100101100100).bitsXor(), 1) ;
    CPPUNIT_ASSERT_EQUAL(Block(0b11101101101).bitsXor(), 0) ;
    CPPUNIT_ASSERT_EQUAL(Block(0b111001011010100).bitsXor(), 0) ;
}

void StructuresTests::testProduct() {
    Block k(7) ;        // 0...00111
    Block b(12) ;   // 0...01100
    b.product(k) ;         // 0...00100
    CPPUNIT_ASSERT_EQUAL((uint32_t)4, b.getBits()) ;
    b.product(k) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)4, b.getBits()) ;
}

void StructuresTests::testAddition() {
    Block k(7) ;        // 0...00111
    Block b(12) ;   // 0...01100
    b.addition(k) ;         // 0...01011
    CPPUNIT_ASSERT_EQUAL((uint32_t)11, b.getBits()) ;
    b.addition(k) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)12, b.getBits()) ;
}

void StructuresTests::testSetBox() {
    Block k(7) ;        // 0...00111
    k.setBox(0, 8) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)8, k.getBits()) ;
    k.setBox(6, 13) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)218103816, k.getBits()) ;
    k.setBox(3, 3) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)218116104, k.getBits()) ;
}

void StructuresTests::testSimpleSubstitution() {
    Block b(7) ; // 0...00111
    std::vector<int> subst = {3, 15, 10, 5, 12, 0, 7, 4, 2, 6, 13, 11, 14, 1, 9, 8} ;
    b.substitution(0, subst) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)4, b.getBits()) ;
    b.substitution(0, subst) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)12, b.getBits()) ;
    b.substitution(0, subst) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)14, b.getBits()) ;
    b = Block(208) ; // 0...011010000
    b.substitution(1, subst) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)16, b.getBits()) ;
    b.substitution(1, subst) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)240, b.getBits()) ;
    b.substitution(1, subst) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)128, b.getBits()) ;
}

void StructuresTests::testWholeSubstitution() {
    Block b(0b10011000001010111110010010000110) ;
    std::vector<int> subst = {3, 15, 10, 9, 12, 7, 0, 4, 2, 6, 13, 14, 11, 1, 5, 8} ;
    b.substitution(subst) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b01100010101011100101110000100000, b.getBits()) ;
    std::vector<int> reverseSubst = buildReverseSubstitution(subst) ;
    b.substitution(reverseSubst) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b10011000001010111110010010000110, b.getBits()) ;
}

void StructuresTests::testPermutation() {
    Block b(0b10011000001010111110010010000110) ;
    b.permutation(3) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b11010011000001010111110010010000, b.getBits()) ;
    b.permutation(2) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b00110100110000010101111100100100, b.getBits()) ;
    b.permutation(2) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b00001101001100000101011111001001, b.getBits()) ;
    b.permutation(6) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b00100100001101001100000101011111, b.getBits()) ;
    b.permutation(24) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b00110100110000010101111100100100, b.getBits()) ;
    b.permutation(31) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b01101001100000101011111001001000, b.getBits()) ;
    b.permutation(0) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b01101001100000101011111001001000, b.getBits()) ;
    b.permutation(32) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b01101001100000101011111001001000, b.getBits()) ;
    b.permutation(-5) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b00110000010101111100100100001101, b.getBits()) ;
    b.permutation(3) ;
    b.permutation(-3) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b00110000010101111100100100001101, b.getBits()) ;
    b.permutation(-12) ;
    b.permutation(12) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b00110000010101111100100100001101, b.getBits()) ;
}

void StructuresTests::testTurn() {
    Block b(0) ;
    b.turn(Block(42)) ;
    b.reverseTurn(Block(42)) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0, b.getBits()) ;
    b = Block((5<<29) + (7<<15) + 15) ;
    b.turn(Block((31<<12)+18)) ;
    b.reverseTurn(Block((31<<12)+18)) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)((5<<29) + (7<<15) + 15), b.getBits()) ;
    b.addition(Block(42)) ;
    b.turn(Block(-1)) ;
    b.turn(Block(0)) ;
    b.reverseTurn(Block(0)) ;
    b.reverseTurn(Block(-1)) ;
    b.addition(Block(42)) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)((5<<29) + (7<<15) + 15), b.getBits()) ;
}

void StructuresTests::testEncryption() {
    Block b(0) ;
    b.encrypt(
        Block(0b10000000000000000000000000000001),
        Block(0b11111111111111111111111111111111),
        Block(0b01111111111111111111111111111110)
    ) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0b00111001011001100110011001100110, b.getBits()) ;
}

void StructuresTests::testDecryption() {
    Block b(0b00111001011001100110011001100110) ;
    b.decrypt(
        Block(0b10000000000000000000000000000001),
        Block(0b11111111111111111111111111111111),
        Block(0b01111111111111111111111111111110)
    ) ;
    CPPUNIT_ASSERT_EQUAL((uint32_t)0, b.getBits()) ;
}

void StructuresTests::testEncryptDecrypt() {
    srand((unsigned int) time(NULL)) ;
    for(int i = 0 ; i < 10000 ; i++) {
        Block text((uint32_t)rand()) ;
        Block copy(text) ;
        Block k1((uint32_t)rand()) ;
        Block k2((uint32_t)rand()) ;
        Block k3((uint32_t)rand()) ;
        text.encrypt(k1, k2, k3) ;
        if(text.getBits() == copy.getBits()){
            std::cerr << "WARNING: cipher is the same than plain text." << std::endl ;
        }
        text.decrypt(k1, k2, k3) ;
        CPPUNIT_ASSERT_EQUAL(text.getBits(), copy.getBits()) ;
    }
}

CppUnit::Test* StructuresTests::suite() {
    CppUnit::TestSuite *suite = new CppUnit::TestSuite("StructuresTests");
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testConstructor",
                &StructuresTests::testConstructor));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testXor",
                &StructuresTests::testXor));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testProduct",
                &StructuresTests::testProduct));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testAddition",
                &StructuresTests::testAddition));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testSetBox",
                &StructuresTests::testSetBox));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testSimpleSubstitution",
                &StructuresTests::testSimpleSubstitution));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testWholeSubstitution",
                &StructuresTests::testWholeSubstitution));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testPermutation",
                &StructuresTests::testPermutation));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testTurn",
                &StructuresTests::testTurn));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testEncryption",
                &StructuresTests::testEncryption));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testDecryption",
                &StructuresTests::testDecryption));
    suite->addTest(new CppUnit::TestCaller<StructuresTests>("StructuresTests_testEncryptDecrypt",
                &StructuresTests::testEncryptDecrypt));
    return suite;
}
