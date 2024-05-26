#include <stdio.h>
#include"RESERVATIONS.h"
#include"COUR.h"


// la Structure RESERVATIONS est declare dans le header RESERVATIONS.h

static unsigned int NBR = 0 ;// Compteur pour IdResevation auto incrementable


// Ajouter une reservation au Fichier RESERVATIONS
void ajouterReservation(unsigned int idcour, unsigned int ide)
{
    struct reservation res;
    res.IdReservation = ++NBR;
    res.IdCour = idcour;
    res.IdEnseignant = ide;

    FILE *file = fopen("RESERVATIONS.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%u %u %u\n", res.IdReservation, res.IdCour, res.IdEnseignant);
        fclose(file);
    }
    else
    {
        printf("Erreur d'ouverture du fichier RESERVATIONS\n");
    }
}

// afficher toutes les reservations a partir du Fichier
void afficherTousReservations()
{
    RESERVATION res;

    FILE *file = fopen("RESERVATIONS.txt", "r");
    if (file != NULL)
    {
        while (fscanf(file, "%u %u %u\n", &res.IdReservation, &res.IdCour, &res.IdEnseignant) == 3)
        {
            printf("IdReservation: %u, IdCour: %u, IdEnseignant: %u\n", res.IdReservation, res.IdCour, res.IdEnseignant);
        }
        fclose(file);
    }
    else
    {
        printf("Erreur d'ouverture du fichier RESERVATIONS\n");
    }
}



// Affiche les reservations d'un enseignant a partir de son IdEnseignant passer en parametre
//Utile pour afficher les rersevation d'un enseignant lorsqu'il choisi d'annuler une reservation
void afficherResevationEnseignant (unsigned int ide)
{
    FILE *f = fopen("RESERVATIONS.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    RESERVATION r ;
    while (!feof(f))
    {
        fscanf(f, "%u %u %u\n", &r.IdReservation,&r.IdCour,&r.IdEnseignant);
        if(r.IdEnseignant == ide)
        {
            FILE *f2 = fopen("COURS.txt", "r");
            COUR c ;
            while(!feof(f2))
            {
                fscanf(f2, "%u %u %u %u %u %u/%u\n", &c.IdCour, &c.IdSalle, &c.IdHoraire, &c.IdClasse, &c.IdMatiere, &c.date.j, &c.date.m);
                if(c.IdCour = r.IdCour)
                {
                    printf("\n\tIdReservation: %u", r.IdReservation);
                    printf("\tIdCour: %u", c.IdCour);
                    chercherHoraire(c.IdHoraire);
                    chercherSalle(c.IdSalle);
                    chercherMatiere(c.IdMatiere);
                    printf("\tDate: %u/%u \n", c.date.j, c.date.m);
                    printf("-----------------------------------------------------------------------------------");

                    break ;
                }

            }
            fclose(f2);
        }

    }

    fclose(f);
}

/*Recupere L'id d'un Cour associe a une reservation utile pour modifier les informations d'un cours
dans le Fichier COURS lorsqu'un enseignant effectue une annulation */

unsigned int * recupererIdCour(unsigned int idr)
{
    RESERVATION res;
    unsigned int *aux ;
    FILE *file = fopen("RESERVATIONS.txt", "r");
    if (file != NULL)
    {
        while (fscanf(file, "%u %u %u\n", &res.IdReservation, &res.IdCour, &res.IdEnseignant) == 3)
        {
            if(res.IdReservation = idr)
            {
                fclose(file);
                *aux = res.IdCour;
                return aux ;
            }
        }

    }
    else
    {
        printf("Erreur d'ouverture du fichier RESERVATIONS\n");
        fclose(file);
        return 0 ;
    }

}
// cette fonction supprime  la reseravation dont l'IdReservation est passe en parmetre dans le fichier RESERVATIONS

void supprimerReservation(unsigned int idr)
{
    FILE *f = fopen("RESERVATIONS.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    RESERVATION r;
    while (fscanf(f, "%u %u %u\n", &r.IdReservation, &r.IdCour, &r.IdEnseignant) == 3)
    {
        if (r.IdReservation != idr)
        {
            fprintf(temp, "%u %u %u\n", r.IdReservation, r.IdCour, r.IdEnseignant);
        }
    }

    fclose(f);
    fclose(temp);

    remove("RESERVATIONS.txt");
    rename("temp.txt", "RESERVATIONS.txt");
}


