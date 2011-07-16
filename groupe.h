/*
Classe:		groupe.h

Description:	Structure objet pour definir un groupe et ses attributs

Auteurs:	Alain Sirois     SIRA15068305
		Philippe Mercure MERP27078708
Date:		18 juin 2011
Cours:		yyyyyyyyyy
Groupe:		30
Travail:	TP2
Professeur:	xxxxxxxxxx
*/




#include "usager.h"
#include "info.h"

typedef struct groupe* Groupe;



// Creer un groupe
Groupe	creerGroupe (char* nom, char* type, Usager responsable);



// Donner le nom d'un groupe
char*	donnerGroupeNom (Groupe groupe);



// Donner le type d'une groupe
char*	donnerGroupeType (Groupe groupe);



// Donner le responsable d'un groupe
Usager	donnerResponsable (Groupe groupe);



// Donner le tableau des membres d'un groupe
Usager*	donnerMembres (Groupe groupe);



// Donner les infos d'un groupe
Info*	donnerInfo (Groupe groupe);



// ToString des membres d'un groupe
char*	groupeMembresToString (Groupe groupe);



// ToString des infos d'un groupe
char*	groupeInfoToString (Groupe groupe);



// Nombre des membres dans un groupe
int	donnerNbrMembres (Groupe groupe);



// Nombres des infos d'un groupe
int	donnerNbrInfo (Groupe groupe);



// Ajouter un membre dans un groupe
void	groupeAjouterMembre (Groupe groupe, Usager usager);



// Verifier si un membre fait partie d'un groupe
int	groupeContientMembre (Groupe groupe, char* nom);



// Position d'un membre dans le tableau
int	groupePositionMembre (Groupe groupe, char* nom);



// Enlever un membre d'un groupe
Usager	groupeEnleverMembre (Groupe groupe, char* nom);



// Verifier si un usager a deja un info dans un groupe
int	groupeContientInfo (Groupe groupe, char* nom);



// Position de l'info d'un certain membre dans un groupe
int	groupePositionInfo (Groupe groupe, char* nom);



// Ajouter un info pour un membre
void	groupeAjouterInfo (Groupe groupe, char* nom);



// Augmenter le nombre d'interventions pour un membre
void	groupeAugmenterInterventions (Groupe groupe, char* nom);



// Ajouter la date de depart pour un membre
void	groupeDepartInfo (Groupe groupe, char* nom);



// Reset des infos d'un usager
void 	groupeReinitialiserInfo (Groupe groupe, char* nom);



// Supprimer un groupe
void	supprimerGroupe (Groupe groupe);



// Donner le tableau des demandes pour un groupes
Usager*	donnerDemandes (Groupe groupe);



// ToString des demandes
char*	groupeDemandesToString (Groupe groupe);



// Donner le nombre de demandes pour un groupe
int	donnerNbrDemandes (Groupe groupe);



// Position dans le tableau d'une demande
int	groupePositionDemande (Groupe groupe, char* nom);



// Verifier si on a une demande pour un usager
int	groupeContientDemande (Groupe groupe, char* nom);



// Ajouter une demande pour un usager dans un certain groupe
void	groupeAjouterDemande (Groupe groupe, Usager usager);



// Enlever une demande pour un groupe
Usager	groupeEnleverDemande (Groupe groupe, char* nom);
