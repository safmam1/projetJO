#ifndef ATHLETE_H
#define ATHLETE_H

#define MAX_NAME_LEN 100

typedef struct Performance {
    char date[11];
    char event[50];
    float time;
    int position; // -1 for non-relay events, 1-4 for relay positions
    struct Performance* next;
} Performance;

typedef struct Athlete {
    char name[MAX_NAME_LEN];
    Performance* performances;
    struct Athlete* next;
} Athlete;

typedef struct {
    Athlete* head;
} AthleteList;

AthleteList* create_athlete_list();
Athlete* find_athlete(AthleteList* list, const char* name);
Athlete* add_athlete(AthleteList* list, const char* name);
void free_athletes(AthleteList* list);

#endif
