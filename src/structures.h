#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <string>
#include <vector>

#define DEFAULT_SUBST {7, 3, 6, 1, 13, 9, 10, 11, 2, 12, 0, 4, 5, 15, 8, 14}

// List of plaintexts and ciphertexts:
// http://perso.ens-lyon.fr/adeline.langlois/webpage/Crypto2014/clairs_chiffres.txt

class Key {
    protected:
        uint32_t bits ;
    public:
        explicit Key(uint32_t b) ;
        uint32_t getBits(void) ;
};

class Block: public Key {
    public:
        explicit Block(uint32_t b) ;
        // Add the key to the bits (bitwise XOR)
        void addition(Key key) ;
        // Substitute the block of size 4 of the given position (according to the substitution subst).
        void substitution(int position, std::vector<int> subst = DEFAULT_SUBST) ;
        // Perform a substitution of the bits, by blocks of size 4 (according to the substitution subst).
        void substitution(std::vector<int> subst = DEFAULT_SUBST) ;
        // Perform a circular permutation on the right.
        void permutation(int shift = 2) ;
        // Perform a substitution and a permutation (with default values).
        // Then, add the key.
        void turn(Key k) ;
        // Perform the encryption with a vector of keys.
        void encrypt(std::vector<Key> keys) ;
        // Perform the encryption with 3 keys.
        void encrypt(Key k0, Key k1, Key k2) ;
};

std::vector<int> buildReverseSubstitution(std::vector<int> subst) ;

#endif
