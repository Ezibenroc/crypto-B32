#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>
#include <stdlib.h>
#include <stdint.h>
#include <random>
#include <algorithm>    // std::min_element, std::max_element

#include "structures.h"
#include "clear_ciffers.h"

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

// Question 4
void experimentalCheck(uint32_t a=1, uint32_t b=5) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(0, UINT32_MAX);
    Block A(a<<28);
    Block B(b<<28);
    B.permutation() ;
    int nbMess = 1000000 ;
    for(int i = 0 ; i < 10 ; i++) {
        Block K0(dis(gen)) ;
        Block K1(dis(gen)) ;
        int nbEqual = 0 ;
        for(int j = 0 ; j < nbMess ; j++) {
            Block m(dis(gen)) ;
            Block x(m) ;
            x.addition(K0) ;
            x.turn(K1) ;
            m.product(A) ;
            x.product(B) ;
            if(m.bitsXor() == x.bitsXor())
                nbEqual ++ ;
        }
        std::cout << "$" << (double)nbEqual/(double)nbMess << "$ & ";//std::endl ;
    }
    std::cout << std::endl ;
}

int guessKeyBox(int blockIndex, uint32_t a=4, uint32_t b=8) {
    std::vector<int> keyCount(16, 0) ;
    Block A(a<<(blockIndex*4)) ;
    Block B(b<<(blockIndex*4)) ;
    B.permutation(2) ;
    for(unsigned int i = 0 ; i < Plaintext.size() ; i++) {
        Block M(Plaintext[i]) ;
        Block C(Ciphertext[i]) ;
        C.permutation(-2) ;
        for(uint32_t k = 0 ; k < 16 ; k++) {
            Block K(k<<(blockIndex*4)) ;
            K.addition(C) ;
            K.substitution(REVERSE_DEFAULT_SUBST) ;
            Block Mcopy(M) ;
            Mcopy.product(A) ;
            K.product(B) ;
            if(Mcopy.bitsXor() == K.bitsXor())
                keyCount[k] ++ ;
        }
    }
    int kmin = std::min_element(keyCount.begin(), keyCount.end()) - keyCount.begin();
    int kmax = std::max_element(keyCount.begin(), keyCount.end()) - keyCount.begin();
    if(std::abs((double)Plaintext.size()/2 - keyCount[kmin]) > std::abs((double)Plaintext.size()/2 - keyCount[kmax]))
        return kmin ;
    else
        return kmax ;
}

Block guessKey() {
    Block K(0) ;
    for(int i = 0 ; i < 8 ; i++) {
        K.setBox(i, guessKeyBox(i)) ;
    }
    K.permutation() ;
    return K ;
}

int main(int argc, char *argv[]) {
    // Question 3
    // if(argc != 2) {
    //     std::cerr << "Syntax:" << argv[0] << " <size of the S box>" << std::endl ;
    //     return 1 ;
    // }
    // int S = atoi(argv[1]) ;
    // int nbElt = 1<<S ;
    // linearApproximationMatrix(nbElt) ;

    // Question 4
    // if(argc != 3) {
    //     std::cerr << "Syntax:" << argv[0] << " <a> <b>" << std::endl ;
    //     return 1 ;
    // }
    // int a = atoi(argv[1]), b = atoi(argv[2]) ;
    // experimentalCheck(a, b) ;

    std::cout << guessKey().getBits() << std::endl ;
    return 0 ;
}
