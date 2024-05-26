#include <stdio.h>
#include <string.h>
#include "saisir_chaine.h"
#include "ENSEIGNANTS.h"
#include <malloc.h>
#include <string.h>
#include "CLASSES.h"
#include"RESERVATIONS.h"

// declaration de la structure enseignant

struct enseignant
{
    unsigned int IdEnseignant;
    char *NomEnseignant;
    char *PrenomEnseignant;
    unsigned int CniEnseignant;
    unsigned int NumTelEnseignant;
    char *Login;
    char *Password;
};
typedef struct enseignant ENSEIGNANT;


// creation d'un enseignant
ENSEIGNANT creerEnseignant()
{
    ENSEIGNANT e;
    printf(" \n entrer l'Id de L'enseignant : ");
    scanf("%u",&e.IdEnseignant);
    getchar();
    printf(" \n entrer le nom de L'enseignant : ");
    e.NomEnseignant = saisir_chaine();
    printf(" \n entrer le prenom de L'enseignant : ");
    e.PrenomEnseignant = saisir_chaine();
    printf(" \n entrer la CNI de L'enseignant : ");
    scanf("%u",&e.CniEnseignant);
    getchar();
    printf(" \n entrer le numero de telephone de L'enseignant : ");
    scanf("%u",&e.NumTelEnseignant);
    getchar();
    printf(" \n entrer le login de L'enseignant : ");
    e.Login = saisir_chaine();
    printf(" \n entrer le mot de passe de L'enseignant ");
    e.Password = saisir_chaine();
    return e;
}

//ajout d'un enseignant dans le fichier Enseignant
void ajouterEnseignant( )
{
    ENSEIGNANT e ;
    FILE *f = fopen("ENSEIGNANTS.txt", "a");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    printf("\n entrer les information de l'enseignant :");
    e=creerEnseignant();

    fprintf(f, "%u %s %s %u %u %s %s\n", e.IdEnseignant, e.NomEnseignant, e.PrenomEnseignant, e.CniEnseignant, e.NumTelEnseignant, e.Login, e.Password);

    fclose(f);
}



// affichage de tous les enseignant

void afficherTousEnseignants()
{
    FILE *f = fopen("ENSEIGNANTS.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    ENSEIGNANT e;
    e.Login = malloc(sizeof(e.Login));
    e.NomEnseignant = malloc(sizeof(e.NomEnseignant));
    e.PrenomEnseignant = malloc(sizeof(e.PrenomEnseignant));
    e.Password = malloc(sizeof(e.Password));
    while (!feof(f))
    {
        fscanf(f, "%u %[^ ] %[^ ] %u %u %[^ ] %[^\n]\n", &e.IdEnseignant, e.NomEnseignant, e.PrenomEnseignant, &e.CniEnseignant, &e.NumTelEnseignant, e.Login, e.Password);
        printf("\n\nIdEnseignant: %u", e.IdEnseignant);
        printf("\nNomEnseignant: %s", e.NomEnseignant);
        printf("\nPrenomEnseignant: %s", e.PrenomEnseignant);
        printf("\nCniEnseignant: %u", e.CniEnseignant);
        printf("\nNumTelEnseignant: %u", e.NumTelEnseignant);
        printf("\nLogin: %s", e.Login);
        printf("\nPassword: %s", e.Password);
    }

    fclose(f);
}

// Cette fonction verifie si un login et un mot de passe existe dans le fichier des ENSEIGNANTS et retourne
// l'IdEnseignant pour lequel il y'a correspondance elle retourne 0 sinon
unsigned int verifieEnseignant(char *login, char *password)
{
    FILE *f = fopen("ENSEIGNANTS.txt", "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return 0;
    }

    ENSEIGNANT e;
    e.Login = malloc(sizeof(e.Login));
    e.NomEnseignant = malloc(sizeof(e.NomEnseignant));
    e.PrenomEnseignant = malloc(sizeof(e.PrenomEnseignant));
    e.Password = malloc(sizeof(e.Password));
    while (fscanf(f, "%u %s %s %d %d %s %s\n", &e.IdEnseignant, e.NomEnseignant, e.PrenomEnseignant, &e.CniEnseignant, &e.NumTelEnseignant, e.Login, e.Password) != EOF)
    {
        if (strcmp(e.Login, login) == 0)
        {
            if (strcmp(e.Password, password) == 0)
            {
                fclose(f);
                return e.IdEnseignant;
            }
            else
            {
                printf("Erreur : Le mot de passe ne correspond pas au login fourni.\n");
                fclose(f);
                return 0;
            }
        }
    }
    printf("Erreur : Aucun Enseignant avec le login fourni n'a été trouvé.\n");
    fclose(f);
}



// le menu des differentes actions possibles pour un enseignant

void menu_enseignant()
{
    unsigned int ide ;
    char * login, *password ;
    printf("\n Entrer votre Login :");
    getchar();
    login = saisir_chaine();
    printf(" \n Entrer votre mot de passe :");
    password = saisir_chaine() ;
    ide = verifieEnseignant(login,password);

    if (ide)
    {
        unsigned int  choix = 0 ;
        unsigned int idc = 0, idcr = 0, ids = 0,idm = 0, nb = 0, idrsupp = 0, *idcsupp = NULL ;
        do
        {

            printf(" \n\n\t\t\t------- Veuillez faire votre choix --------\n ");
            printf( " \n 1. Pour effectuer une reservation ");
            printf( " \n 2. Pour annuler une reservation ");
            printf( " \n 3. Quitter ");
            printf(" \n choix ====> ");
            scanf("%u",&choix);

            switch(choix)
            {
            case 1 :
                printf( " \n\t\t\t **********les differentes classes***********\n ");
                afficherToutesClasse();
                printf("\n choisir la classe concernee en entrant son Id : ");
                scanf("%u",&idc);
                getchar();
                printf("\n voici les creneau disponible pour cette classe \n");
                afficherDisponibiliteClasse(idc,&nb);
                if( nb == 0)
                {
                    printf(" il n'y a aucune disponibilite pour cette classe ");
                }
                else
                {
                    printf(" \n entrer l'Id du Cour correspondant a votre choix : ");
                    scanf("%u",&idcr);
                    getchar();
                    afficherSallesDisponibles(idcr);
                    printf("\n entrer l'Id de la salle que vous souhaitez :");
                    scanf("%u",&ids);
                    getchar();
                    afficherTousMatieres();
                    printf("\n entrer l'Id de la matiere concerne :");
                    scanf("%u",&idm);
                    getchar();
                    programmerCour(idcr,ids,idm);
                    ajouterReservation(idcr,ide);
                    printf(" \n");
                }

                break;

            case 2 :
                afficherResevationEnseignant(ide);
                printf(" \n Veuillez choisir la reservation concernee :");
                scanf("%u",&idrsupp);
                printf("%u",idrsupp);
                getchar();
                idcsupp = recupererIdCour(idrsupp);
                printf("%u",*idcsupp);
                annulerCour(idcsupp);
                supprimerReservation(idrsupp);
                afficherTousCours();
                break ;
            case 3 :
                printf(" \n Fermeture du menu ");
                break;
            default :
                printf("\n Choix inexistant");
                break ;

            }

        }
        while( choix != 3) ;


    }
}




