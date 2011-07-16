
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "listeGroupe.h"
#include "groupe.h"
#include "config.h"



static int	nbrElems = 0;
static void*	lesGroupes[MAX_GROUPES];



// Ajouter un groupe dans la liste
void	listeGroupeAjouter (void* elem) {
	assert (elem != NULL && "elem doit etre un pointeur non NULL");
	assert (nbrElems < MAX_GROUPES && "liste groupe pleine");

	lesGroupes[nbrElems] = elem;
	nbrElems++;
}



// Donner le nombre de groupes
int	listeGroupeTaille () {
	return nbrElems;
}



// Verifier si un groupe est dans la liste
int	listeGroupeContient (char* nom) {
	int i;
	for (i=0; i < nbrElems; i++) {
		if ( !strcmp(donnerGroupeNom(lesGroupes[i]), nom) )
			return 1;
	}
	return 0;
}



// Donner la position d'un groupe dans la liste
int	listeGroupePosition (char* nom) {
	int i;
	for (i=0; i < nbrElems; i++) {
		if ( !strcmp(donnerGroupeNom(lesGroupes[i]), nom) )
			return i;
	}
	return -1;
}



// Donner le groupe a une certaine position
void*	listeGroupeObtenir (int position) {
	assert (nbrElems > 0 && "liste groupes vide");
	return lesGroupes[position];
}



// Donner le groupe correspondant a un certain nom
void*	listeGroupeElement (char* nom) {
	assert (nbrElems > 0 && "liste groupes vide");
	return lesGroupes[ listeGroupePosition(nom) ];
}



// Enlever le groupe portant un certain nom
void*	listeGroupeEnlever (char *nom) {
	assert (nbrElems > 0 && "liste groupes vide");

	int position = listeGroupePosition (nom);
	Groupe groupe = lesGroupes[position];
	supprimerGroupe (lesGroupes[position]);

	int i;
	for ( i=position; i < (nbrElems-1); i++ )
		lesGroupes[i] = lesGroupes[i+1];

	nbrElems--;
	return groupe;
}



// Verifier si un usager est responsable d'au moins un groupe
int	listeGroupeEstResponsable (char* nom) {

	int i;
	for ( i=0; i < nbrElems; i++ ) {
		if ( !strcmp(nom, donnerUsagerNom(donnerResponsable(lesGroupes[i]))) )
			return 1;
	}

	return 0;
}



// Verifier si un usager est membre d'au moins un groupe prive
int	listeGroupeEstMembrePrive (char* nom) {

	int i;
	for ( i=0; i < nbrElems; i++ ) {
		if ( !strcmp("prive", donnerGroupeType(lesGroupes[i])) ) {
			if ( groupeContientMembre(lesGroupes[i], nom) )
				return 1;
		}
	}

	return 0;
}




// ToString des groupes dans la liste
char*	listeGroupeToString () {

	if ( nbrElems == 0 )
		return "Il n'y a aucun groupe presentement";

	char* groupe1 = donnerGroupeNom (lesGroupes[0]);
	char* reponse = (char*) malloc ( ((int) strlen(groupe1) + 1) * sizeof(char) );
	sprintf (reponse, "%s", groupe1);
	int i;
	for ( i=1; i < nbrElems; i++ ) {
		int l = (int) strlen (reponse);
		char* groupe = donnerGroupeNom (lesGroupes[i]);
		reponse = (char*) realloc ( reponse, ((l + (int) strlen (groupe) + 1) * sizeof(char)) );
		sprintf (reponse, "%s %s", reponse, groupe);
	}

	return reponse;
}
