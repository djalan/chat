void	listeGroupeAjouter (void* elem);

int	listeGroupeTaille ();
int	listeGroupeContient (char* nom);
int	listeGroupePosition (char* nom);
void*	listeGroupeObtenir (int position);
void*	listeGroupeElement (char* nom);
void*	listeGroupeEnlever (char *nom);
int	listeGroupeEstResponsable (char* nom);
int	listeGroupeEstMembrePrive (char* nom);
char*	listeGroupeToString ();
