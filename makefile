#Wheel of Lies Makefile
CC = g++
CFLAGS = -g -Wall

#Special Default Dependency
all:AVLTest

#dependencies
AVLTest:AVLTest.o
	$(CC) $(CFLAGS) -o AVLTest AVLTest.o

AVLTest.o:AVLTest.cpp LCMap.h
	$(CC) $(CFLAGS) -c AVLTest.cpp

clean:
	rm -f AVLTest *.o *.~ *.gch
