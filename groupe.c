
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "groupe.h"


#define MAX_USAGERS 100

struct groupe {
	char*	nom;
	char*	type;
	int	nbrMembres;
	int	nbrInfo;
	Usager	responsable;
	Usager*	membres;
	Info*	info;
};





Groupe	creerGroupe (char* nom, char* type, Usager responsable) {
	assert( responsable != NULL && "responsable doit etre un pointeur Usager non NULL" );

	Groupe monGroupe = (Groupe) malloc (sizeof(struct groupe));
	if ( monGroupe == NULL )
		return NULL;

	monGroupe->nom = malloc ((int) strlen(nom) * sizeof(char));
	strcpy( monGroupe->nom, nom );

	monGroupe->type = malloc ((int) strlen(type) * sizeof(char));
	strcpy( monGroupe->type, type );

	monGroupe->nbrMembres = 1;

	monGroupe->nbrInfo = 1;

	monGroupe->responsable = responsable;

	monGroupe->membres = (Usager*) malloc (MAX_USAGERS * sizeof(Usager));
	monGroupe->membres[0] = responsable;

	monGroupe->info = (Info*) malloc (MAX_USAGERS * sizeof(Info));
	monGroupe->info[0] = creerInfo (nom);

	return monGroupe;
}



char*	donnerGroupeNom (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->nom;
}



char*	donnerGroupeType (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->type;
}



Usager	donnerResponsable (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->responsable;
}


//int	donnerMembres (Groupe groupe) {

Usager*	donnerMembres (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->membres;
}


//int	donnerInfo (Groupe groupe) {

Info*	donnerInfo (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->info;
}



int	donnerNbrMembres (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->nbrMembres;
}



int	donnerNbrInfo (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->nbrInfo;
}



void	groupeAjouter (Groupe groupe, Usager usager) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	assert ( usager != NULL && "usager doit etre un pointeur non NULL" );
	int n = groupe->nbrMembres;
	groupe->membres[n] = usager;
	groupe->nbrMembres = n + 1;
}



void	supprimerGroupe (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int i;
	for ( i=0; i < groupe->nbrMembres; i++ ) {
		supprimerUsager (groupe->membres[i]);
	}
	for ( i=0; i < groupe->nbrInfo; i++ ) {
		supprimerInfo (groupe->info[i]);
	}
	supprimerUsager (groupe->responsable);
	free (groupe->info);
	free (groupe->membres);
	free (groupe->nom);
	free (groupe->type);
	free (groupe);
}



char*	groupeMembresToString (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );

	int nbr = groupe->nbrMembres;
	char* reponse = (char*) malloc ( ((int) strlen (donnerUsagerNom(groupe->membres[0]))) * sizeof(char) );
	sprintf (reponse, "%s", donnerUsagerNom(donnerMembres(groupe)[0]) );

	if ( nbr > 1 ) {
		int i;
		for ( i=1; i < nbr; i++ ) {
			int l = (int) strlen (reponse);
			char* nom = donnerUsagerNom( groupe->membres[i] );	
			reponse = (char*) realloc ( reponse, ((l + 1 + (int)strlen(nom)) * sizeof(char)) );
			sprintf (reponse, "%s %s", reponse, nom);
		}
	}
	return reponse;
}


char*	groupeInfoToString (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );

	int nbr = groupe->nbrInfo;

	char* reponse = (char*) malloc ( ((int) strlen (infoToString(groupe->info[0])) + 1) * sizeof(char) );
	sprintf (reponse, "%s\n", infoToString(groupe->info[0]) );
	
	return reponse;
}
