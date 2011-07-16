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



// Obtenir la date / heure du moment
char*	obtenirDateHeure () {
	time_t timer = time (NULL);
	char* dateHeure = ctime (&timer);
	int l = (int) strlen (dateHeure);
	dateHeure[l-1] = '\0';
	return dateHeure;
}



// Creer une info pour un usager
Info	creerInfo (char* nom) {
	Info monInfo = (Info) malloc (sizeof(struct info));
	if ( monInfo == NULL )
		return NULL;

	monInfo->nomUsager = malloc ( ((int) strlen(nom) + 1) * sizeof(char));
	sprintf (monInfo->nomUsager, "%s", nom );

	char* dateHeure = obtenirDateHeure();
	monInfo->arrivee = (char*) malloc ( ((int) strlen(dateHeure) + 1) * sizeof(char));
	sprintf (monInfo->arrivee, "%s", dateHeure ); 

	char* encore = "Encore dans le groupe!";
	monInfo->depart = (char*) malloc ( ((int) strlen(encore) + 1) * sizeof(char));
	sprintf (monInfo->depart, "%s", encore);

	monInfo->nbrInterventions = 0;

	return monInfo;
}



// Reset d'une info
void	reinitialiserInfo (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	sprintf (info->arrivee, "%s", obtenirDateHeure() );

	free (info->depart);
	char* encore = "Encore dans le groupe!";
	info->depart = (char*) malloc ( ((int) strlen(encore) + 1) * sizeof(char));
	sprintf (info->depart, "%s", encore);

	info->nbrInterventions = 0;
}



// Donner le nom d'usager d'une certaine info
char*	donnerInfoNom (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	return info->nomUsager;
}



// Donner la date d'arrive d'un usager
char*	donnerInfoArrivee (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	return info->arrivee;
}



// Donner la date de depart d'un usager
char*	donnerInfoDepart (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	return info->depart;
}



// Donner le nombre d'interventions d'un usager dans un groupe
int	donnerNbrInterventions (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	return info->nbrInterventions;
}



// ToString d'une info
char*	infoToString (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	int l_nom = (int) strlen (info->nomUsager);
	int l_arr = (int) strlen (info->arrivee);
	int l_dep = (int) strlen (info->depart);
	char tmp[10];
	sprintf (tmp, "%d", info->nbrInterventions);
	int l_nbr = (int) strlen (tmp);

	char* reponse = (char*) malloc ( (4 + l_nom + 3 + 8 + l_arr + 3 + 7 + l_dep + 3 + 14 + l_nbr + 1) * sizeof(char) );

	sprintf (reponse, "NOM:%s - ARRIVEE:%s - DEPART:%s - INTERVENTIONS:%d", 
		info->nomUsager,
		info->arrivee,
		info->depart,
		info->nbrInterventions);

	return reponse;
}



// Incrementer le nombre d'interventions d'une info
void	augmenterInterventions (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	info->nbrInterventions++;
}



// Inscrire la date de depart d'un usager
void	inscrireDepart (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	free (info->depart);
	char* dateHeure = obtenirDateHeure();
	info->depart = (char*) malloc ( ((int) strlen(dateHeure) + 1) * sizeof(char));
	sprintf (info->depart, "%s", dateHeure ); 
}



// Supprimer une info
void	supprimerInfo (Info info) {
	assert ( info != NULL && "info doit etre un pointeur non NULL" );

	free (info->nomUsager);
	free (info->arrivee);
	free (info->depart);
	free (info);
}
