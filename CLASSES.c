#include <stdio.h>
#include "CLASSES.h"


//declaration de la structure d'une classe

struct classe
{
    unsigned int IdClasse ;
    char * NomClasse ;
};
typedef struct classe CLASSE ;

// Creation d'une classe

CLASSE creerClasse()
{
    CLASSE c ;
    printf(" \n entrer l'Id de la Classe: ");
    scanf("%u",&c.IdClasse);
    getchar();
    printf(" \n entrer le nom de La Classe : ");
    c.NomClasse = saisir_chaine();
    return c ;
}

// Permet d'ajouter une nouvelle Classe dans le fichier CLASSES.txt
void ajouterClasse()
{
    CLASSE c ;
    FILE *f = fopen("CLASSES.txt", "a");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    printf("\n entrer les information de la matiere :");
    c= creerClasse();

    fprintf(f, "%u %s\n", c.IdClasse, c.NomClasse);

    fclose(f);
}

// Permet d'afficher les informations de toutes les classes a partir du Fichier
void afficherToutesClasse()
{
    FILE *f = fopen("CLASSES.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    CLASSE c;
    c.NomClasse = malloc(sizeof(c.NomClasse));
    while (!feof(f))
    {
        fscanf(f, "%u %[^\n]\n", &c.IdClasse ,c.NomClasse);
        printf("\n\tIdClasse: %u", c.IdClasse);
        printf("\tNomClasse: %s", c.NomClasse);
    }

    fclose(f);
}

