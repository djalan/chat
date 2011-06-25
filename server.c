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
	printf ("%d\n", donnerUsagerAdresse(alain));
	printf ("\n");

	Usager denis = creerUsager ("denis", 22222);
	printf ("%s\n", donnerUsagerNom(denis));
	printf ("%d\n", donnerUsagerAdresse(denis));
	printf ("\n");

	Usager marie = creerUsager ("marie", 33333);
	printf ("%s\n", donnerUsagerNom(marie));
	printf ("%d\n", donnerUsagerAdresse(marie));
	printf ("\n");

	Usager paul = creerUsager ("paul", 33333);
	printf ("%s\n", donnerUsagerNom(paul));
	printf ("%d\n", donnerUsagerAdresse(paul));
	printf ("\n");

	Groupe groupe = creerGroupe ("g1", "public", alain);
	printf ("%s\n", donnerGroupeNom(groupe));
	printf ("%s\n", donnerGroupeType(groupe));
	printf ("%s\n", donnerUsagerNom(donnerResponsable(groupe)));
	printf ("%d\n", donnerUsagerAdresse(donnerResponsable(groupe)));
	printf ("%d\n", donnerNbrMembres(groupe));
	printf ("%d\n", donnerNbrInfo(groupe));
	printf ("\n");

	groupeAjouterMembre (groupe, denis);
	groupeAjouterMembre (groupe, marie);
	groupeAjouterMembre (groupe, paul);
	printf ("%s\n", groupeMembresToString(groupe));

	printf ("%s\n", donnerUsagerNom(alain));
	printf ("%d\n", donnerUsagerAdresse(alain));
	printf ("%s\n", donnerUsagerNom(denis));
	printf ("%d\n", donnerUsagerAdresse(denis));
	printf ("%s\n", donnerUsagerNom(marie));
	printf ("%d\n", donnerUsagerAdresse(marie));
	printf ("%s\n", donnerUsagerNom(paul));
	printf ("%d\n", donnerUsagerAdresse(paul));
	printf ("\n");

	printf ("%s\n", groupeInfoToString(groupe));

	supprimerGroupe (groupe);
	supprimerInfo (alain_info);
	supprimerUsager (alain);

	return 0;
}
