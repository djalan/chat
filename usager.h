/*
Classe:		usager.h

Description:	Structure objet pour definir un usager et ses attributs

Auteurs:	Alain Sirois     SIRA15068305
		Philippe Mercure MERP27078708
Date:		18 juin 2011
Cours:		yyyyyyyyyy
Groupe:		30
Travail:	TP2
Professeur:	xxxxxxxxxx
*/



typedef struct usager* Usager;



/*
Creer un usager et initialiser son nombre de fichier resultat a 1
*/
Usager	creerUsager (char* nom, int nsd);



// Creer une copie d'un usager
Usager	creerUsagerCopie (Usager usager);



/*
Retourner le nom d'un Usager
*/
char*	donnerUsagerNom (Usager usager);



/*
Retourner le nombre de fichiers resultats d'un usager
*/
int	donnerUsagerNsd (Usager usager);



// Supprimer un usager
void	supprimerUsager (Usager usager);
