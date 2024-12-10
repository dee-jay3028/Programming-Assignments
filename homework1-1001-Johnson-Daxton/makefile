Transporters: person.o cargo.o helpers.o main.o
	g++ -o Transporters main.o person.o cargo.o helpers.o
helpers.o: helpers.cpp helpers.h bus.h train.h cargo.h person.h
	g++ -c helpers.cpp
person.o: person.cpp person.h
	g++ -c person.cpp
cargo.o: cargo.cpp cargo.h
	g++ -c cargo.cpp
main.o: main.cpp helpers.h transporter.h bus.h train.h
	g++ -c main.cpp
clean: 
	rm *.o Transporters