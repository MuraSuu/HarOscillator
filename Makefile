CC = g++
CCFLAGS = -Wall -Wextra -Wpedantic -O1
GFLAGS = -Wall -Wextra -Wpedantic -Og -g
LFLAGS = -lgsl -lgslcblas -lm

default: error

error: error.cc
	$(CC) error.cc $(CCFLAGS) $(LFLAGS) -o error.o

phase: phase.cc
	$(CC) phase.cc $(CCFLAGS) $(LFLAGS) -o phase.o