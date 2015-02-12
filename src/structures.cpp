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
