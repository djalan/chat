/*
Classe:		fenetre.c

Description:	Structure objet pour definir une fenetre du GUI

Auteurs:	Alain Sirois     SIRA15068305
		Philippe Mercure MERP27078708
Date:		18 juin 2011
Cours:		yyyyyyyyyy
Groupe:		30
Travail:	TP2
Professeur:	xxxxxxxxxx
*/



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fenetre.h"



struct fenetre {
	int hauteur;
	int largeur;
	int starty;
	int startx;
};



/*
Creer une nouvelle fenetre avec ses proprietes
*/
Fenetre definirFenetre( int hauteur, int largeur, int starty, int startx ) {

	Fenetre f = (Fenetre) malloc (sizeof( struct fenetre ));
	if ( f == NULL )
		return NULL;

	f->hauteur = hauteur;
	f->largeur = largeur;
	f->starty = starty;
	f->startx = startx;

	return f;
}



/*
Donner la hauteur d'une fenetre
*/
int donnerHauteur( Fenetre f ) {
	assert (f != NULL && "fenetre doit être valide (pointeur non NULL)");
	return f->hauteur;
}



/*
Donner la largeur d'une fenetre
*/
int donnerLargeur( Fenetre f ) {
	assert (f != NULL && "fenetre doit être valide (pointeur non NULL)");
	return f->largeur;
}



/*
Donner la coordonnee Y d'une fenetre
*/
int donnerStarty( Fenetre f ) {
	assert (f != NULL && "fenetre doit être valide (pointeur non NULL)");
	return f->starty;

}



/*
Donner la coordonnee X d'une fenetre
*/
int donnerStartx( Fenetre f ) {
	assert (f != NULL && "fenetre doit être valide (pointeur non NULL)");
	return f->startx;
}
