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


/*Lors des essais, un problème a été rencontré, les nombres flottants étaient mal chargés à cause de la virgule 
donc on a crée une fonction qui remplace la virgule du nombre flottant que contient le champ par un point.
*/
void remplacer_virgule(char *s){
    for (int i = 0; s[i]; i++){
        if (s[i] == ','){
            s[i] = '.';
        }
    }
}



void car_speciaux(char *s){

}
/*Prototype de la fonction de lecture, ses paramètres sont le nom du fichier et le nombre d'arbres, 
passés par pointeur 
*/
void lirecharger_fichier(const char *nom_fichier, int *nb_arbres, ARBRE **tab_arbres){//On pointe vers un tableaux dynamique afin de modifier les éléments sur lesquelles il pointe, donc pointer sur un pointeur donne **
    FILE* fichier = NULL;// pointeur de fichier
    ARBRE* p = NULL; // pointeur vers une structure ARBRE
    char chaine[TAILLE_MAX];//tableau de caractères pour stocker chaque ligne lue
    int i = 0;
    fichier = fopen(nom_fichier, "r"); //a+ pour plus tard

    if(fichier != NULL){

        fgets(chaine, sizeof(chaine), fichier); // lire la première ligne (en-tête) et l'ignorer !

        /*On compte le nombre d'arbres grâce à fgets, fgets parcours chaque ligne une par une donc chaque itération est une ligne*/
        while (fgets(chaine, sizeof(chaine), fichier) != NULL){
            (*nb_arbres)++; // incrémenter le compteur d'arbres pour chaque ligne lue
        }
        if (*tab_arbres != NULL){
             *tab_arbres = realloc(*tab_arbres, (*nb_arbres) * sizeof(ARBRE));// réallocation de mémoire pour le tableau dynamique qui pointe vers des structures arbre, pour une taille exacte
        }
        rewind(fichier); // revenir au début du fichier pour relire les données

        fgets(chaine, sizeof(chaine), fichier); // lire et ignorer à nouveau la première ligne (en-tête)

        while (fgets(chaine, sizeof(chaine), fichier) != NULL){

            p = &((*tab_arbres)[i]); // pointeur vers l'arbre courant dans le tableau
            char *champ = strtok(chaine, ";"); // découpage de la ligne en champs(token) par le séparateur ";" via strtok
            int champ_num = 1; // compteur de champs

            while ( champ_num < 8){// boucle pour afficher chaque champ(progression sur la ligne) tant qu'il y a des champs et que le nombre de champs est inférieur à 7(qui est le nombre d'attributs d'un arbre donc le nombre de colonnnes dans le fichier csv)

                      if (champ_num == 1) {
                        strcpy(p->identifiant, champ); // copier l'identifiant dans la structure ARBRE via strcpy
                    } else if (champ_num == 2) {
                        strcpy(p->espece, champ); // copier l'espèce dans la structure ARBRE
                    } else if (champ_num == 3) {
                        p->age = atoi(champ); // convertir et stocker l'âge dans la structure ARBRE via atoi
                    } else if (champ_num == 4) {
                        remplacer_virgule(champ);//On change la virgule du nombre flottant par un point 
                        p->hauteur = atof(champ); // convertir et stocker la hauteur dans la structure ARBRE via atof
                    } else if (champ_num == 5) {
                        remplacer_virgule(champ);
                        p->diametre = atof(champ); // convertir et stocker le diamètre dans la structure ARBRE
                    } else if (champ_num == 6) {
                        remplacer_virgule(champ);
                        p->volume = atof(champ); // convertir et stocker le volume dans la structure ARBRE
                    } else if (champ_num == 7) {
                        p->sante = atoi(champ); // convertir et stocker la santé dans la structure ARBRE
                    }

                champ = strtok(NULL, ";");// obtenir le champ suivant, NULL indique de continuer à partir de la position actuelle
                champ_num++;// incrémenter le compteur de champs   
            
            }
            i++; // incrémenter l'index du tableau des arbres
        }

        fclose(fichier); // fermer le fichier après la lecture

    }else{
        printf("Erreur d'ouverture du fichier %s\n", nom_fichier);
    }
}



