#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#include "usager.h"
#include "groupe.h"
//#include "info.h"
#include "listeUsager.h"
#include "listeGroupe.h"



int main () {

	Info alain_info = creerInfo("Alain");
	printf ("%s\n", donnerInfoNom(alain_info));
	printf ("%s\n", donnerInfoArrivee(alain_info));
	printf ("%s\n", donnerInfoDepart(alain_info));
	printf ("%d\n", donnerNbrInterventions(alain_info));

	augmenterInterventions (alain_info);
	inscrireDepart (alain_info);

	printf ("%s\n", donnerInfoNom(alain_info));
	printf ("%s\n", donnerInfoArrivee(alain_info));
	printf ("%s\n", donnerInfoDepart(alain_info));
	printf ("%d\n", donnerNbrInterventions(alain_info));

	return 0;
}
