#include <stdio.h>
#include "MATIERES.h"

//declaration de la structure matiere

struct matiere
{
    unsigned int IdMatiere ;
    unsigned int IdEnseignant ;
    char * Nommatiere ;

};

typedef struct matiere MATIERE ;


// creer et retourner une matiere

MATIERE creerMatiere()
{
    MATIERE m ;
    printf(" \n entrer l'Id de la matiere : ");
    scanf("%u",&m.IdMatiere);
    getchar();
    printf(" \n entrer le nom de La matiere : ");
    m.Nommatiere = saisir_chaine();
    printf("\n entrer l'Id de l'enseignant associe :");
    scanf("%u",&m.IdEnseignant);
    getchar();

    return m ;
}

// Ajouter matiere au fichier
void ajouterMatiere( )
{
    MATIERE m ;
    FILE *f = fopen("MATIERES.txt", "a");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    printf("\n entrer les information de la matiere :");
    m=creerMatiere();

    fprintf(f, "%u %s %u\n", m.IdMatiere, m.Nommatiere, m.IdEnseignant);

    fclose(f);
}
// Afficher toutes les matieres

void afficherTousMatieres()
{
    FILE *f = fopen("MATIERES.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    MATIERE m;
    m.Nommatiere = malloc(sizeof(m.Nommatiere));

    while (!feof(f))
    {
        fscanf(f, "%u %[^ ] %u\n", &m.IdMatiere, m.Nommatiere, &m.IdEnseignant);
        printf("\n\tIdMatiere: %u", m.IdMatiere);
        printf("\tNomMatiere: %s", m.Nommatiere);
    }

    fclose(f);
}

//Recherche une matiere dans le fichier matiere a partir de son Id et retourne son Nom

void chercherMatiere(unsigned int idMatiere)
{
    FILE* fichier = fopen("MATIERES.txt", "r");

    if (fichier == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    char nomMatiere[100];
    unsigned int idm;
    unsigned int ide;

    while (fscanf(fichier, "%u %s %u", &idm, nomMatiere, &ide) == 3)
    {
        if (idMatiere == idm)
        {
            fclose(fichier);
            printf("\tMatiere: %s",nomMatiere);
            return;
        }
    }
    printf("\t Matiere: Aucune");
    fclose(fichier);
}
