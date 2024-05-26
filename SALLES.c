#include <stdio.h>
#include "SALLES.h"


// la structure salle est declare dans le header  SALLES.h


// creer et retourner une salle

SALLE creerSalle()
{
    SALLE s;

    printf("Entrez l'ID de la salle : ");
    scanf("%u", &s.IdSalle);
    getchar();
    printf("Entrez le nom de la salle : ");
    s.NomSalle = saisir_chaine();
    printf("Entrez la capacité de la salle : ");
    scanf("%u", &s.Capacite);
    getchar();

    return s;
}

// Ajouter une salle Au fichier SALLES
void ajouterSalle()
{
    SALLE s ;
    FILE *f = fopen("SALLES.txt", "a");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    printf("\n entrer les informations de la salle :\n");
    s=creerSalle();
    fprintf(f, "%u %s %u\n", s.IdSalle, s.NomSalle, s.Capacite);

    fclose(f);
}

// Affiche toute les Salles

void afficherToutesSalles()
{
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
        printf("\n\tIdSalle: %u", s.IdSalle);
        printf("\tNomSalle: %s", s.NomSalle);
        printf("\tCapacite: %u", s.Capacite);
    }

    fclose(f);
}

// Ouvre le fichier Salles et Affiche son Nom a partir de son Identifiant passer en Parametre

void chercherSalle(unsigned int idSalle)
{
    FILE* fichier = fopen("SALLES.txt", "r");

    if (fichier == NULL)
    {
        printf("Error opening file\n");
    }

    unsigned int id;
    char nomSalle[100];
    unsigned int valeur;

    while (fscanf(fichier, "%u %s %u", &id, nomSalle, &valeur) == 3)
    {
        if (idSalle == id)
        {
            fclose(fichier);
            printf("\tSalle : %s",nomSalle);
            return;
        }
    }

    fclose(fichier);
    printf("\tSalle : Aucune");
}

