#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Code principale de l'application, elle doit être capable de:
Lire le fichier csv
D'afficher l'ensembe de ses données de manière visible
Charger les données du fichier csv dans une structure adaptée
Rechercher les arbres d'une même espèce et afficher les données correspondantes
Trier les données selon deux critères différents: par age et par note de santé via deux méthodes de tri différentes

Soit CINQ/SIX fonctions minimum

*/

typedef struct{
    char identifiant[], espece[];
    int age, sante;
    float hauteur, diametre, volume;
}ARBRE;