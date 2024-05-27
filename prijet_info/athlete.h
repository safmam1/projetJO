#ifndef ATHLETE_H // Vérifie si ATHLETE_H n'est pas défini pour éviter les inclusions multiples
#define ATHLETE_H // Définit ATHLETE_H pour signaler que ce fichier a été inclus

#define MAX_NAME_LEN 100 // Définit une constante pour la longueur maximale des noms

typedef struct Performance { // Définit une structure pour représenter une performance
    char date[11]; // Chaîne de caractères pour la date (format: YYYY-MM-DD)
    char event[50]; // Chaîne de caractères pour le nom de l'événement
    float time; // Temps réalisé lors de la performance
    int position; // -1 for non-relay events, 1-4 for relay positions
    struct Performance* next; // Pointeur vers la prochaine performance dans la liste chaînée
} Performance;

typedef struct Athlete { // Définit une structure pour représenter un athlète
    char name[MAX_NAME_LEN]; // Nom de l'athlète
    Performance* performances; // Pointeur vers la liste chaînée des performances de l'athlète
    struct Athlete* next; // Pointeur vers le prochain athlète dans la liste chaînée
} Athlete;

typedef struct { // Définit une structure pour représenter une liste d'athlètes
    Athlete* head; // Pointeur vers le premier athlète de la liste
} AthleteList;

AthleteList* create_athlete_list(); // Déclare une fonction pour créer une nouvelle liste d'athlètes
Athlete* find_athlete(AthleteList* list, const char* name); // Déclare une fonction pour trouver un athlète dans la liste par son nom
Athlete* add_athlete(AthleteList* list, const char* name); // Déclare une fonction pour ajouter un nouvel athlète à la liste
void free_athletes(AthleteList* list); // Déclare une fonction pour libérer la mémoire allouée pour les athlètes

#endif // Termine la condition de préprocesseur pour les inclusions multiples
