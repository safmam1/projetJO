#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "athlete.h"

AthleteList* create_athlete_list() {
    AthleteList* list = (AthleteList*)malloc(sizeof(AthleteList));
    list->head = NULL;
    return list;
}

Athlete* find_athlete(AthleteList* list, const char* name) {
    Athlete* current = list->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Athlete* add_athlete(AthleteList* list, const char* name) {
    Athlete* new_athlete = (Athlete*)malloc(sizeof(Athlete));
    strncpy(new_athlete->name, name, MAX_NAME_LEN);
    new_athlete->performances = NULL;
    new_athlete->next = list->head;
    list->head = new_athlete;
    return new_athlete;
}

void free_performances(Performance* performance) {
    while (performance != NULL) {
        Performance* next = performance->next;
        free(performance);
        performance = next;
    }
}

void free_athletes(AthleteList* list) {
    Athlete* current = list->head;
    while (current != NULL) {
        Athlete* next = current->next;
        free_performances(current->performances);
        free(current);
        current = next;
    }
    free(list);
}
