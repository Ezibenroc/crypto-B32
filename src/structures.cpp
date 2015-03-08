#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cassert>
#include "structures.h"

Block::Block(uint32_t b) : bits(b) {
}

Block::Block(const Block &other) : bits(other.getBits()) {
}

Block::Block(const std::vector<int> b) {
    this->bits = 0 ;
    assert(b.size() == 32) ;
    for(unsigned int i = 0 ; i < b.size () ; i++) {
        this->bits *= 2 ;
        this->bits += b[i] ;
    }
}

uint32_t Block::getBits(void) const {
    return this->bits ;
}

int Block::bitsXor(void) {
    int ret ;
    int x = this->getBits() ;
    ret = x&1 ;
    x >>= 1 ;
    for(int i = 0 ; i < 31 ; i++) {
        ret ^= x&1 ;
        x >>= 1 ;
    }
    return ret ;
}

// Bitwise AND
void Block::product(Block other) {
    this->bits&=other.getBits() ;
}

void Block::addition(Block other) {
    this->bits^=other.getBits() ;
}

void Block::setBox(int boxID, int box, int boxSize) {
    uint32_t mask = ((1<<boxSize)-1)<<(boxID*boxSize) ; // 0...011110...0
    box <<=(boxID*boxSize) ;
    this->bits = (this->bits & (~mask)) | box ;
}

void Block::substitution(int position, std::vector<int> subst) {
    uint32_t mask = 15<<(position*4) ; // 0...011110...0
    uint32_t newValue = mask & this->bits ; // i-th block
    newValue = newValue>>(position*4) ;
    newValue = subst[newValue] ;
    newValue = newValue<<(position*4) ;
    this->bits = (this->bits & (~mask)) | newValue ;
}

void Block::substitution(std::vector<int> subst) {
    for(unsigned int i = 0 ; i < 8 ; i++) {
        this->substitution(i, subst) ;
    }
}

std::vector<int> buildReverseSubstitution(std::vector<int> subst) {
    std::vector<int> rev(subst.size(), -1) ;
    for(unsigned int i = 0 ; i < subst.size() ; i++) {
        rev[subst[i]] = i ;
    }
    return rev ;
}

void Block::permutation(int shift) {
    if(shift < 0)
        shift = 32+shift ;
    if(shift == 0 || shift == 32)
        return ;
    uint32_t mask = (1 << shift) - 1;
    uint32_t newValue = this->bits & mask ;
    this->bits = this->bits>>shift ;
    newValue = newValue<<(32-shift) ;
    mask = (1 << (32-shift)) - 1;
    this->bits = (this->bits & mask) | newValue ;
}

void Block::turn(Block k) {
    this->substitution() ;
    this->permutation() ;
    this->addition(k) ;
}

void Block::encrypt(std::vector<Block> keys) {
    assert(keys.size() > 0) ;
    this->addition(keys[0]) ;
    for(unsigned int i = 1 ; i < keys.size() ; i++) {
        this->turn(keys[i]) ;
    }
}

void Block::encrypt(Block k0, Block k1, Block k2) {
    this->encrypt({k0, k1, k2}) ;
}

void Block::reverseTurn(Block k) {
    this->addition(k) ;
    this->permutation(-DEFAULT_SHIFT) ;
    // std::vector<int>subst = buildReverseSubstitution(DEFAULT_SUBST) ;
    this->substitution(REVERSE_DEFAULT_SUBST) ;
}


void Block::decrypt(std::vector<Block> keys) {
    assert(keys.size() > 0) ;
    for(unsigned int i = (unsigned int)(keys.size()-1) ; i > 0 ; i--) {
        this->reverseTurn(keys[i]) ;
    }
    this->addition(keys[0]) ;
}

void Block::decrypt(Block k0, Block k1, Block k2) {
    this->decrypt({k0, k1, k2}) ;
}
