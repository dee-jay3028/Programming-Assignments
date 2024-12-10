bank_sim: driver.o event.o
	g++ -o bank_sim driver.o event.o
driver.o: driver.cpp arrayQueue.h priorityQueue.h
	g++ -c driver.cpp
event.o: event.cpp event.h
	g++ -c event.cpp
clean:
	rm *.o bank_sim