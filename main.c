#include <stdio.h>
#include "ENSEIGNANTS.h"
#include "CLASSES.h"
#include "MATIERES.h"
#include "HORAIRE.h"
#include "SALLES.h"
#include "COUR.h"
#include "RESERVATIONS.h"
#include"ADMINISTRATEURS.h"



/* Voici quelque informations sur la structuration du programme
 -On suppose que le fichier COURS.txt contient tous les cours de l'annee en cours et chaque cour a un identifiant unique
 - un cours est ici une subdivision journaliere en fonction des Horaires ( on a definit 4 horaires dans le programme) on a
  donc 4 cours dans la journee et chaque cours a un identifiant unique et cela est ainsi chaque jour pour tous les jours de l'annee
 meme les horaires n'etant associe a aucune matiere ni aucune salle sont considere comme un cour et ont un identifiant cela facilite ainsi
 la reservation d'un cours il suffit de selectionne l'Identifiant d'un cour pour lequel Idsalle = ou IdMatiere = 0 ( c'est ainsi qu'on reconnait
 un cour libre )
  ainsi si on suppose qu'on une classe , et qu'il y'a 100 jours de cours en tout on aura 100 jours *4 Idhoraire = 400 Id de cous
  de cour pour chaque classe
  si on a 2 classes on aura 800 id de cours alors dans la table des COURS ( fichier COURS).

  c'est sur ce principe que le programme a ete developpe .
*/


void menu_principal()
{
    unsigned int choix ;
    printf("\n\n\t******BIENVENU DANS LA GESTION DES RESERVATIONS DE SALLES DE COURS *****\n\n");

    do
    {
        printf("\n\t\t -----VEUILLEZ FAIRE VOTRE CHOIX -------- \n");
        printf( " \n\t 1. Afficher un emploi du temp ");
        printf( " \n\t 2. Se connecter en tant que qu 'enseignant ");
        printf( " \n\t 3. Se conecter en tant qu' administrateur ");
        printf( " \n\t 4. Quitter ");
        printf("\n\t --------------------------- \n");
        printf("\n\t choix =======>");
        scanf("%u",&choix );

        switch( choix )
        {
        case 1 :
            afficherCoursClasse();
            break;
        case 2 :
            menu_enseignant();
            break ;
        case 3:
            menu_admin();
            break;
        case 4 :
            printf(" \n Fin du programme ");
            break ;
        default :
            printf(" \n Choix inexistant ");
            break ;

        }
    }
    while( choix != 4);

}



int main()

{

    menu_principal();


}
