
struct Date
{
    unsigned int j ;
    unsigned int m;
};
typedef struct Date DATE ;



struct Cour
{
    unsigned int IdCour ;
    unsigned int IdSalle ;
    unsigned int IdHoraire ;
    unsigned int IdClasse ;
    unsigned int IdMatiere ;
    DATE date ;
};
typedef struct Cour COUR ;

void ajouterCour();
void annulerCour( unsigned int * );
void programmerCour(unsigned int ,unsigned int, unsigned int );
void afficherSallesDisponibles(unsigned int );
void afficherDisponibiliteClasse(unsigned int,unsigned int * );
void afficherTousCours();
