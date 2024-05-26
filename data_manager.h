#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "athlete.h"

void create_data_directory(); // Déclaration de la fonction create_data_directory

AthleteList* load_athletes(const char* filename);
void save_athletes(AthleteList* list, const char* filename);
void view_performances(AthleteList* list);

#endif
