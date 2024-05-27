#include <stdio.h> // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h> // Inclusion de la bibliothèque standard de fonctions utilitaires
#include "athlete.h" // Inclusion du fichier d'en-tête pour les structures et fonctions liées aux athlètes
#include "performance.h" // Inclusion du fichier d'en-tête pour les structures et fonctions liées aux performances
#include "data_manager.h" // Inclusion du fichier d'en-tête pour les fonctions de gestion des données
#include "statistics.h" // Inclusion du fichier d'en-tête pour les fonctions de statistiques


void menu() {
    printf("\nMenu :\n"); // Affiche le titre du menu
    printf("1. Ajouter une performance\n");// Option pour ajouter une performance
    printf("2. Consulter l'historique des performances\n"); // Option pour consulter l'historique des performances
    printf("3. Consulter les statistiques des athlètes\n"); // Option pour consulter les statistiques des athlètes
    printf("4. Quitter\n"); // Option pour quitter le programme
    printf("Entrez votre choix : "); // Invite l'utilisateur à entrer son choix
}

int main() {
    create_data_directory(); // Assurer la création du répertoire de données
    AthleteList* athletes = load_athletes("data.txt"); // Charger la liste des athlètes depuis un fichier 
    
    int choice; // Déclaration de la variable pour stocker le choix de l'utilisateur
    do {
        menu();  // Afficher le menu
        scanf("%d", &choice); // Lire le choix de l'utilisateur
        getchar(); // Consommer le '\n' laissé par scanf

        switch (choice) { // Commencer une structure de contrôle de choix
            case 1:
                add_performance(athletes);  // Ajouter une performance à la liste des athlètes
                break;
            case 2:
                view_performances(athletes); // Consulter l'historique des performances
                break;
            case 3:
                view_statistics(athletes); // Consulter les statistiques des athlètes
                break;
            case 4:
                save_athletes(athletes, "data.txt"); // Sauvegarder les athlètes dans le fichier
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n"); // Message pour choix invalide
        }
    } while (choice != 4); // Continuer le menu tant que le choix n'est pas 4 (Quitter)
    
    free_athletes(athletes); // Libérer la mémoire allouée pour la liste des athlètes
    return 0; // Retourner 0 pour indiquer que le programme s'est terminé avec succès

}
