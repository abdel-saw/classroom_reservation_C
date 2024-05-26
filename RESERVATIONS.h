struct reservation
{
    unsigned int IdReservation ;
    unsigned int IdCour  ;
    unsigned int IdEnseignant ;

};
typedef struct reservation RESERVATION ;

void ajouterReservation(unsigned int , unsigned int );
void afficherTousReservations();
void afficherResevationEnseignant (unsigned int );
void supprimerReservation(unsigned int );
unsigned int * recupererIdCour(unsigned int );

