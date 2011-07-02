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

void	groupeAjouterMembre (Groupe groupe, Usager usager);
int	groupeContientMembre (Groupe groupe, char* nom);
int	groupePositionMembre (Groupe groupe, char* nom);
Usager	groupeEnleverMembre (Groupe groupe, char* nom);
int	groupeContientInfo (Groupe groupe, char* nom);
int	groupePositionInfo (Groupe groupe, char* nom);
void	groupeAjouterInfo (Groupe groupe, char* nom);
void	groupeAugmenterInterventions (Groupe groupe, char* nom);
void	groupeDepartInfo (Groupe groupe, char* nom);
void 	groupeReinitialiserInfo (Groupe groupe, char* nom);
void	supprimerGroupe (Groupe groupe);

Usager*	donnerDemandes (Groupe groupe);
char*	groupeDemandesToString (Groupe groupe);
int	donnerNbrDemandes (Groupe groupe);
int	groupePositionDemande (Groupe groupe, char* nom);
int	groupeContientDemande (Groupe groupe, char* nom);
void	groupeAjouterDemande (Groupe groupe, Usager usager);
Usager	groupeEnleverDemande (Groupe groupe, char* nom);