void affiche_tableau(ARBRE *tab_arbres, int nb_arbres){
    int i;
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
    printf("| ID     | Espece               | Age | Hauteur| Diametre| Volume   | Sante   |\n");
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");

    for (i = 0; i < nb_arbres; i++){
        printf("| %-6s | %-20s | %-3d | %-7.2f| %-8.2f| %-7.2f  | %-d       |\n", 
        tab_arbres[i].identifiant,
        tab_arbres[i].espece,
        tab_arbres[i].age,
        tab_arbres[i].hauteur,
        tab_arbres[i].diametre,
        tab_arbres[i].volume,
        tab_arbres[i].sante
        );
    }

    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
}


void recherche(ARBRE *tab_arbres, int nbr, const char *espece){
    int count = 0;
    printf("\n------Recherche %s ------\n",espece);
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
    printf("| ID     | Espece               | Age | Hauteur| Diametre| Volume   | Sante   |\n");
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
    for (int i = 0 ; i < nbr;i++){
        if (strcmp(tab_arbres[i].espece, espece) == 0){
            printf("| %-6s | %-20s | %-3d | %-7.2f| %-8.2f| %-7.2f  | %-d       |\n", 
            tab_arbres[i].identifiant,
            tab_arbres[i].espece,
            tab_arbres[i].age,
            tab_arbres[i].hauteur,
            tab_arbres[i].diametre,
            tab_arbres[i].volume,
            tab_arbres[i].sante
            );
            count++;
        }

    }
     printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
    printf("Arbres %s trouve : %d",espece,count);
}


void tri(ARBRE *tab_arbres, int nbr){
    int posMin = 0;
    char choix[10] = "";
    ARBRE tmp;
    ARBRE *tab_res = malloc(nbr * sizeof(ARBRE));

    for(int i = 0; i < nbr; i++){
        tab_res[i] = tab_arbres[i];
    }
    printf("Voulez-vous trier par age ou par sante (age/sante) :\n");
    scanf("%s", choix);
    if (strcmp(choix, "age") == 0){
        for(int i = 0; i < nbr - 2; i++){
            posMin = i;
            for(int j = i + 1; j < nbr; j++){
                if(tab_res[j].age < tab_res[posMin].age){
                    posMin = j;
                }
            }
            tmp = tab_res[i];
            tab_res[i] = tab_res[posMin];
            tab_res[posMin] = tmp;

        }

        

    }

    else if (strcmp(choix, "sante") == 0){
        for(int i = 1; i < nbr ; i++){
            tmp = tab_res[i];
            int j = i - 1;
            while(j >= 0 && tab_res[j].sante > tmp.sante){
                tab_res[j+1] = tab_res[j];
                j = j - 1;
            }
            tab_res[j + 1] = tmp;
        }
    }

    affiche_tableau(tab_res, nbr);
}



int main(){

    const char *nom_fichier = "foret_arbres_50_V1.csv";
    int nb_arbres = 0, stop = 1, saisie_arbres;
    ARBRE *tab_arbres = NULL;
    char reponse[20] = "", cherche_espece[20] = "", demarrage[20]="";

    tab_arbres = malloc(TAILLE_MAX * sizeof (ARBRE)); // allocation initiale de mémoire pour le tableau des arbres
    lirecharger_fichier(nom_fichier, &nb_arbres, &tab_arbres);
    printf("Nombre d'arbres lus: %d\n", nb_arbres);
    if (nb_arbres != 0){

        printf("Les données du tableau sont :\n");
        affiche_tableau(tab_arbres, nb_arbres);

        while (stop){
            printf("\nQue voulez vous faire ?(Saisir/Rechercher/Trier/Rien) :");
            scanf("%10s",demarrage);
            if (strcmp(demarrage, "Saisir") == 0){
                printf("\nCombien d'arbres souhaitez-vous saisir ? :");
                scanf("%d", &saisie_arbres);

                printf("\n Les arbres ont bien été rajoutés.");

            }else if (strcmp(demarrage, "Rechercher") == 0){
                printf("\n Quelle espece d'arbre souhaitez vous rechercher ? :");
                scanf("%s", cherche_espece);
                recherche(tab_arbres, nb_arbres, cherche_espece);
                
            }else if (strcmp(demarrage, "Trier") == 0){

            }else if (strcmp(demarrage, "Rien") == 0){
                printf("Aurevoir !\n");
                stop = 0;
            }else{
                printf("Ce n'est pas possible.\n");
            }
        }
    }else{
        printf("Les données du tableau sont :");
        printf("Il n'y a pas de données disponibles.\n");
    }
    
    free(tab_arbres); // libération de la mémoire allouée pour les arbres
    return 0;
    
}
