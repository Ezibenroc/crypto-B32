#######################################
# Makefile PBM                        #
#                                     #
# E.B.                                #
#######################################


PROG = crypt

# Variables pour la compilation des fichiers
CC        =  g++
CFLAGS    =  -g -Wall -Wextra
CPPFLAGS  =  -std=c++11
LDFLAGS   =  -g

all : $(PROG)

%.o : %.cpp %.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(PROG): src/main.o src/structures.o
	$(CC) $(LDFLAGS) -o $@ $< src/structures.o


clean :
	rm -f *.o src/*.o $(PROG)
