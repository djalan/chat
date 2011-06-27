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



struct commande {
        char**  chaine;
        int     nbrToken;
        int     nsd;
};

struct commande	cmd;
int		sd;
int		connectlist[5];
fd_set		set_sockets;
int		highsock;



void decomposer_commande (char buffer[1024]) {

        char    copie[1024];
        char*   pch;

        sprintf (copie, "%s", buffer);

        int nbrToken = 0;
        cmd.chaine = (char**) malloc (1 * sizeof(char*));

        pch = strtok (copie, " ");
        while (pch != NULL) {
                nbrToken++;

                cmd.chaine = (char**) realloc (cmd.chaine, (nbrToken * sizeof(char*)) );
                cmd.chaine[nbrToken-1] = (char*) malloc ( ((int)strlen(pch)+1) * sizeof(char));
                sprintf (cmd.chaine[nbrToken-1], "%s", pch);

                pch = strtok (NULL, " ");
        }

        cmd.nbrToken = nbrToken;
}



void setnonblocking (int sock) {

	int opts = fcntl(sock,F_GETFL);

	if (opts < 0) {
		perror("Erreur: fcntl(F_GETFL)");

	} else {
		opts = (opts | O_NONBLOCK);
		if (fcntl(sock,F_SETFL,opts) < 0)
			perror("Erreur fcntl(F_SETFL)");
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

	int nsd = accept (sd, NULL, NULL);
	if (nsd < 0) {
		perror("Erreur lors du accept sur la listening socket sd!");
	}

	setnonblocking(nsd);

	int i, n;
	for (i = 0; (i < 5) && (nsd != -1); i ++)
		if (connectlist[i] == 0) {
			printf("Nouvelle connexion acceptee: FD=%d; Slot=%d\n", nsd, i);
			connectlist[i] = nsd;
			nsd = -1;
		}

	if (nsd != -1) {
		char occupe[] = "Desole, le serveur est trop occupee!";
		printf("%s\n", occupe);

		n = send (nsd, occupe, ((int)strlen(occupe)+1), 0);
		if (n < 0) {
			printf("Erreur lors de l'envoi de données pour dire que le serveur est trop occupe!\n");
		}

		close(nsd);
	}
}



char*  slash_nom() {

	if ( cmd.nbrToken != 2 )
		return "Erreur! Usage: /nom nom_usager";

	if ( listeUsagerContient(cmd.chaine[1]) )
		return "Erreur! Le nom est deja utilise par une autre personne!";

	Usager nouveau = creerUsager (cmd.chaine[1], cmd.nsd);
	listeUsagerAjouter (nouveau);
	return "Votre nom est accepte!";
}



char*  slash_mp() {}



char*  slash_mg() {}



char*  slash_quitter (int pos) {
	close (cmd.nsd);
	connectlist[pos] = 0;
}



char*  slash_creerGroupe() {

	if ( cmd.nbrToken != 3 )
		return "Erreur! Usage: /creerGroupe nom type";

	if ( strcmp(cmd.chaine[2],"public") && strcmp(cmd.chaine[2],"prive") )
		return "Erreur! Le type de groupe est 'prive' ou 'public'";

	if ( listeGroupeContient(cmd.chaine[1]) )
		return "Erreur! Un groupe de ce nom est deja cree!";

	Usager responsable = listeUsagerElement( listeUsagerTrouverNom(cmd.nsd) );
	Groupe groupe = creerGroupe (cmd.chaine[1], cmd.chaine[2], responsable);
	listeGroupeAjouter (groupe);
	return "Votre groupe a ete cree!";
}



char*  slash_joindreGroupe() {}



char*  slash_quitterGroupe() {}



char*  slash_listeUsagers() {}



char*  slash_listeGroupes() {}



char*  slash_infoGroupe() {

	if ( cmd.nbrToken != 2 )
		return "Erreur! Usage: /infoGroupe nom";

	if ( ! listeGroupeContient(cmd.chaine[1]) )
		return "Erreur! Il n'y a pas de groupe de ce nom!";

	return groupeInfoToString ( listeGroupeElement(cmd.chaine[1]) );
}




void deal_with_data (int pos) {
	char buffer[1024];
	int n;
	int nsd = connectlist[pos];

	printf("Deal_with_data: FD=%d pos=%d\n", nsd, pos);

	n = recv (nsd, buffer, 1024, 0);
	if (n < 0) {
		printf("Erreur lors de la reception de données !\n");
		close (nsd);
		connectlist[pos] = 0;


	} else {
		printf("Chaine recue: %s\n", buffer);

		decomposer_commande (buffer);
		cmd.nsd = nsd;

		printf("Commande: %s\n", cmd.chaine[0]);
		
		if ( !strcmp(cmd.chaine[0], "/nom") ) {
			sprintf( buffer, "%s", slash_nom());
		} else if ( !strcmp(cmd.chaine[0], "/mp") ) {
			sprintf( buffer, "%s", slash_mp());
		} else if ( !strcmp(cmd.chaine[0], "/mg") ) {
			sprintf( buffer, "%s", slash_mg());
		} else if ( !strcmp(cmd.chaine[0], "/quitter") ) {
			sprintf( buffer, "%s", slash_quitter(pos));
		} else if ( !strcmp(cmd.chaine[0], "/creerGroupe") ) {
			sprintf( buffer, "%s", slash_creerGroupe());
		} else if ( !strcmp(cmd.chaine[0], "/joindreGroupe") ) {
			sprintf( buffer, "%s", slash_joindreGroupe());
		} else if ( !strcmp(cmd.chaine[0], "/quitterGroupe") ) {
			sprintf( buffer, "%s", slash_quitterGroupe());
		} else if ( !strcmp(cmd.chaine[0], "/listeUsagers") ) {
			sprintf( buffer, "%s", slash_listeUsagers());
		} else if ( !strcmp(cmd.chaine[0], "/listeGroupes") ) {
			sprintf( buffer, "%s", slash_listeGroupes());
		} else if ( !strcmp(cmd.chaine[0], "/infoGroupe") ) {
			sprintf( buffer, "%s", slash_infoGroupe());
		} else {
			sprintf (buffer, "Commande non supportee!");
		}

		n = send (nsd, buffer, 1024, 0);	
		if(n<0)	{
			printf("Erreur lors de l'envoi de la reponse au client!\n");
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
