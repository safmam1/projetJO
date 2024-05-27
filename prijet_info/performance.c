#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "performance.h"

Performance* create_performance(const char* date, const char* event, float time, int position) {
    Performance* new_performance = (Performance*)malloc(sizeof(Performance));
    strncpy(new_performance->date, date, 11);
    strncpy(new_performance->event, event, 50);
    new_performance->time = time;
    new_performance->position = position;
    new_performance->next = NULL;
    return new_performance;
}

int check_relay_date(AthleteList* list, const char* date) {
    Athlete* current = list->head;
    while (current != NULL) {
        Performance* perf = current->performances;
        while (perf != NULL) {
            if (strcmp(perf->date, date) == 0 && strcmp(perf->event, "Relais 4x400m") == 0) {
                return 1; // Relay already exists on this date
            }
            perf = perf->next;
        }
        current = current->next;
    }
    return 0;
}

void save_performance_to_file(const char* filename, const char* name, const char* date, const char* event, float time, int position) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    FILE* file = fopen(filepath, "a");
    if (!file) {
        perror("fopen");
        return;
    }

    fprintf(file, "%s,%s,%s,%.2f,%d\n", name, date, event, time, position);
    fclose(file);
}

void add_performance(AthleteList* list) {
    char name[MAX_NAME_LEN];
    char date[11];
    char event[50];
    float time;
    int position = -1;

    printf("Nom de l'athlète : ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Date de l'entraînement (YYYY-MM-DD) : ");
    fgets(date, 11, stdin);
    date[strcspn(date, "\n")] = '\0';
    getchar(); // Consommer le '\n' laissé par fgets

    printf("Choisissez une épreuve :\n");
    printf("1. 100m\n");
    printf("2. 400m\n");
    printf("3. 5000m\n");
    printf("4. Marathon\n");
    printf("5. Relais 4x400m\n");
    printf("Entrez votre choix : ");
    int choix;
    scanf("%d", &choix);
    getchar(); // Consommer le '\n' laissé par scanf

    switch (choix) {
        case 1:
            strcpy(event, "100m");
            break;
        case 2:
            strcpy(event, "400m");
            break;
        case 3:
            strcpy(event, "5000m");
            break;
        case 4:
            strcpy(event, "Marathon");
            break;
        case 5:
            strcpy(event, "Relais 4x400m");
            if (check_relay_date(list, date)) {
                printf("Un relais est déjà enregistré pour cette date.\n");
                return;
            }
            break;
        default:
            printf("Choix invalide.\n");
            return;
    }

    if (choix == 5) { // Relais
        for (int i = 1; i <= 4; i++) {
            char relay_name[MAX_NAME_LEN];
            printf("Nom de l'athlète %d : ", i);
            fgets(relay_name, MAX_NAME_LEN, stdin);
            relay_name[strcspn(relay_name, "\n")] = '\0';

            printf("Position dans le relais (1-4) : ");
            scanf("%d", &position);
            getchar(); // Consommer le '\n' laissé par scanf

            printf("Temps (en secondes) : ");
            scanf("%f", &time);
            getchar(); // Consommer le '\n' laissé par scanf

            Athlete* athlete = find_athlete(list, relay_name);
            if (!athlete) {
                athlete = add_athlete(list, relay_name);
            }

            Performance* new_performance = create_performance(date, event, time, position);
            new_performance->next = athlete->performances;
            athlete->performances = new_performance;

            // Sauvegarde immédiate dans le fichier
            save_performance_to_file("data.txt", relay_name, date, event, time, position);
        }
    } else { // Autres épreuves
        printf("Temps (en secondes) : ");
        scanf("%f", &time);
        getchar(); // Consommer le '\n' laissé par scanf

        Athlete* athlete = find_athlete(list, name);
        if (!athlete) {
            athlete = add_athlete(list, name);
        }

        Performance* new_performance = create_performance(date, event, time, position);
        new_performance->next = athlete->performances;
        athlete->performances = new_performance;

        // Sauvegarde immédiate dans le fichier
        save_performance_to_file("data.txt", name, date, event, time, position);

        // Calculer et afficher la différence de temps pour une même épreuve entre deux dates
        Performance* perf1 = NULL;
        Performance* perf2 = new_performance;
        Performance* current = athlete->performances;
        while (current != NULL) {
            if (strcmp(current->event, event) == 0 && strcmp(current->date, date) != 0) {
                if (perf1 == NULL || strcmp(current->date, perf1->date) > 0) {
                    perf1 = current;
                }
            }
            current = current->next;
        }

        if (perf1) {
            float diff = perf2->time - perf1->time;
            printf("Différence de temps pour %s entre %s et %s : %.2f secondes\n", event, perf1->date, perf2->date, diff);
        } else {
            printf("Aucune performance précédente trouvée pour comparaison.\n");
        }
    }
}
