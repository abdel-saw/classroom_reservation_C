#include <stdio.h>
#include"SALLES.h"
#include <stdbool.h>
#include"COUR.h"

// la structure COUR et celle de DATE sont declare dans le header "COUR.h"

// Permet de creer et retourner une Date
DATE creerDate()
{
    DATE d;
    printf("Entrez la date sous le format j/m (exemple 12/12) : ");
    scanf("%u/%u", &d.j, &d.m);
    return d;
}

//Permet de creer et retourner un Cour
COUR creerCour()
{
    COUR c;
    printf("Entrez l'ID du cours : ");
    scanf("%u", &c.IdCour);
    getchar();
    printf("Entrez l'ID de la salle : ");
    scanf("%u", &c.IdSalle);
    getchar();
    printf("Entrez l'ID de l'horaire : ");
    scanf("%u", &c.IdHoraire);
    getchar();
    printf("Entrez l'ID de la classe : ");
    scanf("%u", &c.IdClasse);
    getchar();
    printf("Entrez l'ID de la matière : ");
    scanf("%u", &c.IdMatiere);
    getchar();
    c.date = creerDate();
    return c;
}

// Permet d'ajouter un Cour au fichier COURS

void ajouterCour()
{
    COUR c ;
    FILE *f = fopen("COURS.txt", "a");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    printf(" \n entrer les informations du cours: \n");
    c = creerCour();
    fprintf(f, "%u %u %u %u %u %u/%u\n", c.IdCour, c.IdSalle, c.IdHoraire, c.IdClasse, c.IdMatiere, c.date.j, c.date.m);

    fclose(f);
}

// Ouvre le fichier COURS et affiche ses informations

void afficherTousCours()
{
    FILE *f = fopen("COURS.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    COUR c;
    while (!feof(f))
    {
        fscanf(f, "%u %u %u %u %u %u/%u\n", &c.IdCour, &c.IdSalle, &c.IdHoraire, &c.IdClasse, &c.IdMatiere, &c.date.j, &c.date.m);

            printf("\n\tIdCour: %u", c.IdCour);
            chercherHoraire(c.IdHoraire);
            chercherSalle(c.IdSalle);
            chercherMatiere(c.IdMatiere);
            printf("\tDate: %u/%u \n", c.date.j, c.date.m);
            printf("-----------------------------------------------------------------------------------");


    }

    fclose(f);
}


// Ouvre le fichier COURS et recherche la disponibilite d'une classe a partir de son idClasse Passer en parametre
// c'est a dire les creneaux libres d'une classe ( par convention les creneaux libres sont reconnus par IdSalle = 0 ou IdMatiere = 0 )
// le parametre nb sert de variable d'etat s'il est nul a la sortie alors il n'existe aucun creneau disponible pour cette classe

void afficherDisponibiliteClasse(unsigned int idc,unsigned int *nb)
{
    FILE *f = fopen("COURS.txt", "r");
    * nb = 0 ;
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return NULL;
    }

    COUR c;
    while (!feof(f))
    {
        fscanf(f, "%u %u %u %u %u %u/%u\n", &c.IdCour, &c.IdSalle, &c.IdHoraire, &c.IdClasse, &c.IdMatiere, &c.date.j, &c.date.m);
        if (c.IdClasse == idc && c.IdMatiere == 0)
        {

            printf("\n\tIdCour: %u", c.IdCour);
            chercherHoraire(c.IdHoraire);
            chercherSalle(c.IdSalle);
            chercherMatiere(c.IdMatiere);
            printf("\tDate: %u/%u \n", c.date.j, c.date.m);
            printf("-----------------------------------------------------------------------------------");

            (*nb) ++ ;
        }
    }

    fclose(f);

}

// Permet de recuperer l'IdHoraire et la date associe a un cour dont l'id est passe en parametre
//le choix du passage par adresse pour date et idHoraire se justifie par le fait que cette fonction sera appele
// a l'interieur d'une autre fonction ci dessous "afficherSallesNonUtilisees" qui sera par la suite utilise pour afficher
// toutes les sallles disponibles pour la date et l'heure concerne

