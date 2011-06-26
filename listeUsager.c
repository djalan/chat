#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "listeUsager.h"
#include "usager.h"



#define MAX_ELEMS 1000
static int	nbrElems = 0;
static void*	lesUsagers[MAX_ELEMS];



void	listeUsagerAjouter (void* elem) {
	assert (elem != NULL && "elem doit etre un pointeur non NULL");
	assert (nbrElems < MAX_ELEMS && "liste d'usager pleine");

	lesUsagers[nbrElems] = creerUsagerCopie (elem);
	//lesUsagers[nbrElems] = elem;
	nbrElems++;
}



int	listeUsagerTaille () {
	return nbrElems;
}



int	listeUsagerContient (char* nom) {
	int i;
	for (i=0; i < nbrElems; i++) {
		if ( !strcmp(donnerUsagerNom(lesUsagers[i]), nom) )
			return 1;
	}
	return 0;
}



int	listeUsagerPosition (char* nom) {
	int i;
	for (i=0; i < nbrElems; i++) {
		if ( !strcmp(donnerUsagerNom(lesUsagers[i]), nom) )
			return i;
	}
	return -1;
}



void*	listeUsagerObtenir (int position) {
	assert (nbrElems > 0 && "liste d'usagers vide");
	return lesUsagers[position];
}



void*	listeUsagerElement (char* nom) {
	assert (nbrElems > 0 && "liste d'usagers vide");
	return lesUsagers[ listeUsagerPosition(nom) ];
}



void*	listeUsagerEnlever (char *nom) {
	assert (nbrElems > 0 && "liste d'usagers vide");

	int position = listeUsagerPosition (nom);
	Usager usager = lesUsagers[position];
	supprimerUsager (lesUsagers[position]);

	int i;
	for ( i=position; i < (nbrElems-1); i++ )
		lesUsagers[i] = lesUsagers[i+1];

	nbrElems--;
	return usager;
}



char*	listeUsagerToString () {

	if ( nbrElems == 0 )
		return "Il n'y a aucun usager presentement!"; 

	char* usager1 = donnerUsagerNom(lesUsagers[0]);
	char* reponse = (char*) malloc ( ((int) strlen(usager1) + 1) * sizeof(char) );
	sprintf (reponse, "%s", usager1);
	int i;
	for ( i=1; i < nbrElems; i++ ) {
		int l = (int) strlen (reponse);
		char* usager = donnerUsagerNom(lesUsagers[i]);
		reponse = (char*) realloc ( reponse, ((l + (int) strlen(usager) + 1) * sizeof(char)) );
		sprintf (reponse, "%s %s", reponse, usager);
	}
	return reponse;
}
