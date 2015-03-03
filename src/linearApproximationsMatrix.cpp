#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

#include "structures.h"

#define abs(x) ((x)<0 ? -(x) : (x))

int op(int x) {
    int ret ;
    ret = x&1 ;
    x >>= 1 ;
    for(int i = 0 ; i < 31 ; i++) {
        ret ^= x&1 ;
        x >>= 1 ;
    }
    return ret ;
}

void check(void) {
    assert(op(0b1110101101)) ;
    assert(op(0b11100101100100)) ;
    assert(!op(0b11101101101)) ;
    assert(!op(0b111001011010100)) ;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Syntax:" << argv[0] << " <size of the S box>" << std::endl ;
        return 1 ;
    }
    std::vector<int> substitution = {7, 3, 6, 1, 13, 9, 10, 11, 2, 12, 0, 4, 5, 15, 8, 14} ;
    std::vector<std::pair<int,int>> goodKeys ;
    int S = atoi(argv[1]) ;
    int nbElt = 1<<S ;
    std::cout << "\\[\n\\bordermatrix{\n& " ;
    for(int b = 0 ; b < nbElt-1 ; b++) {
        std::cout << b << " & " ;
    }
    std::cout << nbElt-1 << "\\cr\n" ;
    for(int a = 0 ; a < nbElt ; a++) {
        std::cout << a << " & " ;
        for(int b = 0 ; b < nbElt ; b++) {
            int nbKey = 0 ;
            for(int c = 0 ; c < nbElt ; c++)
                if(op(a&c) == op(b&substitution[c])) {
                    nbKey ++ ;
                }
            std::cout << nbKey ;
            double proba = ((double)nbKey)/16 ;
            if(abs(proba - 0.5) > 0.3) {
                // std::cout << nbKey ;
                goodKeys.push_back(std::pair<int,int>(a, b)) ;
            }
            if(b < nbElt-1)
                std::cout << " & " ;
        }
        std::cout << "\\cr\n" ;
    }
    std::cout << "}\n\\]\n";
    std::cout << "Couples (a, b) with the highest probability:\n\\[" ;
    if(goodKeys.size() > 0)
        std::cout << "(" << goodKeys[0].first << ", " << goodKeys[0].second << ")" ;
    for(unsigned i = 1 ; i < goodKeys.size() ; i++) {
        std::cout << ", (" << goodKeys[i].first << ", " << goodKeys[i].second << ")" ;
    }
    std::cout << "\\]\n" ;
    return 0 ;
}
