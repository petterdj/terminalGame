CC = g++
CFLAGS = -std=c++0x -Wall -g
LDFLAGS=-lncurses

default: hello
#	chmod +x main.o

hello: main.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o $(LDFLAGS)

clean:
	rm *.o
