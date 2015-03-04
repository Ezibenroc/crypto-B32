#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>

#include "structures.h"

// Questions 2 and 3
void linearApproximationMatrix(int nbElt) {
    std::vector<std::pair<int,int>> goodKeys ;
    std::cout << "\\[\n\\bordermatrix{\n& " ;
    for(int b = 0 ; b < nbElt-1 ; b++) {
        std::cout << b << " & " ;
    }
    std::cout << nbElt-1 << "\\cr\n" ;
    for(int a = 0 ; a < nbElt ; a++) {
        std::cout << a << " & " ;
        for(int b = 0 ; b < nbElt ; b++) {
            int nbKey = 0 ;
            for(int c = 0 ; c < nbElt ; c++) {
                Block blockA(a) ;
                Block blockB(b) ;
                Block key(c) ;
                blockA.product(key) ;
                key.substitution() ;
                blockB.product(key) ;
                if(blockA.bitsXor() == blockB.bitsXor()) {
                    nbKey ++ ;
                }
            }
            std::cout << nbKey ;
            double proba = ((double)nbKey)/16 ;
            if(std::abs(proba - 0.5) > 0.3) {
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
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Syntax:" << argv[0] << " <size of the S box>" << std::endl ;
        return 1 ;
    }
    int S = atoi(argv[1]) ;
    int nbElt = 1<<S ;
    linearApproximationMatrix(nbElt) ;
    return 0 ;
}
