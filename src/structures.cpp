#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cassert>
#include "structures.h"

Key::Key(uint32_t b) : bits(b) {
}

uint32_t Key::getBits(void) {
    return this->bits ;
}

Block::Block(uint32_t b) : Key(b) {
}

void Block::addition(Key key) {
    this->bits^=key.getBits() ;
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
    std::vector<int> rev(subst.size()) ;
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

void Block::turn(Key k) {
    this->substitution() ;
    this->permutation() ;
    this->addition(k) ;
}

void Block::encrypt(std::vector<Key> keys) {
    assert(keys.size() > 0) ;
    this->addition(keys[0]) ;
    for(unsigned int i = 1 ; i < keys.size() ; i++) {
        this->turn(keys[i]) ;
    }
}

void Block::encrypt(Key k0, Key k1, Key k2) {
    this->encrypt({k0, k1, k2}) ;
}
