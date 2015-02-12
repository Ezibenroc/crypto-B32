/* Utilitaires de lecture pour les fichiers PBM, PGM, PPM
 * E.B.  12/98
 */

#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <string>
#include <vector>

#define DEFAULT_SUBST {7, 3, 6, 1, 13, 9, 10, 11, 2, 12, 0, 4, 5, 15, 8, 14}

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
        void addition(Key key) ;
        void substitution(int position, std::vector<int> subst = DEFAULT_SUBST) ;
        void substitution(std::vector<int> subst = DEFAULT_SUBST) ;
        void permutation(int shift = 2) ;
};

#endif
