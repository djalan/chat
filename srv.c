#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "groupe.h"
#include "listeUsager.h"
#include "listeGroupe.h"



int main () {

	Info alain_info = creerInfo("alain");
	printf ("%s\n", donnerInfoNom(alain_info));
	printf ("%s\n", donnerInfoArrivee(alain_info));
	printf ("%s\n", donnerInfoDepart(alain_info));
	printf ("%d\n", donnerNbrInterventions(alain_info));
	printf ("\n");
	augmenterInterventions (alain_info);
	inscrireDepart (alain_info);
	printf ("%s\n", donnerInfoNom(alain_info));
	printf ("%s\n", donnerInfoArrivee(alain_info));
	printf ("%s\n", donnerInfoDepart(alain_info));
	printf ("%d\n", donnerNbrInterventions(alain_info));
	printf ("\n");

	Usager alain = creerUsager ("alain", 11111);
	printf ("%s\n", donnerUsagerNom(alain));
	printf ("%d\n", donnerUsagerNsd(alain));
	printf ("\n");

	Usager denis = creerUsager ("denis", 22222);
	printf ("%s\n", donnerUsagerNom(denis));
	printf ("%d\n", donnerUsagerNsd(denis));
	printf ("\n");

	Usager marie = creerUsager ("marie", 33333);
	printf ("%s\n", donnerUsagerNom(marie));
	printf ("%d\n", donnerUsagerNsd(marie));
	printf ("\n");

	Usager paul = creerUsager ("paul", 33333);
	printf ("%s\n", donnerUsagerNom(paul));
	printf ("%d\n", donnerUsagerNsd(paul));
	printf ("\n");

	Groupe groupe = creerGroupe ("g1", "public", alain);
	printf ("%s\n", donnerGroupeNom(groupe));
	printf ("%s\n", donnerGroupeType(groupe));
	printf ("%s\n", donnerUsagerNom(donnerResponsable(groupe)));
	printf ("%d\n", donnerUsagerNsd(donnerResponsable(groupe)));
	printf ("%d\n", donnerNbrMembres(groupe));
	printf ("%d\n", donnerNbrInfo(groupe));
	printf ("\n");

	groupeAjouterMembre (groupe, denis);
	groupeAjouterMembre (groupe, marie);
	groupeAjouterMembre (groupe, paul);
	printf ("%s\n", groupeMembresToString(groupe));
	printf ("%s\n", groupeInfoToString(groupe));
	printf ("\n");

	printf ("%s\n", donnerUsagerNom(alain));
	printf ("%d\n", donnerUsagerNsd(alain));
	printf ("%s\n", donnerUsagerNom(denis));
	printf ("%d\n", donnerUsagerNsd(denis));
	printf ("%s\n", donnerUsagerNom(marie));
	printf ("%d\n", donnerUsagerNsd(marie));
	printf ("%s\n", donnerUsagerNom(paul));
	printf ("%d\n", donnerUsagerNsd(paul));
	printf ("\n");

	groupeAugmenterInterventions(groupe,"alain");
	groupeAugmenterInterventions(groupe,"alain");
	groupeAugmenterInterventions(groupe,"denis");
	groupeAugmenterInterventions(groupe,"alain");
	groupeAugmenterInterventions(groupe,"marie");
	printf ("%s\n", groupeInfoToString(groupe));
	
	groupeEnleverMembre(groupe,"alain");
	printf ("%s\n", groupeMembresToString(groupe));
	printf ("%s\n", groupeInfoToString(groupe));
	groupeAugmenterInterventions(groupe,"denis");
	printf ("%s\n", groupeInfoToString(groupe));
	groupeAjouterMembre (groupe, alain);
	printf ("%s\n", groupeMembresToString(groupe));
	printf ("%s\n", groupeInfoToString(groupe));
	printf ("\n");

	listeUsagerAjouter (alain);
	listeUsagerAjouter (denis);
	listeUsagerAjouter (marie);
	printf ("%s\n", listeUsagerToString());
	listeUsagerEnlever ("alain");
	printf ("%s\n", listeUsagerToString());
	printf ("\n");

	Groupe groupe2 = creerGroupe ("g2", "public", denis);

	listeGroupeAjouter (groupe);
	listeGroupeAjouter (groupe2);
	printf ("%s\n", listeGroupeToString());
	listeGroupeEnlever ("g2");
	printf ("%s\n", listeGroupeToString());
	printf ("\n");

	supprimerGroupe (groupe);
	supprimerInfo (alain_info);
	printf ("%s\n", donnerUsagerNom(alain));
	printf ("%d\n", donnerUsagerNsd(alain));
	supprimerUsager (alain);

	return 0;
}