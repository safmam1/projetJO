#ifndef PERFORMANCE_H 
#define PERFORMANCE_H 


#include "athlete.h" // Inclusion du fichier d'en-tête pour les structures et fonctions liées aux athlètes


Performance* create_performance(const char* date, const char* event, float time, int position); // Déclaration de la fonction pour créer une performance
void add_performance(AthleteList* list); // Déclaration de la fonction pour ajouter une performance à la liste des athlètes
int check_relay_date(AthleteList* list, const char* date); // Déclaration de la fonction pour ajouter une performance à la liste des athlètes

#endif // Fin de la conditionnelle de préprocesseur pour PERFORMANCE_H
