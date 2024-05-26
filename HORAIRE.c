#include <stdio.h>


// declaration de la structure heure
struct Heure
{
    unsigned int h ;
    unsigned int mn ;
};
typedef struct Heure HEURE ;

// declaration de la structure horaire
struct Horaire
{
    unsigned int IdHoraire ;
    HEURE Debut ;
    HEURE FIN ;
};
typedef struct Horaire HORAIRE ;


// creer et retourner une heure

HEURE creerHeure()
{
    HEURE H ;

    printf("\n sous le format h:mn (exemple 12:50) : ");
    scanf("%u:%u", &H.h, &H.mn);
    return H ;

}


// creer et retourner une Horaire
HORAIRE creerHoraire()

{
    HORAIRE HO ;
    printf(" \n entrer l'Id de L'horaire :");
    scanf("%u",&HO.IdHoraire);
    getchar();
    printf("\n entrer l'Heure de debut :");
    HO.Debut = creerHeure();
    printf(" \n entrer l'heure de fin :");
    HO.FIN = creerHeure();

    return HO ;
}

// ajouter un horaire  au fichier HORAIRES

void ajouterHoraire()
{
    HORAIRE h ;
    FILE *f = fopen("HORAIRES.txt", "a");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    printf(" \n entrer les informations de l'Horaire :");
    h = creerHoraire();
    fprintf(f, "%u %u:%u %u:%u\n", h.IdHoraire, h.Debut.h, h.Debut.mn, h.FIN.h, h.FIN.mn);

    fclose(f);
}


// affiche toutes les horaires

void afficherTousHoraire()
{
    FILE *f = fopen("HORAIRES.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    HORAIRE h;
    while (!feof(f))
    {
        fscanf(f, "%u %u:%u %u:%u\n", &h.IdHoraire, &h.Debut.h, &h.Debut.mn, &h.FIN.h, &h.FIN.mn);
        printf("\n\tIdHoraire: %u", h.IdHoraire);
        printf("\tDebut: %u:%u", h.Debut.h, h.Debut.mn);
        printf("\tFIN: %u:%u", h.FIN.h, h.FIN.mn);
    }

    fclose(f);
}



// Ouvre le Fichier Horaire et affiche les Heures de debut et de fin a partir de son identifiant

void chercherHoraire(unsigned int idHoraire)
{
    FILE* fichier = fopen("HORAIRES.txt", "r");

    if (fichier == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    unsigned int id;
    int start_hour, start_minute, end_hour, end_minute;

    while (fscanf(fichier, "%u %d:%d %d:%d", &id, &start_hour, &start_minute, &end_hour, &end_minute) == 5)
    {
        if (idHoraire == id)
        {
            fclose(fichier);
            printf("\tHoraire: %02d:%02d - %02d:%02d\n",start_hour, start_minute, end_hour, end_minute);
            return;
        }
    }

    fclose(fichier);
    printf("\tHoraire: aucune");
}

