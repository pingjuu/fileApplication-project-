all: fileprocess

fileprocess: fileprocess.o person.o
	g++ -o fileprocess fileprocess.o person.o

fileprocess.o: fileprocess.cpp person.h
	g++ -c -o fileprocess.o fileprocess.cpp

person.o: person.cpp person.h
	g++ -c -o person.o person.cpp

clean:
	rm -f fileprocess *.o