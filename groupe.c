/*
Classe:		groupe.c

Description:	Structure objet pour definir un groupe et ses attributs

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

#include "groupe.h"
#include "config.h"



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



// Creer un groupe
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

	return monGroupe;
}



// Donner le nom d'un groupe
char*	donnerGroupeNom (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->nom;
}



// Donner le type d'un groupe
char*	donnerGroupeType (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->type;
}



// Donner le responsable d'un groupe
Usager	donnerResponsable (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->responsable;
}



// Donner la liste des membres d'un groupe
Usager*	donnerMembres (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->membres;
}



// Donner la liste des demandes pour un groupe
Usager*	donnerDemandes (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->demandes;
}



// Donner la liste des infos pour un groupe
Info*	donnerInfo (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->info;
}



// Donner le nombre de membre d'un groupe
int	donnerNbrMembres (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->nbrMembres;
}



// Donner le nombre d'info pour un groupe
int	donnerNbrInfo (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->nbrInfo;
}



// Donner le nombre de demandes pour un groupe
int	donnerNbrDemandes (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	return groupe->nbrDemandes;
}



// Ajouter un membre dans un groupe
void	groupeAjouterMembre (Groupe groupe, Usager usager) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	assert ( usager != NULL && "usager doit etre un pointeur non NULL" );
	
	int n = groupe->nbrMembres;
	groupe->membres[n] = creerUsagerCopie (usager);
	groupe->nbrMembres = n + 1;
}



// Ajouter une demande pour un usager dans un groupe
void	groupeAjouterDemande (Groupe groupe, Usager usager) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	assert ( usager != NULL && "usager doit etre un pointeur non NULL" );
	
	int n = groupe->nbrDemandes;
	groupe->demandes[n] = creerUsagerCopie (usager);
	groupe->nbrDemandes = n + 1;
}



// Valider si un membre appartient a un groupe
int	groupeContientMembre (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrMembres; i++) {
		if ( !strcmp(donnerUsagerNom(groupe->membres[i]), nom) )
			return 1;
	}
	return 0;
}



// Valider si une demande a ete faite pour un usager pour un certain groupe
int	groupeContientDemande (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrDemandes; i++) {
		if ( !strcmp(donnerUsagerNom(groupe->demandes[i]), nom) )
			return 1;
	}
	return 0;
}



// Trouver la position d'un membre dans le tableau
int	groupePositionMembre (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrMembres; i++) {
		if ( !strcmp(donnerUsagerNom(groupe->membres[i]), nom) )
			return i;
	}
	return -1;
}



// Trouver la position d'une demande dans le tableau
int	groupePositionDemande (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrDemandes; i++) {
		if ( !strcmp(donnerUsagerNom(groupe->demandes[i]), nom) )
			return i;
	}
	return -1;
}



// Enlever un membre d'un groupe
Usager	groupeEnleverMembre (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	
	int pos = groupePositionMembre (groupe, nom);
	Usager usager = creerUsagerCopie(groupe->membres[pos]);
	supprimerUsager (groupe->membres[pos]);
	int i;
	for ( i=pos; i < (groupe->nbrMembres - 1); i++ ) {
		groupe->membres[i] = groupe->membres[i+1];
	}
	groupe->nbrMembres--;

	return usager;
}



// Enlever une demande pour un usager dans un groupe
Usager	groupeEnleverDemande (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	
	int pos = groupePositionDemande (groupe, nom);
	Usager usager = creerUsagerCopie(groupe->demandes[pos]);
	supprimerUsager (groupe->demandes[pos]);

	int i;
	for ( i=pos; i < (groupe->nbrDemandes - 1); i++ ) {
		groupe->demandes[i] = groupe->demandes[i+1];
	}

	groupe->nbrDemandes--;

	return usager;
}



// Verifier si un groupe a de l'info pour un certain usager
int	groupeContientInfo (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrInfo; i++) {
		if ( !strcmp(donnerInfoNom(groupe->info[i]), nom) )
			return 1;
	}
	return 0;
}



// Trouver la position d'un info dans le tableau
int	groupePositionInfo (Groupe groupe, char* nom) {
	int i;
	for (i=0; i < groupe->nbrInfo; i++) {
		if ( !strcmp(donnerInfoNom(groupe->info[i]), nom) )
			return i;
	}
	return -1;
}



// Augmenter le nombre d'interventions pour un usager dans un groupe
void	groupeAugmenterInterventions (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int pos = groupePositionInfo (groupe, nom);
	augmenterInterventions ( groupe->info[pos] );
}



// Ajouter un info pour un usager dans un groupe
void	groupeAjouterInfo (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int n = groupe->nbrInfo;
	groupe->info[n] = creerInfo(nom);
	groupe->nbrInfo = n + 1;
}



// Ajouter la date de depart pour un usager dans un groupe
void	groupeDepartInfo (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int pos = groupePositionInfo (groupe, nom);
	inscrireDepart ( groupe->info[pos] );
}



// Reset des infos pou un usager dans un groupe
void	groupeReinitialiserInfo (Groupe groupe, char* nom) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );
	int pos = groupePositionInfo (groupe, nom);
	reinitialiserInfo ( groupe->info[pos] );
}



// Supprimer un groupe
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



// ToString des membres d'uun groupe
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



// ToString des infos pour un groupe
char*	groupeInfoToString (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );

	int nbr = groupe->nbrInfo;
	char* reponse;
	if ( nbr == 1 ) { 
		reponse = (char*) malloc ( ((int) strlen (infoToString(groupe->info[0])) + 1) * sizeof(char) );
		sprintf (reponse, "%s", infoToString(groupe->info[0]) );
	} else {
		reponse = (char*) malloc ( ((int) strlen (infoToString(groupe->info[0])) + 1 + 1) * sizeof(char) );
		sprintf (reponse, "%s\n", infoToString(groupe->info[0]) );
	}
	
	int i;
	for ( i=1; i < nbr; i++ ) {
		int l = (int) strlen (reponse);
		char* info = infoToString (groupe->info[i]);
		if ( i != (nbr-1) ) {
			reponse = (char*) realloc ( reponse, ((l + (int)strlen(info) + 1 + 1) * sizeof(char)) );
			sprintf (reponse, "%s%s\n", reponse, info);
		} else {
			reponse = (char*) realloc ( reponse, ((l + (int)strlen(info) + 1) * sizeof(char)) );
			sprintf (reponse, "%s%s", reponse, info);
		}
	}

	return reponse;
}



// ToString des demandes pour groupe
char*	groupeDemandesToString (Groupe groupe) {
	assert ( groupe != NULL && "groupe doit etre un pointeur non NULL" );

	int nbr = groupe->nbrDemandes;
	if ( nbr == 0 )
		return "Aucune demande";

	char* reponse = (char*) malloc ( ((int) strlen (donnerUsagerNom(groupe->demandes[0])) + 1) * sizeof(char) );
	sprintf (reponse, "%s", donnerUsagerNom(donnerDemandes(groupe)[0]) );

	int i;
	for ( i=1; i < nbr; i++ ) {
		int l = (int) strlen (reponse);
		char* nom = donnerUsagerNom( groupe->demandes[i] );
		reponse = (char*) realloc ( reponse, ((l + 1 + (int) strlen(nom) + 1) * sizeof(char)) );
		sprintf (reponse, "%s %s", reponse, nom);
	}
	return reponse;
}
