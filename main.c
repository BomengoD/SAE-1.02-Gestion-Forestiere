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
    FILE* fichier = NULL;// pointeur de fichier
    ARBRE* p = NULL; // pointeur vers une structure ARBRE
    char chaine[TAILLE_MAX];//tableau de caractères pour stocker chaque ligne lue
    int i = 0;
    fichier = fopen(nom_fichier, "r");

    if(fichier != NULL){

        fgets(chaine, sizeof(chaine), fichier); // lire la première ligne (en-tête) et l'ignorer !

        /*On compte le nombre d'arbres grâce à fgets, fgets parcours chaque ligne une par une donc chaque itération est une ligne*/
        while (fgets(chaine, sizeof(chaine), fichier) != NULL){
            (*nb_arbres)++; // incrémenter le compteur d'arbres pour chaque ligne lue
        }

        *tab_arbres = realloc(*tab_arbres, (*nb_arbres) * sizeof(ARBRE));// réallocation de mémoire pour le tableau des arbres
        rewind(fichier); // revenir au début du fichier pour relire les données

        fgets(chaine, sizeof(chaine), fichier); // lire et ignorer à nouveau la première ligne (en-tête)

        while (fgets(chaine, sizeof(chaine), fichier) != NULL){
            ARBRE* p = &((*tab_arbres)[i]); // pointeur vers l'arbre courant dans le tableau
            char *champ = strtok(chaine, ";"); // découpage de la ligne en champs par le séparateur ";"
            int champ_num = 0; // compteur de champs
            printf("Arbre %d - ", i + 1); // affichage du numéro de l'arbre
            while (champ && champ_num < 7){// boucle pour afficher chaque champ(progression sur la ligne) tant qu'il y a des champs et que le nombre de champs est inférieur à 7(qui est le nombre d'attributs d'un arbre donc le nombre de colonnnes dans le fichier csv)
                printf("Champ %d:%s|", champ_num + 1, champ); // affichage du numéro du champ et son contenu
                champ = strtok(NULL, ";");// obtenir le champ suivant, NULL indique de continuer à partir de la position actuelle
                champ_num++;// incrémenter le compteur de champs   
            
            }

            printf("\n");// nouvelle ligne après avoir affiché tous les champs de l'arbre
            i++; // incrémenter l'index du tableau des arbres
        }

        fclose(fichier); // fermer le fichier après la lecture

    }else{
        printf("Erreur d'ouverture du fichier %s\n", nom_fichier);
    }
}

int main(){

    const char *nom_fichier = "foret_arbres_50_V1.csv";
    int nb_arbres = 0;
    ARBRE *tab_arbres = NULL;
    tab_arbres = malloc(TAILLE_MAX * sizeof (ARBRE)); // allocation initiale de mémoire pour le tableau des arbres
    lirecharger_fichier(nom_fichier, &nb_arbres, &tab_arbres);
    printf("\n Nombre d'arbres lus: %d\n", nb_arbres);
    free(tab_arbres); // libération de la mémoire allouée pour les arbres
    return 0;
    
}