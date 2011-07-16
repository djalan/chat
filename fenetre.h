/*
Classe:		fenetre.h

Description:	Structure objet pour definir une fenetre du GUI

Auteurs:	Alain Sirois     SIRA15068305
		Philippe Mercure MERP27078708
Date:		18 juin 2011
Cours:		yyyyyyyyyy
Groupe:		30
Travail:	TP2
Professeur:	xxxxxxxxxx
*/



typedef struct fenetre * Fenetre;



/*
Creer une nouvelle fenetre avec ses proprietes
*/
Fenetre definirFenetre( int hauteur, int largeur, int starty, int startx );



/*
Donner la hauteur d'une fenetre
*/
int donnerHauteur( Fenetre f );



/*
Donner la largeur d'une fenetre
*/
int donnerLargeur( Fenetre f );



/*
Donner la coordonnee Y d'une fenetre
*/
int donnerStarty( Fenetre f );



/*
Donner la coordonne X d'une fenetre
*/
int donnerStartx( Fenetre f );
