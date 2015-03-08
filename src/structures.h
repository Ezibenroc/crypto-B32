#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <string>
#include <vector>

#define DEFAULT_SUBST {7, 3, 6, 1, 13, 9, 10, 11, 2, 12, 0, 4, 5, 15, 8, 14}
#define REVERSE_DEFAULT_SUBST {10, 3, 8, 1, 11, 12, 2, 0, 14, 5, 6, 7, 9, 4, 15, 13}
#define DEFAULT_SHIFT 2

/*
    Remark: the tabs of the subject were in big endian convention.
    They are translated here in little endian convention.
*/
#define DEFAULT_K0_SUBST {15, 24, 5, 4, 20, 28, 18, 21, 15, 29, 9, 24, 10, 17, 13,\
    25, 20, 11, 4, 2, 27, 27, 1, 8, 18, 20, 7, 18, 0, 0, 31, 17}
#define DEFAULT_K1_SUBST {8, 5, 11, 28, 2, 14, 20, 6, 3, 19, 11, 6, 27, 14, 15, 20,\
    1, 11, 0, 14, 14, 3, 2, 18, 10, 5, 31, 13, 0, 5, 2, 15}
#define DEFAULT_K2_SUBST {2, 28, 19, 30, 30, 18, 23, 16, 11, 15, 30, 26, 21, 20, 0,\
    31, 5, 16, 24, 17, 26, 0, 1, 29, 15, 31, 21, 22, 12, 23, 24, 43}


// List of plaintexts and ciphertexts:
// http://perso.ens-lyon.fr/adeline.langlois/webpage/Crypto2014/clairs_chiffres.txt

class Block {
    private:
        uint32_t bits ;
    public:
        Block(void) ;
        Block(uint32_t b) ;
        Block(const Block &other) ;
        Block(const std::vector<int> b) ;
        uint32_t getBits(void) const ;
        // Return the XOR of the bits of the block.
        int bitsXor(void) ;
        // Bitwise AND
        void product(Block other) ;
        // Bitwise XOR)
        void addition(Block other) ;
        // Get the bits of the box.
        int getBox(int boxID, int boxSize=4) ;
        // Set the bits of the box.
        void setBox(int boxID, int box, int boxSize=4) ;
        // Substitute the block of size 4 of the given position (according to the substitution subst).
        void substitution(int position, std::vector<int> subst = DEFAULT_SUBST) ;
        // Perform a substitution of the bits, by blocks of size 4 (according to the substitution subst).
        void substitution(std::vector<int> subst = DEFAULT_SUBST) ;
        // Perform a circular permutation on the right.
        void permutation(int shift = DEFAULT_SHIFT) ;
        // Perform a substitution and a permutation (with default values).
        // Then, add the key.
        void turn(Block k) ;
        // Perform the encryption with a vector of keys.
        void encrypt(std::vector<Block> keys) ;
        // Perform the encryption with 3 keys.
        void encrypt(Block k0, Block k1, Block k2) ;
        // Add the key.
        // Then perform a permutation and a substitution (with default values).
        void reverseTurn(Block k) ;
        // Perform the decryption with a vector of keys.
        void decrypt(std::vector<Block> keys) ;
        // Perform the decryption with 3 keys.
        void decrypt(Block k0, Block k1, Block k2) ;
        // Generate the keys K0, K1, K2 with the key K and the substitution vectors.
        void generateSubKeys(Block *K, std::vector<int> Subst);
        void generateSubKeys(Block *K0, Block *K1, Block *K2,\
            std::vector<int> K0Subst = DEFAULT_K0_SUBST,\
            std::vector<int> K1Subst = DEFAULT_K1_SUBST,\
            std::vector<int> K2Subst = DEFAULT_K2_SUBST\
        );
};

std::vector<int> buildReverseSubstitution(std::vector<int> subst) ;

#endif
