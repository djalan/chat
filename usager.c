/*
Classe:         usager.c

Description:    Structure objet pour definir un usager et ses attributs

Auteurs:        Alain Sirois      SIRA15068305
                Philippe Mercure  MERP27078708
                
Date:           1er juin 2011
         
Cours:          INF5270
Groupe:         30
Travail:        TP1
Professeur:     Ammar Hamad
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "usager.h"



struct usager {
	char* nom;
	int adresse;
};



/*
Creer un usager et initialiser son nombre de fichier resultat a 1
*/
Usager	creerUsager (char* nom, int adresse) {
	Usager monUsager = (Usager) malloc (sizeof(struct usager));
	if ( monUsager == NULL )
     		return NULL;
	
	monUsager->nom = malloc ( (int) strlen(nom) * sizeof(char) );
	strcpy( monUsager->nom, nom );
	
	monUsager->adresse = adresse;

	return monUsager;
}



/*
Retourner le nom d'un Usager
*/
char*	donnerUsagerNom (Usager usager) {
	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");
	return usager->nom;
}



/*
Retourner le nombre de fichiers resultats d'un usager
*/
int	donnerUsagerAdresse (Usager usager) {
	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");
	return usager->adresse;
}



void	supprimerUsager (Usager usager) {
	assert (usager != NULL && "usager doit être valide (pointeur non NULL)");
	free (usager->nom);
	free (usager);	
}
