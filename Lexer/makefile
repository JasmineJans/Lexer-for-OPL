CC=g++
CFLAGS=-std=c++14 -g	# you can also use -std=c++11
			# or if you are on ada use -std=c++0x

all:	hw12

hw12:	exception.o token.o lexer.o parser.o hw12.o
	$(CC) exception.o token.o lexer.o parser.o hw12.o -o hw12

hw11:	exception.o token.o lexer.o hw11.o
	$(CC) exception.o token.o lexer.o hw11.o -o hw11

hw12.o:	hw12.cpp
	$(CC) $(CFLAGS) -c hw12.cpp

hw11.o:	hw11.cpp
	$(CC) $(CFLAGS) -c hw11.cpp

token.o:token.cpp
	$(CC) $(CFLAGS) -c token.cpp

lexer.o:lexer.cpp
	$(CC) $(CFLAGS) -c lexer.cpp

parser.o:parser.cpp
	$(CC) $(CFLAGS) -c parser.cpp

exception.o:exception.cpp
	$(CC) $(CFLAGS) -c exception.cpp

clean:
	rm *.o hw11 hw12
