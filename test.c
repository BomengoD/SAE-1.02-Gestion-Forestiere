#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Permet d'utiliser les fonctions toupper et tolower*/
#include <ctype.h>
/*Permet d'utiliser l'encodage UTF-8 et donc d'afficher les caractères spéciaux*/
#include <Windows.h>

#define TAILLE_MAX 100
int nb_arbres = 0;
/*Déclaration du type de données utilisé pour l'enregistrment des arbes : structure, avec un tableau dynamique d'éléments ARBRE(déclaré dans la fonction principale)*/
typedef struct{
    char identifiant[6], espece[20];
    int age, sante;
    float hauteur, diametre, volume;
}ARBRE;


void ecrire_fichier(const char *nom_fichier, int nba, ARBRE *tab_arbres){
    FILE *fichier = NULL;
    ARBRE arbre;
    char chaine[TAILLE_MAX];//tableau de caractères pour stocker chaque ligne lue
    int i, k, compteur = nb_arbres + 1;
    fichier = fopen(nom_fichier, "a+");
    if (fichier != NULL){
        for (i = 0; i < nba; i++){
            /*auto_id(arbre, compteur);*/
            printf("\nRentrez son espèce :");
            if (fgets(arbre.espece, sizeof(arbre.espece),stdin) == NULL){
                printf("Erreur de lecture");
            }
             if (sscanf(chaine, "%s", &arbre.espece) != 1){
                printf("L'entrée n'est pas valide, veuillez entrez une chaîne de caractères.\n");
             }
            printf("\nRentrez son Âge :");
            if (fgets(chaine, sizeof(arbre.age), stdin) == NULL){
                printf("Erreur de lecture");
            }
            if (sscanf(chaine, "%3d",&arbre.age) != 1){
                printf("L'entrée n'est pas valide, veuillez entrez un entier correct.");
            }
            /*
            while (!verif_age(arbre.age)){
                printf("\nL'arbre doit au moins avoir 1 ans.\n");
                printf("Retapez son âge :");
                scanf("%3d", &arbre.age);
            }
            printf("\nRentrez son hauteur :");
            scanf("%7.2f", &arbre.hauteur);
            while (!verif_float(arbre.hauteur)){
                printf("\nC'est pas correct, c'est un nombre à virgule supérieur à 0\n");
                printf("Retapez la hauteur :");
                scanf("%7.2f", &arbre.hauteur);

            }
            printf("\nRentrez son diamètre :");
            scanf("%8.2f", &arbre.diametre);
            while (verif_float(arbre.diametre)){
                printf("\nC'est pas correct, c'est un nombre à virgule supérieur à 0\n");
                printf("Retapez le diamètre :");
                scanf("%8.2f", &arbre.diametre);

            }
            printf("\nRentrez son volume :");
            scanf("%7.2f", &arbre.volume);
            while (verif_float(arbre.volume)){
                printf("\nC'est pas correct, c'est un nombre à virgule supérieur à 0\n");
                printf("Retapez la hauteur :");
                scanf("%7.2f", &arbre.volume);

            }
            printf("\nRentrez son indice de sante sur 10 :");
            scanf("%d", &arbre.sante);
            while (verif_sante(arbre.sante)){
                printf("\nL'indice n'est pas correct, il doit être entre 0 et 10(10 compris)\n");
                printf("Retapez l'indice :");
                scanf("%d", &arbre.sante);
            
            }
            */
            fprintf(fichier,"%6s;%20s;%3d;%7.2f;%8.2f;%7.2f;%d\n",arbre.identifiant,arbre.espece,arbre.age,arbre.hauteur,arbre.diametre,arbre.volume,arbre.sante);
            compteur++;
        }
        fclose(fichier);  
    }else{
        exit(EXIT_FAILURE);
    }

}
int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    const char *nom_fichier = "foret_arbres_50_V1.csv";
    ARBRE *tab_arbres = NULL;
    int  saisie_arbres;
    tab_arbres = malloc(nb_arbres * sizeof (ARBRE)); // allocation  de mémoire pour le tableau des arbres
    printf("\nCombien d'arbres souhaitez-vous saisir ? :");
    scanf("%d", &saisie_arbres);
    ecrire_fichier(nom_fichier, saisie_arbres, tab_arbres);
    
    return 0;
}