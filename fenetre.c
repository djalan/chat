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


int donnerHauteur( Fenetre f ) {
	assert (f != NULL && "fenetre doit être valide (pointeur non NULL)");
	return f->hauteur;
}


int donnerLargeur( Fenetre f ) {
	assert (f != NULL && "fenetre doit être valide (pointeur non NULL)");
	return f->largeur;
}


int donnerStarty( Fenetre f ) {
	assert (f != NULL && "fenetre doit être valide (pointeur non NULL)");
	return f->starty;

}


int donnerStartx( Fenetre f ) {
	assert (f != NULL && "fenetre doit être valide (pointeur non NULL)");
	return f->startx;
}
