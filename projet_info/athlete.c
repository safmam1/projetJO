#include <stdio.h> // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h> // Inclusion de la bibliothèque standard pour la gestion de la mémoire dynamique et d'autres opérations utilitaires
#include <string.h>  // Inclusion de la bibliothèque standard pour les opérations sur les chaînes de caractères
#include "athlete.h" // Inclusion du fichier d'en-tête "athlete.h" qui contient les définitions des structures et fonctions relatives aux athlètes

// Fonction pour créer une liste d'athlètes
AthleteList* create_athlete_list() {
    AthleteList* list = (AthleteList*)malloc(sizeof(AthleteList)); // Allocation de mémoire pour une nouvelle liste d'athlètes
    list->head = NULL; // Initialisation de la tête de liste à NULL
    return list; // Retourne la liste d'athlètes créée
}

// Fonction pour trouver un athlète dans la liste par son nom
Athlete* find_athlete(AthleteList* list, const char* name) {
    Athlete* current = list->head; // Début de la recherche à la tête de la liste
    while (current != NULL) { // Parcourt la liste des athlètes
        if (strcmp(current->name, name) == 0) { // Compare le nom de l'athlète actuel avec le nom recherché
            return current; // Si les noms correspondent, retourne un pointeur vers l'athlète
        }
        current = current->next; // Passe à l'athlète suivant dans la liste
    }
    return NULL; // Si aucun athlète n'est trouvé, retourne NULL
}

// Fonction pour ajouter un nouvel athlète à la liste
Athlete* add_athlete(AthleteList* list, const char* name) {
    Athlete* new_athlete = (Athlete*)malloc(sizeof(Athlete)); // Allocation de mémoire pour un nouvel athlète
    strncpy(new_athlete->name, name, MAX_NAME_LEN); // Copie le nom fourni dans la structure de l'athlète
    new_athlete->performances = NULL; // Initialise la liste des performances de l'athlète à NULL
    new_athlete->next = list->head; // Insère le nouvel athlète au début de la liste

    list->head = new_athlete;  // Met à jour la tête de la liste pour pointer vers le nouvel athlète
    return new_athlete;  // Met à jour la tête de la liste pour pointer vers le nouvel athlète
}

// Fonction pour libérer la mémoire allouée pour les performances d'un athlète
void free_performances(Performance* performance) {
    while (performance != NULL) { // Parcourt la liste des performances
        Performance* next = performance->next; // Sauvegarde un pointeur vers la performance suivante

        free(performance); // Libère la mémoire de la performance actuelle
        performance = next; // Passe à la performance suivante

    }
}

// Fonction pour libérer la mémoire allouée pour la liste des athlètes et leurs performances
void free_athletes(AthleteList* list) {
    Athlete* current = list->head; // Commence à la tête de la liste des athlètes
    while (current != NULL) { // Parcourt la liste des athlètes
        Athlete* next = current->next; // Sauvegarde un pointeur vers l'athlète suivant
        free_performances(current->performances); // Libère la mémoire des performances de l'athlète actuel
        free(current); // Libère la mémoire de l'athlète actuel
        current = next; // Passe à l'athlète suivant
    }
    free(list); // Libère la mémoire de la structure de la liste des athlètes
}
