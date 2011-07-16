/*
Classe:		listeUsager.h

Description:	Liste des usagers et ses methodes de manipulations

Auteurs:	Alain Sirois     SIRA15068305
		Philippe Mercure MERP27078708
Date:		18 juin 2011
Cours:		yyyyyyyyyy
Groupe:		30
Travail:	TP2
Professeur:	xxxxxxxxxx
*/



// Ajouter un usager dans la liste
void	listeUsagerAjouter (void* elem);



// Donner le nombre d'usagers dans la liste
int	listeUsagerTaille ();



// Verifier si un usager est dans la liste
int	listeUsagerContient (char* nom);



// Donner la poistion d'un usager dans la liste
int	listeUsagerPosition (char* nom);



// Retourner l'usager a une certaine position
void*	listeUsagerObtenir (int position);



// Retourner l'usager ayant un certain nom
void*	listeUsagerElement (char* nom);



// Enlever un usager de la liste
void*	listeUsagerEnlever (char *nom);



// ToString des usagers
char*	listeUsagerToString ();



// Donner le nom d'usager portant un certain socket descriptor
char*	listeUsagerTrouverNom (int nsd);



// Donner le socket descriptor d'un  usager
int	listeUsagerTrouverNsd (char* nom);
