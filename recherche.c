#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Code principale de l'application, elle doit être capable de:
Lire le fichier csv et afficher l'ensembe de ses données de manière visible
Charger les données du fichier csv dans une structure adaptée
Rechercher les arbres d'une même espèce et afficher les données correspondantes
Trier les données selon deux critères différents: par age et par note de santé via deux méthodes de tri différentes

Soit CINQ/SIX fonctions minimum

*/

#define TAILLE_MAX 100
/*Déclaration du type de données utilisé pour l'enregistrment des arbes : structure d'enregistrement*/
typedef struct{
    char identifiant[6], espece[20];
    int age, sante;
    float hauteur, diametre, volume;
}ARBRE;

/*Prototype de la fonction de lecture, ses paramètres sont le nom du fichier et le nombre d'arbres, 
passés par pointeur 
*/
void lirecharger_fichier(const char *nom_fichier, int *nb_arbres, ARBRE **tab_arbres){
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX];
    int i = 0;

    fichier = fopen(nom_fichier, "r");

    if (fichier != NULL){

        // Lire et ignorer l'en-tête
        fgets(chaine, sizeof(chaine), fichier);

        // Compter le nombre d'arbres
        while (fgets(chaine, sizeof(chaine), fichier) != NULL){
            (*nb_arbres)++;
        }

        // Réallouer l'espace mémoire pour la bonne taille
        *tab_arbres = realloc(*tab_arbres, (*nb_arbres) * sizeof(ARBRE));

        // Revenir au début du fichier
        rewind(fichier);

        // Ignorer à nouveau l'en-tête
        fgets(chaine, sizeof(chaine), fichier);

        // Chargement réel des données
        while (fgets(chaine, sizeof(chaine), fichier) != NULL){

            ARBRE* p = &((*tab_arbres)[i]);
            char *champ = strtok(chaine, ",");

            // ID
            strcpy(p->identifiant, champ);

            // Espece
            champ = strtok(NULL, ",");
            strcpy(p->espece, champ);

            // Age
            champ = strtok(NULL, ",");
            p->age = atoi(champ);

            // Santé
            champ = strtok(NULL, ",");
            p->sante = atoi(champ);

            // Hauteur
            champ = strtok(NULL, ",");
            p->hauteur = atof(champ);

            // Diamètre
            champ = strtok(NULL, ",");
            p->diametre = atof(champ);

            // Volume
            champ = strtok(NULL, ",");
            p->volume = atof(champ);

            i++;
        }

        fclose(fichier);

    } else {
        printf("Erreur d'ouverture du fichier %s\n", nom_fichier);
    }
}



void afficher_tableau(ARBRE *tab, int nb) {
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
    printf("| ID     | Espece               | Age | Sante  | Hauteur | Diametre | Volume  |\n");
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");

    for(int i = 0; i < nb; i++) {
        printf("| %-6s | %-20s | %3d | %6d | %7.2f | %8.2f | %7.2f |\n",
            tab[i].identifiant,
            tab[i].espece,
            tab[i].age,
            tab[i].sante,
            tab[i].hauteur,
            tab[i].diametre,
            tab[i].volume
        );
    }

    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
}

void recherche(ARBRE *tab, int nbr, const char *espece){
    int count = 0;
    printf("\n------Recherche %s ------\n",espece);
    for (int i = 0 ; i < nbr;i++){
        if (strcmp(tab[i].espece, espece) == 0){
            printf("%s:%d ans, %.1fm, sante %d\n", tab[i].identifiant,tab[i].age,tab[i].hauteur,tab[i].sante);
            count++;
        }

    }
    printf("Arbres %s trouve : %d",espece,count);
}   


int main(){

    const char *nom_fichier = "foret_arbres_50_V2.csv";
    int nb_arbres = 0;
    ARBRE *tab_arbres = NULL;
    tab_arbres = malloc(TAILLE_MAX * sizeof (ARBRE)); // allocation initiale de mémoire pour le tableau des arbres
    lirecharger_fichier(nom_fichier, &nb_arbres, &tab_arbres);
    afficher_tableau(tab_arbres, nb_arbres);
    printf("\n Nombre d'arbres lus: %d\n", nb_arbres);
    recherche(tab_arbres,nb_arbres,"Chene");
    free(tab_arbres); // libération de la mémoire allouée pour les arbres
    return 0;
    
}
