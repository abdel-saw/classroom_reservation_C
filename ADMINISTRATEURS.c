#include <stdio.h>
#include "ADMINISTRATEURS.h"
#include"ENSEIGNANTS.h"
#include"COUR.h"
#include "HORAIRE.h"
#include "CLASSES.h"
#include "MATIERES.h"
#include "RESERVATIONS.h"
#include "SALLES.h"

// declarartion de la structure administrateur
struct administrateur

{
    unsigned int IdAdmin ;
    char * NomAdmin ;
    char * PrenomAdmin ;
    char * Login ;
    char * Password ;
};
typedef struct administrateur ADMIN ;



// Création d'un nouvel administrateur
ADMIN creerAdmin()
{

    ADMIN admin ;
    printf(" \n Entrer l'Id de l'administrateur : ");
    scanf("%u",&admin.IdAdmin);
    getchar();
    printf( "\n Entrer le Nom de l'administrateur :") ;
    admin.NomAdmin = saisir_chaine();
    printf( "\n Entrer le Prenom de l'administrateur :") ;
    admin.PrenomAdmin = saisir_chaine();
    printf( "\n Entrer le Login de l'administrateur :") ;
    admin.Login = saisir_chaine();
    printf( "\n Entrer le mot de passe de l'administrateur :") ;
    admin.Password = saisir_chaine();

    return admin;
}

// Ajout d'un nouvel administrateur dans le fichier ADMINISTRATEURS.txt
void ajouterAdmin()
{
    ADMIN admin ;
    FILE* file = fopen("ADMINISTRATEURS.txt", "a");
    admin = creerAdmin();
    if (file != NULL)
    {
        fprintf(file, "%u %s %s %s %s\n", admin.IdAdmin, admin.NomAdmin, admin.PrenomAdmin, admin.Login, admin.Password);
        fclose(file);
    }
    else
    {
        printf("\n Erreur d'ouverture du fichier ");
    }
}

// Affichage de tous les adminstrateurs a partir du fichier
void afficherTousAdmins()
{
    FILE* file = fopen("ADMINISTRATEURS.txt", "r");
    if (file != NULL)
    {
        ADMIN admin;
        admin.Login = malloc(sizeof(admin.Login));
        admin.NomAdmin = malloc(sizeof(admin.NomAdmin));
        admin.PrenomAdmin = malloc(sizeof(admin.PrenomAdmin));
        admin.Password = malloc(sizeof(admin.Password));
        while (fscanf(file, "%u %s %s %s %s\n", &admin.IdAdmin, admin.NomAdmin, admin.PrenomAdmin, admin.Login, admin.Password) != EOF)
        {
            printf("ID: %u, Nom: %s, Prenom: %s, Login: %s, Password: %s\n", admin.IdAdmin, admin.NomAdmin, admin.PrenomAdmin, admin.Login, admin.Password);
        }
        fclose(file);
    }
    else
    {
        printf("\n Ouverture du fichier impossible ");
    }
}




// Recherche d'un admin par login et password et retourne son identifiant s'il existe

unsigned int verifieAdmin(char* login, char* password)
{
    FILE* file = fopen("ADMINISTRATEURS.txt", "r");
    if (file != NULL)
    {
        ADMIN admin;
        admin.Login = malloc(sizeof(admin.Login));
        admin.NomAdmin = malloc(sizeof(admin.NomAdmin));
        admin.PrenomAdmin = malloc(sizeof(admin.PrenomAdmin));
        admin.Password = malloc(sizeof(admin.Password));
        while (fscanf(file, "%u %s %s %s %s\n", &admin.IdAdmin, admin.NomAdmin, admin.PrenomAdmin, admin.Login, admin.Password) != EOF)
        {
            if (strcmp(admin.Login, login) == 0)
            {
                if (strcmp(admin.Password, password) == 0)
                {
                    fclose(file);
                    return admin.IdAdmin;
                }
                else
                {
                    printf("Erreur : Le mot de passe ne correspond pas au login fourni.\n");
                    fclose(file);
                    return 0;
                }
            }
        }
        printf("Erreur : Aucun ADMIN avec le login fourni n'a été trouvé.\n");
        fclose(file);
    }
    return 0;
}

// Menu des actions possibles pour un administrateur certaines fonctionalites
//sont definis dans les autres fichier

void menu_admin()

{
    unsigned int ida ;
    char * login, *password ;
    getchar();
    printf("\n Veuillez entrer votre Login :");
    login = saisir_chaine();
    printf(" \n Veuillez entrer votre mot de passe :");
    password = saisir_chaine();
    ida = verifieAdmin(login,password);
    if(ida)
    {
        unsigned int choix, idc ;
        unsigned int idcr = 0, ids = 0,idm = 0;
        printf(" \n\n\t\t\t ********* BIENVENU DANS LE MENU ADMINISTRATEURS **********");

        do
        {
            printf(" \n\t\t\t ---------- VEUILLEZ FAIRE UN CHOIX ----------");
            printf(" \n 1.Ajouter un admin ");
            printf(" \n 2.Ajouter un enseignant ");
            printf(" \n 3.Programmer un Cour ");
            printf(" \n 4.Ajouter une Horaire ");
            printf(" \n 5.Afficher les cours");
            printf(" \n 6.Annuler un cours ");
            printf(" \n 7. Quitter");
            printf(" \n \t\t\t-------------------------------------");
            printf(" \n\t\t choix =======> ");
            scanf("%u",&choix);

            switch(choix)
            {
            case 1 :
                ajouterAdmin();
                break;
            case 2 :
                ajouterEnseignant();
                break;
            case 3 :
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
                break;
            case 4 :
                ajouterHoraire();
                break;
            case 5 :
                afficherTousCours();
                break ;
            case 6 :
                printf(" \n Entrer le numero de cours a annuler :");
                scanf("%u",&idc);
                getchar();
                annulerCour(&idc);
            case 7 :
                printf(" \n Fermeture du menu ");
                break;

            }
        }
        while( choix != 7);
    }


}


