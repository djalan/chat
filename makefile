CC = gcc
CFLAGS = -W -Wall



all:		gui.out



OBJS_GUI = gui.o fenetre.o
gui.out:	$(OBJS_GUI)
	$(CC) $(CFLAGS) -l curses $(OBJS_GUI) -o gui.out
gui.o:		gui.c fenetre.h
	$(CC) $(CFLAGS) -c gui.c
fenetre.o:	fenetre.c fenetre.h
	$(CC) $(CFLAGS) -c fenetre.c



clean:
	rm *.o *~


#############################
# Options qui ne marchent pas
#############################
# $(.SOURCE)
# $(.TARGET)
