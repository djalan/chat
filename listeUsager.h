void	listeUsagerAjouter (void* elem);

int	listeUsagerTaille ();
int	listeUsagerContient (char* nom);
int	listeUsagerPosition (char* nom);
void*	listeUsagerObtenir (int position);
void*	listeUsagerElement (char* nom);
void*	listeUsagerEnlever (char *nom);
char*	listeUsagerToString ();

char*	listeUsagerTrouverNom (int nsd);
int	listeUsagerTrouverNsd (char* nom);
