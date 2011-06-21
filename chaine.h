


typedef struct chaine* Chaine;



Chaine chaineCreerVide( int longueur );
int chaineAjouter( Chaine ch, unsigned char carac );
int chaineEnlever( Chaine ch );
char* chaineValeur( Chaine ch );
int chaineLongueur( Chaine ch );
void chaineSupprime( Chaine ch );
