struct salle
{
    unsigned int IdSalle ;
    char * NomSalle ;
    unsigned int Capacite ;
};
typedef struct salle SALLE ;

void ajouterSalle();
void afficherToutesSalles();
void chercherSalle(unsigned int );
