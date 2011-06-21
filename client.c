#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fenetre.h"
#include "chaine.h"
//#include <time.h>



WINDOW * create_newwin_with_border( Fenetre f );
WINDOW * create_newwin_no_border( Fenetre f );
void destroy_win(WINDOW * local_win);
int key_handler( Fenetre fen );



WINDOW * w_haut;
WINDOW * w_chat;
WINDOW * w_cmd;
WINDOW * w_bas;
Chaine input;



#define	marge_bas 1
#define f_haut_hauteur 3
#define f_bas_hauteur 1
#define f_cmd_hauteur 5



/*
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
*/






int main() {

	initscr();	// Start curses mode
	cbreak();	// Line buffering disabled, Pass on everty thing to me


	//my_win = create_newwin(height, width, starty, startx);
	Fenetre f_haut	= definirFenetre( f_haut_hauteur, COLS, 0, 0 );
	Fenetre f_bas	= definirFenetre( f_bas_hauteur, COLS, (LINES - f_bas_hauteur - marge_bas), 0 );
	Fenetre f_cmd	= definirFenetre( f_cmd_hauteur, COLS, (LINES - donnerHauteur(f_bas) - f_cmd_hauteur - marge_bas), 0 );
	Fenetre f_chat	= definirFenetre( (LINES - donnerHauteur(f_haut) - donnerHauteur(f_cmd) - donnerHauteur(f_bas) - marge_bas), COLS, donnerHauteur(f_haut), 0 );


	refresh();
	w_haut	= create_newwin_with_border( f_haut );
	w_bas	= create_newwin_no_border( f_bas );
	w_cmd	= create_newwin_with_border( f_cmd );
	w_chat	= create_newwin_no_border( f_chat );


	scrollok( w_chat, 1 );
	wsetscrreg( w_chat, donnerStarty(w_chat), donnerStarty(w_cmd) - 1 );
	wtimeout(w_bas, 2000);


	mvwprintw(w_haut, 1, 1, "CHAT CLIENT");
	wprintw(w_chat, "Le scroll marche! Tapper plusieurs lignes pour le tester.\n" );
	mvwprintw(w_cmd, 1, 1, "Liste des commandes");
	mvwprintw(w_cmd, 2, 1, "/quitter");
	wmove( w_bas, 0, 0 );
	wrefresh(w_haut);
	wrefresh(w_chat);
	wrefresh(w_cmd);
	wrefresh(w_bas);


	
	input = chaineCreerVide( COLS );
	while ( 1 ) {
		if ( !key_handler(f_bas) )
			break;
	}	

	endwin(); // End curses mode
	return 0;
}



WINDOW * create_newwin_with_border( Fenetre f ) {

	WINDOW * local_win;

	//local_win = newwin(height, width, starty, startx);
	local_win = newwin( donnerHauteur(f), donnerLargeur(f), donnerStarty(f), donnerStartx(f) );
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}




WINDOW * create_newwin_no_border( Fenetre f ) {

	WINDOW * local_win;

	//local_win = newwin(height, width, starty, startx);
	local_win = newwin( donnerHauteur(f), donnerLargeur(f), donnerStarty(f), donnerStartx(f) );

	wrefresh(local_win);

	return local_win;
}



void destroy_win( WINDOW *local_win )
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}



int key_handler( Fenetre fen ) {

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
			w_bas = create_newwin_no_border( fen );
			
			if ( longueur > COLS ) {
				mvwprintw(w_bas, 0, 0, "%s", &chaineValeur(input)[longueur-COLS] );
			} else {
				mvwprintw( w_bas, 0, 0, "%s", chaineValeur(input) );
			}

		} else {
			delwin(w_bas);
			w_bas = create_newwin_no_border( fen );
			wmove( w_bas, 0, 0 );
		}

	} else if ( ch == '\n' ) { // ENTER
		wprintw(w_chat, "%s\n", chaineValeur(input) );
		//wrefresh(w_chat);
		delwin(w_bas);
		w_bas = create_newwin_no_border( fen );
		wmove( w_bas, 0, 0 );

		if ( !strcmp(chaineValeur(input), "/quitter") ) {
			chaineSupprime( input );
			return 0;
		}

		chaineSupprime( input );
		input = chaineCreerVide( COLS );
	}

	wprintw(w_chat, "Allo boucle\n" );
	wmove( w_bas, 0, chaineLongueur(input) );
	wrefresh(w_chat);
	wrefresh(w_bas);

	return 1;
}