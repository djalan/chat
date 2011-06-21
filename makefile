CC = gcc
CFLAGS = -W -Wall -ggdb



all:		client.out



OBJS_CLIENT = client.o fenetre.o chaine.o

client.out:	$(OBJS_CLIENT)
	$(CC) $(CFLAGS) -l curses $(OBJS_CLIENT) -o client.out

client.o:	client.c fenetre.h chaine.h
	$(CC) $(CFLAGS) -c client.c

fenetre.o:	fenetre.c fenetre.h
	$(CC) $(CFLAGS) -c fenetre.c

chaine.o:	chaine.c chaine.h
	$(CC) $(CFLAGS) -c chaine.c



clean:
	rm *.o *~



#############################
# Options qui ne marchent pas
#############################
# $(.SOURCE)
# $(.TARGET)
