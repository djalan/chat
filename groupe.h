#include "usager.h"
#include "info.h"

typedef struct groupe* Groupe;



Groupe	creerGroupe (char* nom, char* type, Usager responsable);

char*	donnerGroupeNom (Groupe groupe);
char*	donnerGroupeType (Groupe groupe);
Usager	donnerResponsable (Groupe groupe);
Usager*	donnerMembres (Groupe groupe);
Info*	donnerInfo (Groupe groupe);
char*	groupeMembresToString (Groupe groupe);
char*	groupeInfoToString (Groupe groupe);

int	donnerNbrMembres (Groupe groupe);
int	donnerNbrInfo (Groupe groupe);

void	groupeAjouter (Groupe groupe, Usager usager);
void	supprimerGroupe (Groupe groupe);
