

// Ajouter un usager dans la liste
void	listeUsagerAjouter (void* elem);



// Donner le nombre d'usagers dans la liste
int	listeUsagerTaille ();



// Verifier si un usager est dans la liste
int	listeUsagerContient (char* nom);



// Donner la poistion d'un usager dans la liste
int	listeUsagerPosition (char* nom);



// Retourner l'usager a une certaine position
void*	listeUsagerObtenir (int position);



// Retourner l'usager ayant un certain nom
void*	listeUsagerElement (char* nom);



// Enlever un usager de la liste
void*	listeUsagerEnlever (char *nom);



// ToString des usagers
char*	listeUsagerToString ();



// Donner le nom d'usager portant un certain socket descriptor
char*	listeUsagerTrouverNom (int nsd);



// Donner le socket descriptor d'un  usager
int	listeUsagerTrouverNsd (char* nom);
