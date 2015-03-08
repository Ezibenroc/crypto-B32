#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <string>
#include <vector>

#define DEFAULT_SUBST {7, 3, 6, 1, 13, 9, 10, 11, 2, 12, 0, 4, 5, 15, 8, 14}
#define REVERSE_DEFAULT_SUBST {10, 3, 8, 1, 11, 12, 2, 0, 14, 5, 6, 7, 9, 4, 15, 13}
#define DEFAULT_SHIFT 2

#define DEFAULT_K0_SUBST {17, 31, 0, 0, 18, 7, 20, 18, 8, 1, 27, 27, 2, 4, 11,\
    20, 25, 13, 17, 10, 24, 9, 29, 15, 21, 18, 28, 20, 4, 5, 24, 15}
#define DEFAULT_K1_SUBST {15, 2, 5, 0, 13, 31, 5, 10, 18, 2, 3, 14, 14, 0, 11,\
    1, 20, 15, 14, 27, 6, 11, 19, 3, 6, 20, 14, 2, 28, 11, 5, 8}
#define DEFAULT_K2_SUBST {4, 24, 23, 12, 22, 21, 31, 15, 29, 1, 0, 26, 17, 24,\
    16, 5, 31, 0, 20, 21, 26, 30, 15, 11, 16, 23, 18, 30, 30, 19, 28, 23}


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
