#include "groupe.h"
#include "listeUsager.h"
#include "listeGroupe.h"
#include "config.h"


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
#include <signal.h>



struct commande {
        char**  chaine;
        int     nbrToken;
        int     nsd;
};

struct commande	cmd;
int		sd;
int		connectlist[MAX_USAGERS];
fd_set		set_sockets;
int		highsock;



void decomposer_commande (char buffer[BUF_SIZE]) {
	char	copie[BUF_SIZE];
	sprintf (copie, "%s", buffer);

	cmd.chaine = (char**) malloc (1 * sizeof(char*));

	int nbrToken = 0;	
	int l = 0;
	int pos = 0;

	char*	pch;
	pch = strtok (copie, " ");
	while (pch != NULL) {
		nbrToken++;
		cmd.chaine = (char**) realloc (cmd.chaine, (nbrToken * sizeof(char*)) );

		if ( nbrToken < 3 ) {
			l = (int) strlen (pch);
			pos = pos + l + 1;

			cmd.chaine[nbrToken-1] = (char*) malloc ( (l + 1) * sizeof(char));
			sprintf (cmd.chaine[nbrToken-1], "%s", pch);

		} else {
			cmd.chaine[nbrToken-1] = (char*) malloc ( ((int)strlen(&buffer[pos])+1) * sizeof(char));
			sprintf (cmd.chaine[nbrToken-1], "%s", &buffer[pos]);
			break;
		}	

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
	for (i=0; i < MAX_USAGERS; i++) {
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
	for (i = 0; (i < MAX_USAGERS) && (nsd != -1); i ++)
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



char*  slash_mp() {

	printf ("L'usager %s veut envoyer un /mp...\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 3 )
		return "Erreur! Usage: /mp usager votre message ici";

	if ( ! listeUsagerContient(cmd.chaine[1]) )
		return "Erreur! Cet usager n'existe pas!";

	char* buffer = (char*) malloc (BUF_SIZE * sizeof(char));
	sprintf (buffer, "%s -> %s: %s", listeUsagerTrouverNom(cmd.nsd), cmd.chaine[1], cmd.chaine[2] );

	int sd_dest = listeUsagerTrouverNsd (cmd.chaine[1]);
	int n = send (sd_dest, buffer, BUF_SIZE, 0);	
	if ( n < 0 )	{
		char erreur[] = "Erreur lors de l'envoi du message /mp au destinataire!";
		printf ("%s", erreur);
		sprintf (buffer, "%s", erreur);	
	}
	return buffer;
}



char*  slash_mg() {
	printf ("L'usager %s veut envoyer un /mg...\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 3 )
		return "Erreur! Usage: /mg groupe votre message ici";

	if ( ! listeGroupeContient(cmd.chaine[1]) )
		return "Erreur! Ce groupe n'existe pas!";

	Groupe unGroupe = listeGroupeElement (cmd.chaine[1]);
	char* nom_usager = listeUsagerTrouverNom(cmd.nsd);

	if ( !groupeContientMembre(unGroupe, nom_usager) && !listeGroupeEstMembrePrive(nom_usager) )
		return "Erreur! Vous ne pouvez pas envoyer un message a ce groupe!";

	char* buffer = (char*) malloc (BUF_SIZE * sizeof(char));
	sprintf (buffer, "%s -> %s: %s", nom_usager, cmd.chaine[1], cmd.chaine[2]);
	int nbrMembres = donnerNbrMembres (unGroupe);
	int i, nsd, n;
	for ( i=0; i < nbrMembres; i++ ) {
		nsd = donnerUsagerNsd (donnerMembres(unGroupe)[i]);
		char* nom_membre = donnerUsagerNom (donnerMembres(unGroupe)[i]);
		if ( strcmp(nom_usager, nom_membre) ) {
			n = send (nsd, buffer, BUF_SIZE, 0);
			if ( n < 0 )	{
				char erreur[] = "Erreur lors de l'envoi du message a un usager du groupe!";
				printf ("%s", erreur);
			}
		}
	}

	if ( groupeContientMembre(unGroupe, nom_usager) )
		groupeAugmenterInterventions (unGroupe, nom_usager);

	return buffer;
}



char*  slash_quitter (int pos) {
	printf ("L'usager %s veut quitter...\n", listeUsagerTrouverNom(cmd.nsd) );

	char* nom_usager = listeUsagerTrouverNom(cmd.nsd);
	int i;
	int nbrGroupes = listeGroupeTaille();
	Groupe groupe;
	Usager responsable;
	for ( i=0; i < nbrGroupes; i++) {
		groupe = listeGroupeObtenir(i);
		responsable = donnerResponsable (groupe);
		if ( groupeContientMembre(groupe, nom_usager) ) {
			if ( strcmp(nom_usager, donnerUsagerNom(responsable)) ) {
				groupeEnleverMembre (groupe, nom_usager);
				groupeDepartInfo (groupe, nom_usager);
				printf ("L'usager %s a quitte le groupe %s\n", nom_usager, donnerGroupeNom(groupe));
			}
		}
	}
	

	if ( listeGroupeEstResponsable(nom_usager) )
		return "Vous ne pouvez pas quitter! Vous etes encore responsable d'un groupe.";

	connectlist[pos] = 0;

	if ( listeUsagerTaille() > 0 ) {
		printf ("Liste usagers avant:%s\n", listeUsagerToString() );
		listeUsagerEnlever (nom_usager);
		printf ("Liste usagers apres:%s\n", listeUsagerToString() );
	}

	return "Fermeture de la connexion client......";
}



char*  slash_creerGroupe() {
	printf ("L'usager %s veut creer un groupe...\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 3 )
		return "Erreur! Usage: /creer groupe type";

	if ( strcmp(cmd.chaine[2],"public") && strcmp(cmd.chaine[2],"prive") )
		return "Erreur! Le type de groupe est 'prive' ou 'public'";

	if ( listeGroupeContient(cmd.chaine[1]) )
		return "Erreur! Un groupe de ce nom est deja cree!";

	Usager responsable = listeUsagerElement( listeUsagerTrouverNom(cmd.nsd) );
	printf ("Groupe %s cree! Nom du responsable = %s\n", cmd.chaine[1], donnerUsagerNom(responsable));
	Groupe groupe = creerGroupe (cmd.chaine[1], cmd.chaine[2], responsable);
	listeGroupeAjouter (groupe);
	printf ("Nombre de groupes = %d\n", listeGroupeTaille() );
	return "Votre groupe a ete cree!";
}



char*  slash_joindreGroupe() {
	printf ("L'usager %s veut joindre un groupe...\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 2 )
		return "Erreur! Usage: /joindre groupe";

	if ( ! listeGroupeContient(cmd.chaine[1]) )
		return "Erreur! Ce groupe n'existe pas";

	Groupe unGroupe = listeGroupeElement (cmd.chaine[1]);
	char* nom = listeUsagerTrouverNom(cmd.nsd);
	Usager unUsager = listeUsagerElement (nom);

	printf ("%s veut joindre le groupe %s\n", nom, cmd.chaine[1]);
	
	if ( ! strcmp("public", donnerGroupeType(unGroupe)) ) {
		groupeAjouterMembre (unGroupe, unUsager);

		if ( groupeContientInfo(unGroupe,nom) ) {
			groupeReinitialiserInfo (unGroupe, nom);
		} else {
			groupeAjouterInfo (unGroupe, nom);
		}
		return "Vous avez joint le groupe";
	}

	// prive
	groupeAjouterDemande (unGroupe, unUsager);

	char* buffer = (char*) malloc (BUF_SIZE * sizeof(char));
	sprintf (buffer, "%s a envoye une demande pour joindre le groupe %s", nom, cmd.chaine[1] );
	Usager responsable = donnerResponsable (unGroupe);
	int sd_dest = donnerUsagerNsd (responsable);
	int n = send (sd_dest, buffer, BUF_SIZE, 0);

	sprintf (buffer, "Svp attendre que le responsable approuve votre demande");
	if ( n < 0 ) {
		char erreur[] = "Le responsable n'a pas recu l'avis mais la demande a ete envoyee";
		printf ("%s", erreur);
		sprintf (buffer, "%s", erreur);
	}
	return buffer;
}



char*  slash_byebyeGroupe() {
	printf ("L'usager %s veut quitter un groupe...\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 2 )
		return "Erreur! Usage: /byebye groupe";

	if ( ! listeGroupeContient(cmd.chaine[1]) )
		return "Erreur! Ce groupe n'existe pas";

	Groupe unGroupe = listeGroupeElement (cmd.chaine[1]);
	char* nom = (char*) malloc ( ((int) strlen(listeUsagerTrouverNom(cmd.nsd)) + 1) * sizeof(char));
	sprintf (nom, "%s", listeUsagerTrouverNom(cmd.nsd));

	if ( ! groupeContientMembre(unGroupe, nom) )
		return "Erreur! Vous ne faites pas partie de ce groupe!";

	Usager responsable = donnerResponsable (unGroupe);
	int nbrMembres = donnerNbrMembres (unGroupe);

	if ( (!strcmp(nom, donnerUsagerNom(responsable))) && (nbrMembres > 1) )
		return "Impossible de quitter! Vous etes le responsable et il reste d'autres membres!";

	groupeEnleverMembre (unGroupe, nom);
	groupeDepartInfo (unGroupe, nom);

	int nbrMembresApres = donnerNbrMembres (unGroupe);
	if ( nbrMembresApres == 0 ) {
		listeGroupeEnlever (donnerGroupeNom(unGroupe));
		return "Vous avez quitte le groupe et il est maintenant ferme!";
	}
		
	return "Vous avez quitter le groupe";
}



char*  slash_liste() {
	printf ("L'usager %s veut une liste...\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 2 )
		return "Erreur! Usager: /liste [usagers|groupes]";

	if ( strcmp(cmd.chaine[1],"usagers") && strcmp(cmd.chaine[1],"groupes") )
		return "Erreur! Usager: /liste [usagers|groupes]";


	char* reponse = (char*) malloc (BUF_SIZE * sizeof(char));

	if ( ! strcmp(cmd.chaine[1], "usagers") ) {
		if ( listeUsagerTaille() == 0 ) {
			return "Il n'y a aucun nom d'usager pris encore!";
		} else {
			sprintf (reponse, "Liste des usagers: %s", listeUsagerToString() );
		}
	

	} else if ( ! strcmp(cmd.chaine[1], "groupes") ) {
		if ( listeGroupeTaille() == 0 ) {
			return "Il n'y a aucun groupe de cree encore!";
		} else {
			sprintf (reponse, "Liste des groupes: %s", listeGroupeToString() );
		}
	}

	return reponse;
}



char*  slash_statsGroupe() {
	printf ("L'usager %s veut les stats d'un groupe..\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 2 )
		return "Erreur! Usage: /infoGroupe nom";

	if ( ! listeGroupeContient(cmd.chaine[1]) )
		return "Erreur! Il n'y a pas de groupe de ce nom!";

	return groupeInfoToString ( listeGroupeElement(cmd.chaine[1]) );
}



char*  slash_info() {
	printf ("L'usager %s veut les infos d'un groupe..\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 2 )
		return "Erreur! Usage: /membres groupe";

	if ( ! listeGroupeContient(cmd.chaine[1]) )
		return "Erreur! Il n'y a pas de groupe de ce nom!";

	Groupe groupe = listeGroupeElement(cmd.chaine[1]);
	char* reponse = (char*) malloc (BUF_SIZE * sizeof(char));
	sprintf (reponse, "Responsable: %s\nMembres:     %s\nDemandes:    %s", donnerUsagerNom(donnerResponsable(groupe)), groupeMembresToString(groupe), groupeDemandesToString(groupe) );

	return reponse;
}



char*	slash_accept() {
	printf ("L'usager %s veut approuver une demande..\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 3 )
		return "Erreur! Usage: /accept usager groupe";

	if ( ! listeGroupeContient(cmd.chaine[2]) )
		return "Erreur! Il n'y a pas de groupe de ce nom!";

	Groupe groupe = listeGroupeElement (cmd.chaine[2]);
	if ( ! groupeContientDemande(groupe, cmd.chaine[1]) )
		return "Erreur! Aucune demande pour cet usager pour ce groupe!";

	if ( strcmp(listeUsagerTrouverNom(cmd.nsd), donnerUsagerNom(donnerResponsable(groupe))) )
		return "Vous n'etes pas le responsable de ce groupe!";

	Usager usager = groupeEnleverDemande (groupe, cmd.chaine[1]);
	groupeAjouterMembre (groupe, usager);
	char* nom = donnerUsagerNom (usager);

	if ( groupeContientInfo(groupe,nom) ) {
		groupeReinitialiserInfo (groupe, nom);
	} else {
		groupeAjouterInfo (groupe, nom);
	}

	char* buffer = (char*) malloc (BUF_SIZE * sizeof(char));
	sprintf (buffer, "%s est maintenant un membre du groupe %s", cmd.chaine[1], cmd.chaine[2] );
	int sd_dest = donnerUsagerNsd (usager);
	int n = send (sd_dest, buffer, BUF_SIZE, 0);	
	if ( n < 0 )	{
		char erreur[] = "L'usager ne sait pas qu'il fait maintenant partie d'un groupe!";
		printf ("%s", erreur);
		sprintf (buffer, "%s", erreur);	
	}

	return buffer;
}



char*	slash_refuser() {
	printf ("L'usager %s veut refuser une demande..\n", listeUsagerTrouverNom(cmd.nsd) );

	if ( cmd.nbrToken != 3 )
		return "Erreur! Usage: /refuser usager groupe";

	if ( ! listeGroupeContient(cmd.chaine[2]) )
		return "Erreur! Il n'y a pas de groupe de ce nom!";

	Groupe groupe = listeGroupeElement (cmd.chaine[2]);
	if ( ! groupeContientDemande(groupe, cmd.chaine[1]) )
		return "Erreur! Aucune demande pour cet usager pour ce groupe!";

	if ( strcmp(listeUsagerTrouverNom(cmd.nsd), donnerUsagerNom(donnerResponsable(groupe))) )
		return "Vous n'etes pas le responsable de ce groupe!";

	Usager usager = groupeEnleverDemande (groupe, cmd.chaine[1]);
	char* buffer = (char*) malloc (BUF_SIZE * sizeof(char));
	sprintf (buffer, "Le groupe %s a rejete l'usager %s!", cmd.chaine[2], cmd.chaine[1] );
	int sd_dest = donnerUsagerNsd (usager);
	int n = send (sd_dest, buffer, BUF_SIZE, 0);	
	if ( n < 0 )	{
		char erreur[] = "L'usager ne sait pas que le groupe l'a rejete!";
		printf ("%s", erreur);
		sprintf (buffer, "%s", erreur);	
	}

	return buffer;
}



void deal_with_data (int pos) {
	char buffer[BUF_SIZE];
	int n;
	int nsd = connectlist[pos];

	printf("Deal_with_data: FD=%d pos=%d\n", nsd, pos);

	n = recv (nsd, buffer, BUF_SIZE, 0);
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
			sprintf( buffer, "%s", slash_quitter(pos) );
		} else if ( !strcmp(cmd.chaine[0], "/creer") ) {
			sprintf( buffer, "%s", slash_creerGroupe());
		} else if ( !strcmp(cmd.chaine[0], "/joindre") ) {
			sprintf( buffer, "%s", slash_joindreGroupe());
		} else if ( !strcmp(cmd.chaine[0], "/byebye") ) {
			sprintf( buffer, "%s", slash_byebyeGroupe());
		} else if ( !strcmp(cmd.chaine[0], "/liste") ) {
			sprintf( buffer, "%s", slash_liste() );
		} else if ( !strcmp(cmd.chaine[0], "/stats") ) {
			sprintf( buffer, "%s", slash_statsGroupe());
		} else if ( !strcmp(cmd.chaine[0], "/accept") ) {
			sprintf( buffer, "%s", slash_accept());
		} else if ( !strcmp(cmd.chaine[0], "/refuser") ) {
			sprintf( buffer, "%s", slash_refuser());
		} else if ( !strcmp(cmd.chaine[0], "/info") ) {
			sprintf( buffer, "%s", slash_info());
		} else {
			sprintf (buffer, "Commande non supportee!");
		}

		if ( strcmp(buffer, "!@#Rien envoyee a l'initiateur!@#") ) {
			n = send (nsd, buffer, BUF_SIZE, 0);	
			if(n<0)	{
				printf("Erreur lors de l'envoi de la reponse au client!\n");
			}
			printf("Reponse: %s\n", buffer);
		}
		
		if ( !strcmp(cmd.chaine[0], "/quitter") && !strcmp(buffer, "Fermeture de la connexion client......") )
			close (cmd.nsd);
	}
}



void lire_sockets() {
	if (FD_ISSET(sd, &set_sockets))
		handle_new_connection();

	int i;
	for (i=0; i < MAX_USAGERS; i++) {
		if (FD_ISSET(connectlist[i], &set_sockets))
			deal_with_data(i);
	}
}



void	fin_du_serveur() {
	printf ("Fin du serveur...\n");

	int i;
	for ( i=0; i < MAX_USAGERS; i++ ) {
		if ( connectlist[i] != 0 )
			close (connectlist[i]);
	}

	close (sd);
}



int main (int argc, char* argv[]) {

	
	if (argc < 2) {
		printf ("Usage: %s PORT\r\n",argv[0]);
		exit (EXIT_FAILURE);
	}

	// pour fermer les connexions sur reception du CTRL-C
	signal (SIGINT, fin_du_serveur);

	
	struct sockaddr_in	server_address;
	struct timeval		timeout;
	int 			nbr_sockets_lus;
	
	
	
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	
	int reuse_addr = 1;
	setsockopt (sd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr) );

	
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

	
	listen (sd, MAX_USAGERS);

	while (1) {
		build_select_list();
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;
			
		nbr_sockets_lus = select(highsock+1, &set_sockets, NULL, NULL, &timeout);
		
		if (nbr_sockets_lus < 0) {
			perror("Erreur de select... Possiblement a cause d'un CTRL-C pour terminer le serveur!\n");
			break;

		} else if (nbr_sockets_lus == 0) {
			printf("Rien a lire. Serveur en vie...\n");
			fflush(stdout);
		} else {
			lire_sockets();
		}
	}

	fin_du_serveur();
	return 0;
}
