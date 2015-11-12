CC	=	g++	
DEBUG	=	-g -O0 -pedantic-errors	
CFLAGS	=	-Wall -std=c++11 -c $(DEBUG)	
LFLAGS	=	-Wall $(DEBUG)	

all: socketserv socketcli

socketserv: socketserv.o
	$(CC) $(LFLAGS) -o socketserv socketserv.o

socketserv.o: socketserv.cpp
	$(CC) $(CFLAGS) socketserv.cpp

socketcli: socketcli.o
	$(CC) $(LFLAGS) -o socketcli socketcli.o

socketcli.o: socketcli.cpp
	$(CC) $(CFLAGS) socketcli.cpp

.PHONY: clean

clean:
	rm -rf lab12
	rm -rf *.o