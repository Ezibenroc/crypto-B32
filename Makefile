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
CFLAGS    =  -g -Wall -Wextra
CPPFLAGS  =  -std=c++11
LDFLAGS   =  -g
UNITFLAGS = -lcppunit


all : $(PROG)

%.o : %.cpp %.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(PROG): src/main.o src/structures.o
	$(CC) $(LDFLAGS) -o $@ $< src/structures.o

$(APPROX): src/linearApproximationsMatrix.o
	$(CC) $(LDFLAGS) -o $@ $<

$(TEST): tests/main.o tests/structures_tests.o src/structures.o
	$(CC) $(LDFLAGS) $(UNITFLAGS) $^ -o $@

clean :
	rm -f *.o src/*.o tests/*.o $(PROG) $(TEST) $(APPROX)
