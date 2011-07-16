/*
Classe:		info.h

Description:	Structure objet pour definir les infos d'un usager dans un groupe

Auteurs:	Alain Sirois     SIRA15068305
		Philippe Mercure MERP27078708
Date:		18 juin 2011
Cours:		yyyyyyyyyy
Groupe:		30
Travail:	TP2
Professeur:	xxxxxxxxxx
*/



typedef struct info* Info;



// Obtenir date / heure du moment
char*	obtenirDateHeure ();



// Creer une info
Info	creerInfo (char* nom);



// Reset d'un info
void	reinitialiserInfo (Info info);



// Donner le nom d'usager pour une info
char*	donnerInfoNom (Info info);



// Donner l'heure d'arrive d'un usager
char*	donnerInfoArrivee (Info info);



// Donner l'heure de depart d'un usager
char*	donnerInfoDepart (Info info);



// Donner le nombre d'interventions d'un usager
int	donnerNbrInterventions (Info info);



// ToString d'un info
char*	infoToString (Info info);



// Incrementer le nombre d'interventions d'un usager
void	augmenterInterventions (Info info);



// Inscrire la date de depart d'un usager
void	inscrireDepart (Info info);



// Supprimer une info
void	supprimerInfo (Info info);
