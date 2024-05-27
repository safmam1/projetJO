#ifndef DATA_MANAGER_H // Directive de préprocesseur pour éviter les inclusions multiples du fichier d'en-tête
#define DATA_MANAGER_H // Définit la macro DATA_MANAGER_H


#include "athlete.h"  // Inclusion du fichier d'en-tête "athlete.h" qui contient les définitions des structures et fonctions relatives aux athlètes

void create_data_directory(); // Déclaration de la fonction create_data_directory

AthleteList* load_athletes(const char* filename); // Déclaration de la fonction load_athletes qui charge la liste des athlètes à partir d'un fichier
void save_athletes(AthleteList* list, const char* filename); // Déclaration de la fonction save_athletes qui sauvegarde la liste des athlètes dans un fichier
void view_performances(AthleteList* list); // Déclaration de la fonction view_performances qui affiche les performances des athlètes

#endif // Fin de la directive de préprocesseur pour les inclusions multiples
