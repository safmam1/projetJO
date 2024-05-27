#include <stdio.h>
#include <string.h>
#include "statistics.h"

void best_worst_avg_time(Athlete* athlete, const char* event, float* best, float* worst, float* avg) {
    Performance* current = athlete->performances;
    int count = 0;
    float sum = 0;
    
    *best = *worst = -1;
    
    while (current != NULL) {
        if (strcmp(current->event, event) == 0) {
            if (*best == -1 || current->time < *best) {
                *best = current->time;
            }
            if (*worst == -1 || current->time > *worst) {
                *worst = current->time;
            }
            sum += current->time;
            count++;
        }
        current = current->next;
    }
    
    if (count > 0) {
        *avg = sum / count;
    } else {
        *avg = -1;
    }
}

void top_athletes(AthleteList* list, const char* event) {
    Athlete* current = list->head;
    Athlete* top3[3] = {NULL, NULL, NULL};
    float top3_avg[3] = {1e6, 1e6, 1e6}; // Initializing with a large number

    while (current != NULL) {
        float avg = 0;
        int count = 0;
        Performance* performance = current->performances;
        
        while (performance != NULL) {
            if (strcmp(performance->event, event) == 0) {
                avg += performance->time;
                count++;
            }
            performance = performance->next;
        }
        
        if (count > 0) {
            avg /= count;
            if (avg < top3_avg[2]) {
                if (avg < top3_avg[1]) {
                    if (avg < top3_avg[0]) {
                        top3_avg[2] = top3_avg[1];
                        top3_avg[1] = top3_avg[0];
                        top3_avg[0] = avg;
                        top3[2] = top3[1];
                        top3[1] = top3[0];
                        top3[0] = current;
                    } else {
                        top3_avg[2] = top3_avg[1];
                        top3_avg[1] = avg;
                        top3[2] = top3[1];
                        top3[1] = current;
                    }
                } else {
                    top3_avg[2] = avg;
                    top3[2] = current;
                }
            }
        }
        
        current = current->next;
    }

    printf("\nTop 3 athlètes pour l'épreuve %s :\n", event);
    for (int i = 0; i < 3; i++) {
        if (top3[i]) {
            printf("%s - Temps moyen : %.2f\n", top3[i]->name, top3_avg[i]);
        }
    }
}

void view_statistics(AthleteList* list) {
    char name[MAX_NAME_LEN];
    char event[50];
    
    printf("Nom de l'athlète : ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("Épreuve : ");
    fgets(event, 50, stdin);
    event[strcspn(event, "\n")] = '\0';
    
    Athlete* athlete = find_athlete(list, name);
    if (athlete) {
        float best, worst, avg;
        best_worst_avg_time(athlete, event, &best, &worst, &avg);
        
        printf("Meilleur temps pour %s : %.2f\n", event, best);
        printf("Pire temps pour %s : %.2f\n", event, worst);
        printf("Temps moyen pour %s : %.2f\n", event, avg);
    } else {
        printf("Athlète non trouvé.\n");
    }

    top_athletes(list, event);
}
