#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        std::cerr << "Syntax:" << argv[0] << " <size of the S box>" << std::endl ;
        return 1 ;
    }
    std::vector<int> substitution = {7, 3, 6, 1, 13, 9, 10, 11, 2, 12, 0, 4, 5, 15, 8, 14} ;
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
                if((a^c) == (substitution[b]^c)) {
                    nbKey ++ ;
                }
            std::cout << nbKey ;
            if(b < nbElt-1)
                std::cout << " & " ;
        }
        std::cout << "\\cr\n" ;
    }
    std::cout << "}\n\\]";
    return 0 ;
}
