calculator: driver.o 
	g++ driver.o -o calculator

driver.o: driver.cpp linkedStack.h node.h arrayStack.h
	g++ -c driver.cpp

clean: 
	rm *.o calculator