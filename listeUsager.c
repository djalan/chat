
/*
Classe:		listeUsager.c

Description:	Liste des usagers et ses methodes de manipulation

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
#include <string.h>
#include <assert.h>

#include "listeUsager.h"
#include "usager.h"
#include "config.h"




static int	nbrElems = 0;
static void*	lesUsagers[MAX_USAGERS];



// Ajouter un usager dans la liste
void	listeUsagerAjouter (void* elem) {
	assert (elem != NULL && "elem doit etre un pointeur non NULL");
	assert (nbrElems < MAX_USAGERS && "liste d'usager pleine");

	lesUsagers[nbrElems] = creerUsagerCopie (elem);
	//lesUsagers[nbrElems] = elem;
	nbrElems++;
}



// Donner le nombre d'usagers dans la liste
int	listeUsagerTaille () {
	return nbrElems;
}



// Verifier si un usager est dans la liste
int	listeUsagerContient (char* nom) {
	int i;
	for (i=0; i < nbrElems; i++) {
		if ( !strcmp(donnerUsagerNom(lesUsagers[i]), nom) )
			return 1;
	}
	return 0;
}



// Donner la position d'un usager dans la liste
int	listeUsagerPosition (char* nom) {
	int i;
	for (i=0; i < nbrElems; i++) {
		if ( !strcmp(donnerUsagerNom(lesUsagers[i]), nom) )
			return i;
	}
	return -1;
}



// Retourner l'usager a une certaine position
void*	listeUsagerObtenir (int position) {
	assert (nbrElems > 0 && "liste d'usagers vide");
	return lesUsagers[position];
}



// Retourner l'usager portant un certain nom
void*	listeUsagerElement (char* nom) {
	assert (nbrElems > 0 && "liste d'usagers vide");
	return lesUsagers[ listeUsagerPosition(nom) ];
}



// Enlever un usager dans la liste
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



// ToString des usagers
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



// Donner le nom d'un usager ayant un certain socket descriptor
char*	listeUsagerTrouverNom (int nsd) {
	int i;
	for ( i=0; i < nbrElems; i++ ) {
		if ( donnerUsagerNsd(lesUsagers[i]) == nsd )
			return donnerUsagerNom (lesUsagers[i]);
	}
	return "Aucun usager n'a ce numero de socket!";
}



// Donner le socket descriptor d'un usager
int	listeUsagerTrouverNsd (char* nom) {
	int i;
	for ( i=0; i < nbrElems; i++ ) {
		if ( !strcmp(donnerUsagerNom(lesUsagers[i]),nom) )
			return donnerUsagerNsd (lesUsagers[i]);
	}
	return -1;
}
