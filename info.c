#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//#include "usager.h"
#include "info.h"



struct info {
	char*	nomUsager;
	char*	arrivee;
	char*	depart;
	int	nbrInterventions;
};



Info	creerInfo (char* nom) {

	Info monInfo = (Info) malloc (sizeof(struct info));
	if ( monInfo == NULL )
		return NULL;

	monInfo->nomUsager = malloc ((int) strlen(nom) * sizeof(char));
	strcpy( monInfo->nomUsager, nom );

	monInfo->arrivee = (char*) malloc (50 * sizeof(char));
	sprintf (monInfo->arrivee, "ARRrivee");

	monInfo->depart = (char*) malloc (50 * sizeof(char));
	sprintf (monInfo->depart, "L'usager est encore dans le groupe.");

	monInfo->nbrInterventions = 0;

	return monInfo;
}



char*	donnerInfoNom (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	return info->nomUsager;
}



char*	donnerInfoArrivee (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	return info->arrivee;
}



char*	donnerInfoDepart (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	return info->depart;
}



int	donnerNbrInterventions (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	return info->nbrInterventions;
}



void	augmenterInterventions (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	int n = info->nbrInterventions;
	info->nbrInterventions = n + 1;
}



void	inscrireDepart (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	sprintf (info->depart, "GONE!");
}



void	supprimerInfo (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	free (info->nomUsager);
	free (info->arrivee);
	free (info->depart);
	free (info);
}
