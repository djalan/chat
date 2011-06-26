#include "groupe.h"
#include "listeUsager.h"
#include "listeGroupe.h"



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include <ctype.h>


int	sd;
int	connectlist[5];
fd_set	set_sockets;
int	highsock;



void setnonblocking (int sock) {
	int opts;

	opts = fcntl(sock,F_GETFL);
	if (opts < 0) {
		perror("fcntl(F_GETFL)");
		//exit(EXIT_FAILURE);
	}
	opts = (opts | O_NONBLOCK);
	if (fcntl(sock,F_SETFL,opts) < 0) {
		perror("fcntl(F_SETFL)");
		//exit(EXIT_FAILURE);
	}
}



void build_select_list() {

	FD_ZERO (&set_sockets);
	FD_SET (sd, &set_sockets);

	int i;
	for (i=0; i < 5; i++) {
		if (connectlist[i] != 0) {
			FD_SET (connectlist[i], &set_sockets);
			if (connectlist[i] > highsock)
				highsock = connectlist[i];
		}
	}
}



void handle_new_connection() {

	int nsd = accept (sd, NULL, NULL); // Ammad &FROM &L
	if (nsd < 0) {
		perror("accept");
		//exit(EXIT_FAILURE);
	}

	setnonblocking(nsd);

	int i, n;
	for (i = 0; (i < 5) && (nsd != -1); i ++)
		if (connectlist[i] == 0) {
			printf("Connection accepted: FD=%d; Slot=%d\n", nsd, i);
			connectlist[i] = nsd;
			nsd = -1;
			/*
			char okay[] = "Votre connexion a ete acceptee!";
			n = send (nsd, okay, strlen(okay)+1, 0);

			if (n < 0)

			{

				printf("Erreur lors de l'envoi de données !\n");

				//exit(1);

			}*/
		}

	if (nsd != -1) {
		printf("No room left for new client.\n");

		//sock_puts(nsd, "Sorry, this server is too busy. Try again later!\r\n");
		char occupe[] = "Desole, le serveur est trop occupee!";
		n = send (nsd, occupe, strlen(occupe)+1, 0);

		if (n < 0) {

			printf("Erreur lors de l'envoi de données !\n");

			//exit(1);

		}

		close(nsd);
	}
}



void deal_with_data (int pos) {
	char* cur_char;
	char buffer[256];
	int n;

	printf("Deal_with_data: FD=%d pos=%d\n", connectlist[pos], pos);
	n = recv (connectlist[pos], buffer, 256, 0);

	if (n < 0) {
		printf("Erreur lors de la reception de données !\n");
		close (connectlist[pos]);
		connectlist[pos] = 0;
		//exit(1);


	} else {
		printf("\nReceived: %s; ", buffer);
		//sprintf (buffer, "%s", "ALAIN");
		cur_char = buffer;
		while (cur_char[0] != 0) {
			cur_char[0] = toupper(cur_char[0]);
			cur_char++;
		}
		n = send (connectlist[pos], buffer, 256, 0);	
		//n = send (connectlist[pos], buffer, 256, 0);
		//if ( connectlist[0] == 4 && connectlist[1] == 5 )
		//	n = send (connectlist[0], buffer, 256, 0);

		if(n<0)	{

			printf("Erreur lors de l'envoi de données !\n");

			//exit(1);

		}
		printf("responded: %s\n", buffer);
	}
}



void lire_sockets() {

	if (FD_ISSET(sd, &set_sockets))
		handle_new_connection();

	int i;
	for (i=0; i < 5; i++) {
		if (FD_ISSET(connectlist[i], &set_sockets))
			deal_with_data(i);
	}
}



int main (int argc, char* argv[]) {

	
	if (argc < 2) {
		printf ("Usage: %s PORT\r\n",argv[0]);
		exit (EXIT_FAILURE);
	}
	

	
	struct sockaddr_in	server_address;
	struct timeval		timeout;
	int 			nbr_sockets_lus;
	
	
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	

	
	setnonblocking (sd);


	server_address.sin_family 	= AF_INET;
	server_address.sin_addr.s_addr	= INADDR_ANY;
	server_address.sin_port 	= htons(atoi(argv[1]));

	if (bind(sd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0 ) {
		perror("Erreur de bind\n");
		close (sd);
		exit (EXIT_FAILURE);
	}


	highsock = sd;
	memset( (char *) &connectlist, 0, sizeof(connectlist) );

	
	listen (sd, 5);

	while (1) {
		build_select_list();
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
			
		nbr_sockets_lus = select(highsock+1, &set_sockets, NULL, NULL, &timeout);
		
		if (nbr_sockets_lus < 0) {
			perror("Erreur de select\n");
			exit(EXIT_FAILURE);

		} else if (nbr_sockets_lus == 0) {
			printf("Rien a lire. Serveur en vie... FD0=%d FD1=%d FD2=%d FD3=%d FD4=%d\n", 
				connectlist[0],
				connectlist[1],
				connectlist[2],
				connectlist[3],
				connectlist[4]);
			fflush(stdout);
		} else {
			lire_sockets();
		}
	}

	close (sd);
	int i;
	for ( i=0; i<5; i++ ) {
		if ( connectlist[i] != 0 )
			close (connectlist[i]);
	}

	return 0;
}
