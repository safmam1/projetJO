#include <stdio.h>
#include <stdlib.h>
#include "athlete.h"
#include "performance.h"
#include "data_manager.h"
#include "statistics.h"

void menu() {
    printf("\nMenu :\n");
    printf("1. Ajouter une performance\n");
    printf("2. Consulter l'historique des performances\n");
    printf("3. Consulter les statistiques des athlètes\n");
    printf("4. Quitter\n");
    printf("Entrez votre choix : ");
}

int main() {
    create_data_directory(); // Assurer la création du répertoire de données
    AthleteList* athletes = load_athletes("data.txt");
    
    int choice;
    do {
        menu();
        scanf("%d", &choice);
        getchar(); // Consommer le '\n' laissé par scanf

        switch (choice) {
            case 1:
                add_performance(athletes);
                break;
            case 2:
                view_performances(athletes);
                break;
            case 3:
                view_statistics(athletes);
                break;
            case 4:
                save_athletes(athletes, "data.txt");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 4);
    
    free_athletes(athletes);
    return 0;
}
