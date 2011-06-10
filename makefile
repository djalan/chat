CC = gcc
CFLAGS = -W -Wall -lcurses

all:		sept

sept:		sept.o

sept.o:		ex7.c


clean:
	rm *.o *~
