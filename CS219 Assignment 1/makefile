hexAdder: main.o number.o
	g++ -o hexAdder main.o number.o
main.o: main.cpp number.h
	g++ -c main.cpp
number.o: number.cpp number.h
	g++ -c number.cpp
clean: 
	rm *.o hexAdder