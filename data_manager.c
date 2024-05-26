#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "data_manager.h"
#include "performance.h"

void create_data_directory() {
    struct stat st = {0};

    if (stat("data", &st) == -1) {
        mkdir("data", 0700);
    }
}

AthleteList* load_athletes(const char* filename) {
    AthleteList* list = create_athlete_list();
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    FILE* file = fopen(filepath, "r");
    if (!file) {
        perror("fopen");
        return list;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char name[MAX_NAME_LEN], date[11], event[50];
        float time;
        int position = -1;
        sscanf(line, "%99[^,],%10[^,],%49[^,],%f,%d", name, date, event, &time, &position);
        
        Athlete* athlete = find_athlete(list, name);
        if (!athlete) {
            athlete = add_athlete(list, name);
        }
        
        Performance* performance = create_performance(date, event, time, position);
        performance->next = athlete->performances;
        athlete->performances = performance;
    }

    fclose(file);
    return list;
}

void save_athletes(AthleteList* list, const char* filename) {
    create_data_directory(); // S'assurer que le dossier data existe
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    FILE* file = fopen(filepath, "w");
    if (!file) {
        perror("fopen");
        return;
    }

    Athlete* current = list->head;
    while (current) {
        Performance* perf = current->performances;
        while (perf) {
            fprintf(file, "%s,%s,%s,%.2f,%d\n", current->name, perf->date, perf->event, perf->time, perf->position);
            perf = perf->next;
        }
        current = current->next;
    }

    fclose(file);
}

void view_performances(AthleteList* list) {
    char name[MAX_NAME_LEN];

    printf("Nom de l'athlète (laisser vide pour tous) : ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) > 0) {
        Athlete* athlete = find_athlete(list, name);
        if (athlete) {
            Performance* current = athlete->performances;
            while (current) {
                printf("%s - %s - %.2fs - Position: %d\n", current->date, current->event, current->time, current->position);
                current = current->next;
            }
        } else {
            printf("Athlète non trouvé.\n");
        }
    } else {
        Athlete* current = list->head;
        while (current) {
            printf("\nAthlète : %s\n", current->name);
            Performance* perf = current->performances;
            while (perf) {
                printf("%s - %s - %.2fs - Position: %d\n", perf->date, perf->event, perf->time, perf->position);
                perf = perf->next;
            }
            current = current->next;
        }
    }
}
