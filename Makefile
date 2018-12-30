target: algorithm.o
	g++ algorithm.o -o algorithm
algorithm.o:	algorithm.cpp algorithm.h
	g++ -c algorithm.cpp
clean:
	rm *.o
