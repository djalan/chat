#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "info.h"



struct info {
	char*	nomUsager;
	char*	arrivee;
	char*	depart;
	int	nbrInterventions;
};



char*	obtenirDateHeure () {
	time_t timer = time (NULL);
	char* dateHeure = ctime (&timer);
	int l = (int) strlen (dateHeure);
	dateHeure[l-1] = '\0';
	return dateHeure;
}



Info	creerInfo (char* nom) {

	Info monInfo = (Info) malloc (sizeof(struct info));
	if ( monInfo == NULL )
		return NULL;

	monInfo->nomUsager = malloc ((int) strlen(nom) * sizeof(char));
	sprintf (monInfo->nomUsager, "%s", nom );

	monInfo->arrivee = (char*) malloc (30 * sizeof(char));
	sprintf (monInfo->arrivee, "%s", obtenirDateHeure() ); 

	monInfo->depart = (char*) malloc (30 * sizeof(char));
	sprintf (monInfo->depart, "%s", "Encore dans le groupe!");

	monInfo->nbrInterventions = 0;

	return monInfo;
}



void	reinitialiserInfo (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	sprintf (info->arrivee, "%s", obtenirDateHeure() ); 
	sprintf (info->depart, "%s", "Encore dans le groupe!");
	info->nbrInterventions = 0;
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



char*	infoToString (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	int l_nom = (int) strlen (info->nomUsager);
	int l_arr = (int) strlen (info->arrivee);
	int l_dep = (int) strlen (info->depart);
	char tmp[10];
	sprintf (tmp, "%d", info->nbrInterventions);
	int l_nbr = (int) strlen (tmp);

	char* reponse = (char*) malloc ( (4 + l_nom + 3 + 8 + l_arr + 3 + 7 + l_dep + 3 + 14 + l_nbr) * sizeof(char) );

	sprintf (reponse, "NOM:%s - ARRIVEE:%s - DEPART:%s - INTERVENTIONS:%d", 
		info->nomUsager,
		info->arrivee,
		info->depart,
		info->nbrInterventions);

	return reponse;
}


void	augmenterInterventions (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	int n = info->nbrInterventions;
	info->nbrInterventions = n + 1;
}



void	inscrireDepart (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	sprintf (info->depart, "%s", obtenirDateHeure() ); 
}



void	supprimerInfo (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );
	free (info->nomUsager);
	free (info->arrivee);
	free (info->depart);
	free (info);
}
