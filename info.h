typedef struct info* Info;



char*	obtenirDateHeure ();

Info	creerInfo (char* nom);
void	reinitialiserInfo (Info info);

char*	donnerInfoNom (Info info);
char*	donnerInfoArrivee (Info info);
char*	donnerInfoDepart (Info info);
int	donnerNbrInterventions (Info info);
char*	infoToString (Info info);

void	augmenterInterventions (Info info);
void	inscrireDepart (Info info);

void	supprimerInfo (Info info);
