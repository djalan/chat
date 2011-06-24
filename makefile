CC = gcc
CFLAGS = -W -Wall -ggdb



all:		client.out server.out



OBJS_CLIENT = client.o fenetre.o chaine.o gui.o
OBJS_SERVER = server.o groupe.o usager.o info.o listeUsager.o listeGroupe.o



client.out:	$(OBJS_CLIENT)
	$(CC) $(CFLAGS) -l curses $(OBJS_CLIENT) -o client.out

client.o:	client.c fenetre.h chaine.h gui.h
	$(CC) $(CFLAGS) -c client.c

fenetre.o:	fenetre.c fenetre.h
	$(CC) $(CFLAGS) -c fenetre.c

chaine.o:	chaine.c chaine.h
	$(CC) $(CFLAGS) -c chaine.c

gui.o:		gui.c gui.h
	$(CC) $(CFLAGS) -c gui.c



server.out:	$(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o server.out

server.o:	server.c groupe.h usager.h info.h listeUsager.h listeGroupe.h
	$(CC) $(CFLAGS) -c server.c

groupe.o:	groupe.c groupe.h usager.h info.h
	$(CC) $(CFLAGS) -c groupe.c

usager.o:	usager.c usager.h
	$(CC) $(CFLAGS) -c usager.c

info.o:		info.c info.h
	$(CC) $(CFLAGS) -c info.c

listeUsager.o:	listeUsager.c listeUsager.h usager.h
	$(CC) $(CFLAGS) -c listeUsager.c

listeGroupe.o:	listeGroupe.c listeGroupe.h groupe.h
	$(CC) $(CFLAGS) -c listeGroupe.c

clean:
	rm *.o *~ *.nfs*



#############################
# Options qui ne marchent pas
#############################
# $(.SOURCE)
# $(.TARGET)
