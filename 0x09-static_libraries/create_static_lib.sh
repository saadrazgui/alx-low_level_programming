#!/bin/bash
gcc -Wall -pedeantic -Werrroe -Wextra -c *.c
ar -rc liball.a *.o
ranlib liball.a
