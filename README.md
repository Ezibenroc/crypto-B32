# About

This repository is a [homerowk](TP.pdf) whose aim was to build an attack against the block cipher B32 (described by Bart Preneel and Lars Knudsen).

It consists of a theoretical study (see the report) and an implementation (see the program).

# Setup

Compile the report:
```
make report/report.pdf
```

Compile and run the tests:
```
make test
./test
```

Compile the main program:
```
make main
```

# Use the program

Display the linear approximation matrix:
```
./main --linearApproximationMatrix
```

Display the experimental results:
```
./main --experimentalCheck
```

Find the key with a brute force attack (depreciated, way too long):
```
./main --bruteForce
```

Find the key with the active boxes attack:
```
./main --activeBox
```
