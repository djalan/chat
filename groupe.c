
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "groupe.h"


#define MAX_USAGERS 100

struct groupe {
	char*	nom;
	char*	type;
	Usager	responsable;
	int	nbrMembres;
	Usager*	membres;
	int	nbrInfo;
	Info*	info;
	int	nbrDemandes;
	Usager*	demandes;
};





Groupe	creerGroupe (char* nom, char* type, Usager responsable) {
	assert( responsable != NULL && "responsable doit etre un pointeur Usager non NULL" );

	Groupe monGroupe = (Groupe) malloc (sizeof(struct groupe));
	if ( monGroupe == NULL )
		return NULL;

	monGroupe->nom = malloc ( ((int) strlen(nom) + 1) * sizeof(char));
	sprintf (monGroupe->nom, "%s", nom);

	monGroupe->type = malloc ( ((int) strlen(type) + 1) * sizeof(char));
	sprintf (monGroupe->type, "%s", type);

	monGroupe->nbrMembres = 1;

	monGroupe->nbrInfo = 1;

	monGroupe->nbrDemandes = 0;

	monGroupe->responsable = creerUsagerCopie (responsable);

	monGroupe->membres = (Usager*) malloc (MAX_USAGERS * sizeof(Usager));
	monGroupe->membres[0] = creerUsagerCopie (responsable);

	monGroupe->info = (Info*) malloc (MAX_USAGERS * sizeof(Info));
	monGroupe->info[0] = creerInfo (donnerUsagerNom(responsable));

	monGroupe->demandes = (Usager*) malloc (MAX_USAGERS * sizeof(Usager));
	//monGroupe->demandes[0] = NULL;
	//monGroupe->demandes = 1;

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



Usager*	donnerMembres (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->membres;
}



Usager*	donnerDemandes (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->demandes;
}



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



int	donnerNbrDemandes (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->nbrDemandes;
}



void	groupeAjouterMembre (Groupe groupe, Usager usager) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	assert ( usager != NULL && "usager doit etre un pointeur non NULL" );
	
	int n = groupe->nbrMembres;
	groupe->membres[n] = creerUsagerCopie (usager);
	groupe->nbrMembres = n + 1;

	char* nom = donnerUsagerNom (usager);
	if ( groupeContientInfo(groupe,nom) ) {
		groupeReinitialiserInfo (groupe, nom);
	} else {
		groupeAjouterInfo (groupe, nom);
	}
}



void	groupeAjouterDemande (Groupe groupe, Usager usager) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	assert ( usager != NULL && "usager doit etre un pointeur non NULL" );
	
	int n = groupe->nbrDemandes;
	groupe->demandes[n] = creerUsagerCopie (usager);
	groupe->nbrDemandes = n + 1;
}



int	groupeContientMembre (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrMembres; i++) {
		if ( !strcmp(donnerUsagerNom(groupe->membres[i]), nom) )
			return 1;
	}
	return 0;
}



int	groupePositionMembre (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrMembres; i++) {
		if ( !strcmp(donnerUsagerNom(groupe->membres[i]), nom) )
			return i;
	}
	return -1;
}



int	groupePositionDemande (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrDemandes; i++) {
		if ( !strcmp(donnerUsagerNom(groupe->demandes[i]), nom) )
			return i;
	}
	return -1;
}



Usager	groupeEnleverMembre (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	
	int pos = groupePositionMembre (groupe, nom);
	Usager usager = groupe->membres[pos];	
	supprimerUsager (groupe->membres[pos]);
	int i;
	for ( i=pos; i < (groupe->nbrMembres - 1); i++ ) {
		groupe->membres[i] = groupe->membres[i+1];
	}
	groupe->nbrMembres--;

	groupeDepartInfo (groupe, nom);

	return usager;
}



Usager	groupeEnleverDemande (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	
	int pos = groupePositionDemande (groupe, nom);
	Usager usager = groupe->demandes[pos];	
	supprimerUsager (groupe->demandes[pos]);

	int i;
	for ( i=pos; i < (groupe->nbrDemandes - 1); i++ ) {
		groupe->demandes[i] = groupe->demandes[i+1];
	}

	groupe->nbrDemandes--;

	return usager;
}



int	groupeContientInfo (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrInfo; i++) {
		if ( !strcmp(donnerInfoNom(groupe->info[i]), nom) )
			return 1;
	}
	return 0;
}



int	groupePositionInfo (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrInfo; i++) {
		if ( !strcmp(donnerInfoNom(groupe->info[i]), nom) )
			return i;
	}
	return -1;
}



void	groupeAugmenterInterventions (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int pos = groupePositionInfo (groupe, nom);
	augmenterInterventions ( groupe->info[pos] );
}



void	groupeAjouterInfo (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int n = groupe->nbrInfo;
	groupe->info[n] = creerInfo(nom);
	groupe->nbrInfo = n + 1;
}



void	groupeDepartInfo (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int pos = groupePositionInfo (groupe, nom);
	inscrireDepart ( groupe->info[pos] );
}



void	groupeReinitialiserInfo (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int pos = groupePositionInfo (groupe, nom);
	reinitialiserInfo ( groupe->info[pos] );
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
	char* reponse = (char*) malloc ( ((int) strlen (donnerUsagerNom(groupe->membres[0])) + 1) * sizeof(char) );
	sprintf (reponse, "%s", donnerUsagerNom(donnerMembres(groupe)[0]) );

	int i;
	for ( i=1; i < nbr; i++ ) {
		int l = (int) strlen (reponse);
		char* nom = donnerUsagerNom( groupe->membres[i] );
		reponse = (char*) realloc ( reponse, ((l + 1 + (int) strlen(nom) + 1) * sizeof(char)) );
		sprintf (reponse, "%s %s", reponse, nom);
	}
	return reponse;
}


char*	groupeInfoToString (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );

	int nbr = groupe->nbrInfo;
	char* reponse = (char*) malloc ( ((int) strlen (infoToString(groupe->info[0])) + 1 + 1) * sizeof(char) );
	sprintf (reponse, "%s\n", infoToString(groupe->info[0]) );
	
	int i;
	for ( i=1; i < nbr; i++ ) {
		int l = (int) strlen (reponse);
		char* info = infoToString (groupe->info[i]);	
		reponse = (char*) realloc ( reponse, ((l + (int)strlen(info) + 1 + 1) * sizeof(char)) );
		sprintf (reponse, "%s%s\n", reponse, info);
	}
	return reponse;
}



char*	groupeDemandesToString (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return "demandes to string";
}
