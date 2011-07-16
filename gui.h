/*
Classe:		gui.h

Description:	Methodes pour les Window de curses

Auteurs:	Alain Sirois     SIRA15068305
		Philippe Mercure MERP27078708
Date:		18 juin 2011
Cours:		yyyyyyyyyy
Groupe:		30
Travail:	TP2
Professeur:	xxxxxxxxxx
*/



#include "fenetre.h"


// Creer une fenetre avec bordure
WINDOW * create_newwin_with_border( Fenetre f );



// Creer une fenetre sans bordure
WINDOW * create_newwin_no_border( Fenetre f );



// Supprimer une fenetre
void destroy_win( WINDOW *local_win );