void recupererDateEtHoraire(unsigned int idCour, DATE* date, unsigned int* idHoraire)
{
    FILE *f = fopen("COURS.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    COUR c;
    while (!feof(f))
    {
        fscanf(f, "%u %u %u %u %u %u/%u\n", &c.IdCour, &c.IdSalle, &c.IdHoraire, &c.IdClasse, &c.IdMatiere, &c.date.j, &c.date.m);
        if (c.IdCour == idCour)
        {
            *date = c.date;
            *idHoraire = c.IdHoraire;
            break;
        }
    }

    fclose(f);
}

// Cette fonction ouvre le fichier COURS et recupere dans un tableau les IdSalles de tous les cours etant programme a la meme date et a la meme
// Horaire qu'un cour dont L'idCour , L'IdHoraire ainsi que la date sont passe en parametre
// avec ce tableau des salles occupe pendant une horaire et une date  precise on pourra par la suite ouvrir le Fichier des SALLES et
// afficher toutes les salles dont les IdSalle ne se trouvent pas dans le tableau ce qui implique qu'elle sont libres pour
// l'horaire et la date concerne on pourra alors proposer un choix de salles libre a un enseignant voulant effectuer une
// reservation , si aucune salle n'est disponible on affiche le message qu'aucune salle n'est disponible

unsigned int* recupererIdSalleOccupe(unsigned int idCour, DATE date, unsigned int idHoraire, int* taille)
{
    FILE *f = fopen("COURS.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return NULL;
    }

    COUR c;
    unsigned int* Ids = NULL;
    *taille = 0;
    while (!feof(f))
    {
        fscanf(f, "%u %u %u %u %u %u/%u\n", &c.IdCour, &c.IdSalle, &c.IdHoraire, &c.IdClasse, &c.IdMatiere, &c.date.j, &c.date.m);
        if (c.IdCour != idCour && c.IdHoraire == idHoraire && c.date.j == date.j && c.date.m == date.m && c.IdSalle != 0)
        {
            Ids = realloc(Ids, (*taille + 1) * sizeof(unsigned int));
            Ids[*taille] = c.IdSalle;
            (*taille)++;
        }
    }

    fclose(f);
    return Ids;
}



// la fonction qui permet d'afficher les salles non utilises pour l'horaire et la date concerne comme decrit plus haut

void afficherSallesNonUtilisees(unsigned int idCour, DATE date, unsigned int idHoraire)
{
    int taille, nb = 0;
    unsigned int* Ids = recupererIdSalleOccupe(idCour, date, idHoraire, &taille);


    FILE *f = fopen("SALLES.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    SALLE s;
    s.NomSalle = malloc(sizeof(s.NomSalle));
    while (!feof(f))
    {
        fscanf(f, "%u %[^ ] %u\n", &s.IdSalle, s.NomSalle, &s.Capacite);
        bool estUtilisee = false;
        for (int i = 0; i < taille; i++)
        {
            if (Ids[i] == s.IdSalle)
            {
                estUtilisee = true;
                break;
            }
        }
        if (!estUtilisee)
        {
            printf("\n\tIdSalle: %u", s.IdSalle);
            printf("\tNomSalle: %s", s.NomSalle);
            printf("\tCapacite: %u", s.Capacite);
            nb++ ;
        }
    }
    fclose(f);
    free(Ids);
    if( nb == 0)
    {
        printf("\n aucune salle n'est disponible ");
    }
}

// la fonction qui fait appel au trois precedentes fonction pour afficher toutes les salles disponibles pour un IdCour
//( associe a un IdHoraire et une date unique );

void afficherSallesDisponibles(unsigned int idCour)
{

    DATE date;
    unsigned int idHoraire;
    recupererDateEtHoraire(idCour, &date, &idHoraire);

    afficherSallesNonUtilisees(idCour, date, idHoraire);

}

// Cette fonction sera utile pour un admin lorsqu'il veut programmer un cour il suffira d'afficher tous les cours a partir du fichier
//COURS et de selection l'IdCour du cour qu'il souhaite et n'etant pas deja associe a une matiere et une salle
//(IdSalle = 0 et IdMatiere =0 ) puis il luis sera demande d'entrer l'Id de la matiere et l'Id de la Salle qui seront sotcker
// Pour afire appel a la fonction
//cette fonction est egalement utilise lorsqu'un enseignant effectue une reservation
void programmerCour(unsigned int idCour,unsigned int idsalle, unsigned int idmatiere)
{
    FILE *f = fopen("COURS.txt", "r+");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    COUR c;
    long position;
    while (!feof(f))
    {
        position = ftell(f);
        fscanf(f, "%u %u %u %u %u %u/%u\n", &c.IdCour, &c.IdSalle, &c.IdHoraire, &c.IdClasse, &c.IdMatiere, &c.date.j, &c.date.m);
        if (c.IdCour == idCour)
        {
            c.IdSalle = idsalle ;
            c.IdMatiere = idmatiere ;

            fseek(f, position, SEEK_SET);
            fprintf(f, "%u %u %u %u %u %u/%u\n", c.IdCour, c.IdSalle, c.IdHoraire, c.IdClasse, c.IdMatiere, c.date.j, c.date.m);
            printf(" \n Reservation effectuer avec succes !!");
            break;
        }
    }

    fclose(f);
}
//Cette Fonction Ouvre Fichier COURS et modifie les attributs Idsalle et IdMatiere par Idsalle = 0 et IdMatiere = 0
// pour l'IdCour du cour passe en parametre
// elle permet a un enseignant d'annuler une reservation au'il a effectue et a un administrateur d'annuler un cour
void annulerCour( unsigned int *idc)
{
    FILE *f = fopen("COURS.txt", "r+");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    COUR c;
    long position;
    while (!feof(f))
    {
        position = ftell(f);
        fscanf(f, "%u %u %u %u %u %u/%u\n", &c.IdCour, &c.IdSalle, &c.IdHoraire, &c.IdClasse, &c.IdMatiere, &c.date.j, &c.date.m);
        if (c.IdCour == *idc)
        {
            c.IdSalle = 0 ;
            c.IdMatiere = 0 ;

            fseek(f, position, SEEK_SET);
            fprintf(f, "%u %u %u %u %u %u/%u\n", c.IdCour, c.IdSalle, c.IdHoraire, c.IdClasse, c.IdMatiere, c.date.j, c.date.m);
            break;
        }
    }

    fclose(f);
}

// Cette Fonction Affiche les cours d'une classe c'est a dire son emploi du temps

void afficherCoursClasse()
{
    unsigned int idcls ;
    printf("\n\t\t\t\t ******* les classes et leurs Id*******\n");
    afficherToutesClasse();

    printf(" \n\n\t\t Entrer l'identifiant de la classe : ");
    scanf("%u",&idcls);
    getchar();

    FILE *f = fopen("COURS.txt", "r");

    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return NULL;
    }
    COUR c;
    while (!feof(f))
    {
        fscanf(f, "%u %u %u %u %u %u/%u\n", &c.IdCour, &c.IdSalle, &c.IdHoraire, &c.IdClasse, &c.IdMatiere, &c.date.j, &c.date.m);
        if (c.IdClasse == idcls && c.IdSalle != 0)
        {

            printf("\n\tIdCour: %u", c.IdCour);
            chercherHoraire(c.IdHoraire);
            chercherSalle(c.IdSalle);
            chercherMatiere(c.IdMatiere);
            printf("\tDate: %u/%u \n", c.date.j, c.date.m);
            printf("-----------------------------------------------------------------------------------");


        }
    }

    fclose(f);
}
