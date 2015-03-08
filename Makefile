#######################################
# Makefile PBM                        #
#                                     #
# E.B.                                #
#######################################

# Variables pour la compilation des fichiers
CC        =  g++
CFLAGS    =  -g -Wall -Wextra -Werror -Wfatal-errors -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wfloat-equal -Wshadow -Wpointer-arith -Wstrict-aliasing # -pedantic
CPPFLAGS  =  -std=c++11
LDFLAGS   =  -g
UNITFLAGS = -lcppunit


all : main test report/report.pdf

%.o : %.cpp %.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

main: src/main.o src/structures.o
	$(CC) $(CFLAGS) -lboost_program_options -o $@ $^

test: tests/main.o tests/structures_tests.o src/structures.o
	$(CC) $(CFLAGS) $(UNITFLAGS) $^ -o $@

INDEXES=${report/report.tex}
OUT=${INDEXES:.tex=.pdf}

%.pdf : %.tex $(SRC)
		@(cd ${dir $<} && $(MAKE))

clean :
	rm -f *.o src/*.o tests/*.o report/report.pdf report/report.log report/report.aux report/report.out crypt test linearApproximationMatrix
