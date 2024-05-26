#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "athlete.h"

Performance* create_performance(const char* date, const char* event, float time, int position);
void add_performance(AthleteList* list);
int check_relay_date(AthleteList* list, const char* date);

#endif
