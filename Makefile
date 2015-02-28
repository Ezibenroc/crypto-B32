#######################################
# Makefile PBM                        #
#                                     #
# E.B.                                #
#######################################


PROG = crypt
TEST = test
APPROX = linearApproximationMatrix

# Variables pour la compilation des fichiers
CC        =  g++
CFLAGS    =  -g -Wall -Wextra -Werror -Wfatal-errors -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wfloat-equal -Wshadow -Wpointer-arith -Wstrict-aliasing # -pedantic
CPPFLAGS  =  -std=c++11
LDFLAGS   =  -g
UNITFLAGS = -lcppunit


all : $(PROG)

%.o : %.cpp %.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(PROG): src/main.o src/structures.o
	$(CC) $(CFLAGS) -o $@ $< src/structures.o

$(APPROX): src/linearApproximationsMatrix.o
	$(CC) $(CFLAGS) -o $@ $<

$(TEST): tests/main.o tests/structures_tests.o src/structures.o
	$(CC) $(CFLAGS) $(UNITFLAGS) $^ -o $@

INDEXES=${report/report.tex}
OUT=${INDEXES:.tex=.pdf}

%.pdf : %.tex $(SRC)
		@(cd ${dir $<} && $(MAKE))

clean :
	rm -f *.o src/*.o tests/*.o $(PROG) $(TEST) $(APPROX)
