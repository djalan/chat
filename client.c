#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chaine.h"
#include "gui.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 2048

void key_handler ();
int recv_handler ();
void setnonblocking (int sock);



WINDOW * w_haut;
WINDOW * w_chat;
WINDOW * w_cmd;
WINDOW * w_info;
WINDOW * w_bas;

Chaine input;

Fenetre f_haut;
Fenetre f_bas;
Fenetre f_cmd;
Fenetre f_info;
Fenetre f_chat;

int socket_d;
int nom_usager_defini;


#define	marge_bas 1

#define f_haut_hauteur 3
#define f_cmd_hauteur 3
#define f_info_hauteur 5
#define f_bas_hauteur 1



int main (int argc, char* argv[]) {

	if ( argc < 2 ) {
		printf ("Usage: %s PORT\n", argv[0]);
		exit (EXIT_FAILURE);
	}

	initscr();	// Start curses mode
	cbreak();	// Line buffering disabled, Pass on everty thing to me

	//my_win = create_newwin(height, width, starty, startx);
	f_haut	= definirFenetre( f_haut_hauteur, COLS, 0, 0 );
	f_bas	= definirFenetre( f_bas_hauteur, COLS, (LINES - f_bas_hauteur - marge_bas), 0 );
	f_info	= definirFenetre( f_info_hauteur, COLS, (LINES - donnerHauteur(f_bas) - f_info_hauteur - marge_bas), 0 );
	f_cmd 	= definirFenetre( f_cmd_hauteur, COLS, (LINES - donnerHauteur(f_bas) - donnerHauteur(f_info) - marge_bas - f_cmd_hauteur), 0);
	f_chat	= definirFenetre( (LINES - donnerHauteur(f_haut) - donnerHauteur(f_cmd) - donnerHauteur(f_info) - donnerHauteur(f_bas) - marge_bas), COLS, donnerHauteur(f_haut), 0 );

	refresh();
	w_haut	= create_newwin_with_border( f_haut );
	w_bas	= create_newwin_no_border( f_bas );
	w_info	= create_newwin_with_border( f_info );
	w_cmd	= create_newwin_with_border( f_cmd );
	w_chat	= create_newwin_no_border( f_chat );

	scrollok( w_chat, 1 );
	wsetscrreg( w_chat, donnerStarty(f_chat), donnerHauteur(f_chat) );
	wtimeout(w_bas, 500);

	mvwprintw(w_haut, 1, 1, "CHAT CLIENT");
	mvwprintw(w_cmd, 1, 1, "");
	mvwprintw(w_info, 1, 1, "/nom usager\t/mp usager\t/creer   groupe\t\t/info  groupe");
	mvwprintw(w_info, 2, 1, "\t\t/mp groupe\t/joindre groupe\t\t/liste usagers");
	mvwprintw(w_info, 3, 1, "/quitter\t\t\t/byebye  groupe\t\t/liste groupes");
	wmove( w_bas, 0, 0 );
	wrefresh(w_haut);
	wrefresh(w_info);
	wrefresh(w_bas);
	wrefresh(w_cmd);

	
	nom_usager_defini = 0;


	//socklen_t		l;
	struct sockaddr_in	serveur;
	struct hostent*		hp;
	//char 			buffer[BUF_SIZE];
	//struct sockaddr	from;

	socket_d = socket (AF_INET, SOCK_STREAM, 0);
	if (socket_d < 0) {
		printf("Erreur lors de la création de la socket !\n");
		close (socket_d);
		exit(1);
	}
	setnonblocking (socket_d);

	hp = gethostbyname("localhost");
	if (hp==0) {
		printf("Hôte inconnu !\n");
		exit(1);
	}

	serveur.sin_family = AF_INET;
	serveur.sin_port = htons(atoi(argv[1]));
	bcopy((char *)hp->h_addr, (char *)&serveur.sin_addr, hp->h_length);

	if ( connect(socket_d,(struct sockaddr *)&serveur,sizeof(struct sockaddr_in)) < 0 ) {
		printf("Erreur lors de la création d'une nouvelle connexion !\n");
		exit(1);
	}



	input = chaineCreerVide( COLS );
	while ( 1 ) {
		key_handler();

		if ( ! recv_handler() )
			break;
	}	

	endwin (); // End curses mode
	close (socket_d);
	return 0;
}



int	recv_handler () {

	char	buffer[BUF_SIZE];
	int	n;

	n = recv (socket_d, buffer, BUF_SIZE, 0);
	if ( n > 0 ) {
		wprintw (w_chat, "%s\n", buffer );
		wrefresh (w_chat);
	}


	if ( ! strcmp(buffer, "Fermeture de la connexion client......") )
		return 0;

	return 1;
}



void key_handler () {

	int ch = wgetch(w_bas);  
	int longueur = chaineLongueur(input);

	if ( ch != '\n' && ch != ERR && ch!= 127 ) {
		chaineAjouter( input, ch );

		if ( longueur > COLS ) {
			mvwprintw(w_bas, 0, 0, "%s", &chaineValeur(input)[longueur-COLS] );
		}
			

	} else if ( ch == 127 ) { // BACKSPACE
		if ( chaineLongueur(input) > 0 ) {
			chaineEnlever(input);
			delwin(w_bas);
			w_bas = create_newwin_no_border( f_bas );
			
			if ( longueur > COLS ) {
				mvwprintw(w_bas, 0, 0, "%s", &chaineValeur(input)[longueur-COLS] );
			} else {
				mvwprintw( w_bas, 0, 0, "%s", chaineValeur(input) );
			}

		} else {
			delwin(w_bas);
			w_bas = create_newwin_no_border( f_bas );
			wmove( w_bas, 0, 0 );
		}

	} else if ( ch == '\n' ) { // ENTER
		delwin(w_cmd);
		w_cmd = create_newwin_with_border( f_cmd );
		mvwprintw(w_cmd, 1, 1, "%s", chaineValeur(input) );

		delwin(w_bas);
		w_bas = create_newwin_no_border( f_bas );
		wmove( w_bas, 0, 0 );

		char buffer[BUF_SIZE];
		sprintf ( buffer, "%s", chaineValeur(input) );
		int n = send (socket_d, buffer, strlen(buffer)+1, 0);
		if ( n < 0 )
			wprintw(w_chat, "Erreur lors de l'envoi\n");
			
		chaineSupprime( input );
		input = chaineCreerVide( COLS );
	}

	wmove( w_bas, 0, chaineLongueur(input) );
	wrefresh(w_chat);
	wrefresh(w_cmd);
	wrefresh(w_bas);
}



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
