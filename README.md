# Projet de Gestion des Performances des Athlètes aux J-O
## Description du projet 📜
Le but de ce projet est de développer une application permettant aux organisateurs de gérer les performances des athlètes durant les Jeux Olympiques. L'application permet de suivre les performances, calculer des statistiques et gérer les données des athlètes.

## Ce projet implique 💼
● Gestion des fichiers  

● Allocation dynamique  

● Conception d'interface  

● Informations générales
## Avantages du projet 🚀
● Gestion des données des athlètes.  

● Sauvegarde et chargement des états de performance.  

● Calcul des statistiques de performance.  

● Interface utilisateur pour la gestion et l'analyse des données.
● Modes d'utilisation
## Mode Manager 💫
● Création et configuration des profils des athlètes.  

● Enregistrement des performances des athlètes.  

● Définition et modification des données de performance.  

● Consultation des statistiques et des analyses des performances.
## Mode Spectateur 🍾
● Affichage des athlètes et de leurs performances.  

● Consultation des statistiques et des records.  

● Visualisation des meilleures performances et des comparaisons entre athlètes.  
_________________________________________________________________________________________________________________________________________________
## Compilation et Exécution
_Pour compiler le programme, utilisez la commande suivante dans votre terminal :_

gcc -o jo_performance main.c athlete.c performance.c statistics.c data_manager.c  

_Pour exécuter le programme :_

./jo_performance  
______________________________________________________________________________________________________________________________________________________________
## Modules Description  

#### main.c  

Ce fichier est le point d'entrée principal du programme. Il initialise les composants nécessaires, gère les entrées utilisateur et coordonne les différents modules pour effectuer les opérations requises.

#### athlete.h / athlete.c
Ces fichiers définissent la structure Athlete et fournissent des fonctions pour manipuler les données des athlètes.

#### Fonctions principales :

● create_athlete : Initialise un nouvel athlète.  

● update_athlete : Met à jour les informations existantes sur un athlète.  

● print_athlete : Affiche les données d'un athlète.
### performance.h / performance.c
Ces fichiers gèrent les données liées aux performances, fournissant des structures et des fonctions pour enregistrer et récupérer les métriques de performance.

#### Fonctions principales :

● record_performance : Enregistre une nouvelle entrée de performance pour un athlète.  

● get_performance : Récupère les données de performance pour analyse.
#### statistics.h / statistics.c
Ces fichiers fournissent des fonctions pour effectuer des analyses statistiques sur les données de performance des athlètes.

#### Fonctions principales :

● calculate_average : Calcule la moyenne des métriques de performance.  

● find_max_performance : Trouve la valeur de performance maximale.
#### data_manager.h / data_manager.c
Ces fichiers gèrent les opérations d'entrée et de sortie de données, permettant la lecture et l'écriture des données des athlètes dans des fichiers.

#### Fonctions principales :

● load_data : Charge les données des athlètes à partir d'un fichier.  

● save_data : Sauvegarde les données des athlètes dans un fichier.
### Utilisation
#### 1. Ajouter un Athlète :

● Utilisez la fonction create_athlete pour ajouter un nouvel athlète au système.
#### 2. Enregistrer une Performance :

● Utilisez la fonction record_performance pour enregistrer les données de performance des athlètes.
#### 3. Voir les Statistiques :

Utilisez les fonctions dans statistics.c pour analyser et visualiser les données statistiques sur les performances des athlètes.
#### 4.Sauvegarder/Charger les Données :

Utilisez save_data pour sauvegarder l'état actuel des données des athlètes dans un fichier.
Utilisez load_data pour charger les données des athlètes à partir d'un fichier.  
# Réalisation
_Ce projet a été réalisé par :_  
Safrioui Mamoun  
Nasri Assaad  
Saaid Myriam
