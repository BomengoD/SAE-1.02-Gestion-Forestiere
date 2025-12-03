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

/*Déclaration du type de données utilisé pour l'enregistrement de la table des arbres : structure d'enregistrement*/
typedef struct{
    ARBRE *arbres;
}TABLE;

/*Prototype de la fonction de lecture, ses paramètres sont le nom du fichier et le nombre d'arbres, 
passés par pointeur 
*/
void lirecharger_fichier(const char *nom_fichier, int *nb_arbres, TABLE tab_arbres){
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX];

    fichier = fopen(nom_fichier, "r");
    if(fichier != NULL){
        /*On compte le nombre d'arbres gràace à fgets*/
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL){
            printf("%s", chaine);
            (*nb_arbres)++;
        }
        tab_arbres.arbres = (ARBRE*) malloc (*nb_arbres * sizeof(ARBRE));// allocation d'un espace mémoire pour le tableau dynamique d'arbres
        rewind(fichier); // repositionner le curseur au début du fichier
        int i = 0;
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL){
            sscanf(chaine, "%s;%s;%d;%d;%f;%f;%f", &tab_arbres.arbres[i].identifiant,
            &tab_arbres.arbres[i].espece, &tab_arbres.arbres[i].age, &tab_arbres.arbres[i].sante,
            &tab_arbres.arbres[i].hauteur, &tab_arbres.arbres[i].diametre, &tab_arbres.arbres[i].volume);
            i++;
            
        }
        fclose(fichier);
    }else{
        printf("Erreur d'ouverture du fichier %s\n", nom_fichier);
    }
  
}

int main(){

    const char *nom_fichier = "foret_arbres_50_V1.csv";
    int nb_arbres = 0;
    TABLE tab_arbres;
    lirecharger_fichier(nom_fichier, &nb_arbres, tab_arbres);
    printf("\n Nombre d'arbres lus: %d\n", nb_arbres);
    for (int i = 0; i < nb_arbres; i++){
        printf(" %s; %s; %d ; %d; %.2f; %.2f; %.2f\n", tab_arbres.arbres[i].identifiant, tab_arbres.arbres[i].espece,
        tab_arbres.arbres[i].age, tab_arbres.arbres[i].sante, tab_arbres.arbres[i].hauteur,
        tab_arbres.arbres[i].diametre, tab_arbres.arbres[i].volume);
    }
    free(tab_arbres.arbres);
    return 0;
    
}