typedef struct info* Info;



Info	creerInfo (char* nom);

char*	donnerInfoNom (Info info);
char*	donnerInfoArrivee (Info info);
char*	donnerInfoDepart (Info info);
int	donnerNbrInterventions (Info info);
char*	infoToString (Info info);

void	augmenterInterventions (Info info);
void	inscrireDepart (Info info);

void	supprimerInfo (Info info);
