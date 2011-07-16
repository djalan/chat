/*
Classe:		usager.h

Description:	Structure objet pour definir une chaine et ses attributs

Auteurs:	Alain Sirois     SIRA15068305
		Philippe Mercure MERP27078708
Date:		18 juin 2011
Cours:		yyyyyyyyyy
Groupe:		30
Travail:	TP2
Professeur:	xxxxxxxxxx
*/


typedef struct chaine* Chaine;


/*
Creer une chaine vide
*/
Chaine chaineCreerVide( int longueur );



/*
Ajouter un caractere a la fin d'une chaine
*/
int chaineAjouter( Chaine ch, unsigned char carac );



/*
Enlever le dernier caractere d'une chaine
*/
int chaineEnlever( Chaine ch );



/*
Retourne le dernier caractere d'une chaine
*/
char* chaineValeur( Chaine ch );



/*
Retourne la longueur d'une chaine
*/
int chaineLongueur( Chaine ch );



/*
Supprimer une chaine
*/
void chaineSupprime( Chaine ch );
