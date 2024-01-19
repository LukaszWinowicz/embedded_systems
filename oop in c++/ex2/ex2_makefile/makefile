all: program

program: main.o message.o
	g++ -o program main.o message.o

main.o: main.cpp
	g++ -c main.cpp

message.o: message.cpp
	g++ -c message.cpp

clean:
	rm -f *.o program