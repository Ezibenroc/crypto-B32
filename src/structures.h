#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <string>
#include <vector>

#define DEFAULT_SUBST {7, 3, 6, 1, 13, 9, 10, 11, 2, 12, 0, 4, 5, 15, 8, 14}
#define DEFAULT_SHIFT 2


// List of plaintexts and ciphertexts:
// http://perso.ens-lyon.fr/adeline.langlois/webpage/Crypto2014/clairs_chiffres.txt

class Key {
    protected:
        uint32_t bits ;
    public:
        Key(uint32_t b) ;
        uint32_t getBits(void) ;
        // Return the XOR of the bits of the key.
        int bitsXor(void) ;
};

class Block: public Key {
    public:
        Block(uint32_t b) ;
        // Bitwise AND
        void product(Key key) ;
        // Add the key to the bits (bitwise XOR)
        void addition(Key key) ;
        // Substitute the block of size 4 of the given position (according to the substitution subst).
        void substitution(int position, std::vector<int> subst = DEFAULT_SUBST) ;
        // Perform a substitution of the bits, by blocks of size 4 (according to the substitution subst).
        void substitution(std::vector<int> subst = DEFAULT_SUBST) ;
        // Perform a circular permutation on the right.
        void permutation(int shift = DEFAULT_SHIFT) ;
        // Perform a substitution and a permutation (with default values).
        // Then, add the key.
        void turn(Key k) ;
        // Perform the encryption with a vector of keys.
        void encrypt(std::vector<Key> keys) ;
        // Perform the encryption with 3 keys.
        void encrypt(Key k0, Key k1, Key k2) ;
        // Add the key.
        // Then perform a permutation and a substitution (with default values).
        void reverseTurn(Key k) ;
        // Perform the decryption with a vector of keys.
        void decrypt(std::vector<Key> keys) ;
        // Perform the decryption with 3 keys.
        void decrypt(Key k0, Key k1, Key k2) ;
};

std::vector<int> buildReverseSubstitution(std::vector<int> subst) ;

#endif
