#include <stdio.h> // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h> // Inclusion de la bibliothèque standard de fonctions utilitaires
#include <string.h> // Inclusion de la bibliothèque pour les manipulations de chaînes de caractères
#include <sys/stat.h>// Inclusion de la bibliothèque pour les informations de fichier et de répertoire
#include <sys/types.h> // Inclusion de la bibliothèque pour les types de données utilisés dans les opérations de fichier
#include "data_manager.h" // Inclusion du fichier d'en-tête pour la gestion des données des athlètes
#include "performance.h" // Inclusion du fichier d'en-tête pour la gestion des performances des athlètes

// Fonction pour créer un répertoire de données si celui-ci n'existe pas
void create_data_directory() {
    struct stat st = {0}; // Déclaration d'une structure stat pour stocker les informations sur le répertoire

// Vérifie si le répertoire "data" existe
    if (stat("data", &st) == -1) {
        // Si le répertoire n'existe pas, le créer avec les permissions 0700 (lecture, écriture, exécution pour le propriétaire)
        mkdir("data", 0700);
    }
}

// Fonction pour charger la liste des athlètes depuis un fichier
AthleteList* load_athletes(const char* filename) {
    AthleteList* list = create_athlete_list(); // Crée une nouvelle liste d'athlètes
    char filepath[256]; // Déclare un tableau de caractères pour stocker le chemin du fichier
    snprintf(filepath, sizeof(filepath), "data/%s", filename); // Construit le chemin complet du fichier
    FILE* file = fopen(filepath, "r"); // Ouvre le fichier en mode lecture
    if (!file) { // Vérifie si l'ouverture du fichier a échoué
        perror("fopen"); // Affiche un message d'erreur
        return list; // Retourne la liste (qui est vide à ce stade)
    }

    char line[256]; // Déclare un tableau de caractères pour lire les lignes du fichier
    // Lit chaque ligne du fichier jusqu'à la fin
    while (fgets(line, sizeof(line), file)) {
        char name[MAX_NAME_LEN], date[11], event[50]; // Déclare des variables pour stocker les données de la ligne
        float time; // Variable pour stocker le temps de performance
        int position = -1; // Variable pour stocker la position (initialisée à -1)
	// Analyse la ligne lue pour extraire les données formatées
        sscanf(line, "%99[^,],%10[^,],%49[^,],%f,%d", name, date, event, &time, &position);
        
	// Trouve l'athlète dans la liste par son nom
        Athlete* athlete = find_athlete(list, name);
	// Si l'athlète n'existe pas, l'ajoute à la liste
        if (!athlete) {
            athlete = add_athlete(list, name);
        }

	// Crée une nouvelle performance avec les données extraites        
        Performance* performance = create_performance(date, event, time, position);
	// Ajoute la performance à la liste des performances de l'athlète
        performance->next = athlete->performances;
        athlete->performances = performance;
    }

    fclose(file); // Ferme le fichier
    return list; // Retourne la liste d'athlètes remplie
}

// Fonction pour sauvegarder la liste des athlètes dans un fichier
void save_athletes(AthleteList* list, const char* filename) {
    create_data_directory(); // S'assurer que le dossier data existe
    char filepath[256]; // Déclare un tableau de caractères pour stocker le chemin du fichier
    snprintf(filepath, sizeof(filepath), "data/%s", filename); // Construit le chemin complet du fichier
    FILE* file = fopen(filepath, "w"); // Ouvre le fichier en mode écriture
    if (!file) { // Vérifie si l'ouverture du fichier a échoué
        perror("fopen"); // Affiche un message d'erreur
        return; // Retourne sans rien faire
    }

    Athlete* current = list->head; // Pointe vers le premier athlète de la liste
    // Parcourt tous les athlètes de la liste
    while (current) {
        Performance* perf = current->performances; // Pointe vers la première performance de l'athlète
	// Parcourt toutes les performances de l'athlète
        while (perf) {
	    // Écrit les données de la performance dans le fichier
            fprintf(file, "%s,%s,%s,%.2f,%d\n", current->name, perf->date, perf->event, perf->time, perf->position);
            perf = perf->next; // Passe à la performance suivante
        }
        current = current->next; // Passe à l'athlète suivant
    }

    fclose(file); // Ferme le fichier
}

// Fonction pour afficher les performances des athlètes
void view_performances(AthleteList* list) {
    char name[MAX_NAME_LEN]; // Déclare un tableau de caractères pour stocker le nom de l'athlète

    // Demande à l'utilisateur de saisir le nom de l'athlète
    printf("Nom de l'athlète (laisser vide pour tous) : ");
    fgets(name, MAX_NAME_LEN, stdin); // Lit la saisie de l'utilisateur
    name[strcspn(name, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne de la saisie

    // Si un nom est saisi, affiche les performances de l'athlète spécifié
    if (strlen(name) > 0) {
        Athlete* athlete = find_athlete(list, name); // Trouve l'athlète par son nom
	// Si l'athlète est trouvé
        if (athlete) {
            Performance* current = athlete->performances; // Pointe vers la première performance de l'athlète
	    // Parcourt toutes les performances de l'athlète
            while (current) {
		// Affiche les détails de la performance
                printf("%s - %s - %.2fs - Position: %d\n", current->date, current->event, current->time, current->position);
                current = current->next; // Passe à la performance suivante
            }
        } else {
	    // Si l'athlète n'est pas trouvé, affiche un message
            printf("Athlète non trouvé.\n");
        }
    } else {
	// Si aucun nom n'est saisi, affiche les performances de tous les athlètes
        Athlete* current = list->head; // Pointe vers le premier athlète de la liste
	// Parcourt tous les athlètes de la liste
        while (current) {
            printf("\nAthlète : %s\n", current->name); // Affiche le nom de l'athlète
            Performance* perf = current->performances; // Pointe vers la première performance de l'athlète
	    // Parcourt toutes les performances de l'athlète
            while (perf) {
		// Affiche les détails de la performance
                printf("%s - %s - %.2fs - Position: %d\n", perf->date, perf->event, perf->time, perf->position);
                perf = perf->next; // Passe à la performance suivante
            }
            current = current->next; // Passe à l'athlète suivant
        }
    }
}
