#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Permet d'utiliser les fonctions toupper et tolower*/
#include <ctype.h>
/*Permet d'utiliser l'encodage UTF-8 et donc d'afficher les caractères spéciaux*/
#include <Windows.h>

/*Code principale de l'application, elle doit être capable de:
Lire le fichier csv et afficher l'ensembe de ses données de manière visible
Charger les données du fichier csv dans une structure adaptée
Rechercher les arbres d'une même espèce et afficher les données correspondantes
Trier les données selon deux critères différents: par age et par note de santé via deux méthodes de tri différentes

Soit CINQ/SIX fonctions minimum

*/

#define TAILLE_MAX 100
// Variable globale qui compte le nombre d'arbres dans le fichier
int nb_arbres = 0;
/*Déclaration du type de données utilisé pour l'enregistrment des arbres : structure,
avec un tableau dynamique d'éléments ARBRE(déclaré dans la fonction principale)*/
typedef struct{
    char identifiant[6], espece[20];
    int age, sante;
    float hauteur, diametre, volume;
}ARBRE;


/*Lors des essais, un problème a été rencontré, les nombres flottants étaient mal chargés à cause de la virgule 
donc on a crée une fonction qui remplace la virgule du nombre flottant que contient le champ par un point.
Procédure qui remplace les virgules des nombres flottants dans le fichier csv par des points*/
void remplacer_virgule(char *s){
     s[strcspn(s, ",")] = '.';
}

/*Procédure qui parcourt le fichier afin de compter le nombre d'arbres*/
void compte_arbres(const char *nom_fichier, int *nb_arbres){
    FILE* fichier = NULL;// pointeur de fichier
    char chaine[TAILLE_MAX];//tableau de caractères pour stocker chaque ligne lue
    fichier = fopen(nom_fichier, "r");
    if (*nb_arbres != 0){
        *nb_arbres = 0;
    }
    if (fichier != NULL){
        fgets(chaine, sizeof(chaine), fichier); // lire la première ligne (en-tête) et l'ignorer !

            /*On compte le nombre d'arbres grâce à fgets, fgets parcours chaque ligne une par une donc chaque itération est une ligne*/
            while (fgets(chaine, sizeof(chaine), fichier) != NULL){
                (*nb_arbres)++; // incrémenter le compteur d'arbres pour chaque ligne lue
            }
    }else{
        /*Gestion de l'erreur d'ouverture du fichier, perror permet d'afficher le message d'erreur*/
        perror("Erreur avec compte_arbres lors de l'ouverture du fichier.");
        exit(EXIT_FAILURE);
    }
    fclose(fichier); // fermer le fichier après la lecture
}

/*Procédure qui parcourt le fichier et charge les arbres dans le tableau d'arbres  */
void lirecharger_fichier(const char *nom_fichier, ARBRE **tab_arbres){//On pointe vers un tableaux dynamique afin de modifier les éléments sur lesquelles il pointe, donc pointer sur un pointeur donne **
    FILE* fichier = NULL;// pointeur de fichier
    ARBRE* p = NULL; // pointeur vers une structure ARBRE
    char chaine[TAILLE_MAX];//tableau de caractères pour stocker chaque ligne lue
    int i = 0;
    fichier = fopen(nom_fichier, "r"); //a+ pour plus tard

    if(fichier != NULL){

        fgets(chaine, sizeof(chaine), fichier); // lire et ignorer à nouveau la première ligne (en-tête)

        while (fgets(chaine, sizeof(chaine), fichier) != NULL){

            p = &((*tab_arbres)[i]); // pointeur vers l'arbre courant dans le tableau

            char *champ = strtok(chaine, ";"); // découpage de la ligne en champs(token) par le séparateur ";" via strtok
            int champ_num = 1; // compteur de champs

            while ( champ_num < 8){// boucle pour chaque champ(progression sur la ligne) tant qu'il y a des champs et que le nombre de champs est inférieur à 7(qui est le nombre d'attributs d'un arbre donc le nombre de colonnnes dans le fichier csv)

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
        /*Gestion de l'erreur d'ouverture du fichier*/
        perror("Erreur avec lirecharger_fichier lors de l'ouverture du fichier.");
        exit(EXIT_FAILURE);
    }
}



/*Procédure qui affiche les données d'un tableau d'arbres*/
void affiche_tableau(ARBRE *tab_arbres){
    int i;
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
    printf("| ID     | Espèce               | Âge | Hauteur| Diamètre| Volume   | Santé   |\n");
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");

    for (i = 0; i < nb_arbres; i++){
        printf("| %-6s | %-20s | %-3d | %-6.2f | %-7.2f | %-8.2f | %-1d       |\n",//- Permet d'aligner à gauche
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
    printf("Nombre d'arbres lus: %d\n", nb_arbres);
}

/*Procédure qui recherche un arbre dans le tableau*/
void recherche(ARBRE *tab_arbres, char *espece){
    int count = 0;
    printf("\n------Recherche %s ------\n",espece);
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
    printf("| ID     | Espèce               | Âge | Hauteur| Diamètre| Volume   | Santé   |\n");
    printf("+--------+----------------------+-----+--------+---------+----------+---------+\n");
    espece[0] = toupper(espece[0]);
    for (int i = 0 ; i < nb_arbres;i++){
        if (strcmp(tab_arbres[i].espece, espece) == 0){
            printf("| %-6s | %-20s  | %-3d | %-6.2f | %-7.2f | %-8.2f | %-1d       |\n",//- Permet d'aligner à gauche
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
        printf("Arbre(s) %s trouvé(s) : %d\n",espece,count);
        if (count == 0){
            printf("L'espèce n'est pas trouvable.\n");
        }
}

/*Procédure qui effectue un tri et affiche le tableau correspondant*/
void tri(ARBRE *tab_arbres){
    int posMin = 0; // initialisation de la variable position minimum pour le tri par sélection par l'age
    char choix[10] = ""; // initialisation de la chaine de caractère choix (qui sera plus tard soit age soit sante)
    ARBRE tmp; // initialisation de tmp qui sera de type ARBRE
    ARBRE *tab_res = malloc(nb_arbres * sizeof(ARBRE)); // initialisation de tab_res avec le nombre de cases du tableau * la taille d'une variable de type arbre

    for(int i = 0; i < nb_arbres; i++){
        tab_res[i] = tab_arbres[i]; // copie tab_arbres dans tab_res pour garder tab_arbres en original
    }
    
    printf("Voulez-vous trier par âge ou par santé ?(âge/santé) :");
    scanf("%s", choix); 
    
    if (strcmp(choix, "âge") == 0){ // tri par selection si on choisit age
        for(int i = 0; i < nb_arbres - 1; i++){//-1 et non -2 !
            posMin = i;
            for(int j = i + 1; j < nb_arbres; j++){
                if(tab_res[j].age < tab_res[posMin].age){
                    posMin = j;
                }
            }
            tmp = tab_res[i];
            tab_res[i] = tab_res[posMin]; // Ces 3 lignes corresondent à l'échange 
            tab_res[posMin] = tmp;

        }

        

    }

    else if (strcmp(choix, "santé") == 0){ // tri par insertion si on choisit sante
        for(int i = 1; i < nb_arbres ; i++){
            tmp = tab_res[i];
            int j = i - 1;
            while(j >= 0 && tab_res[j].sante > tmp.sante){
                tab_res[j+1] = tab_res[j];
                j = j - 1;
            }
            tab_res[j + 1] = tmp; // range la plus petite valeur du tableau de la partie droite (non trié) dans la partie gauche (déjà triée)
        }
    }
    printf("\n------Tri par %s ------\n",choix);
    affiche_tableau(tab_res); // utilisation de la fonction affiche tableau pour afficher le résultat du tri
    free(tab_res);
}



/* Inverse de la fonction remplacer_virgule pour l'écriture dans le fichier csv(respect du format)*/
void flottant_chaine(float valeur, char *chaine){
    sprintf(chaine,"%.2f", valeur);
    chaine[strcspn(chaine, ".")] = ',';
}


/*Fonction qui rajoute un arbre dans le tableau*/
void ajouter_arbre(ARBRE **tab_arbres, ARBRE *arbre, int *nb_arbres){
    ARBRE *temp = realloc(*tab_arbres, (*nb_arbres + 1) * sizeof(ARBRE));
    ARBRE *p = NULL;
    if (temp != NULL){
        *tab_arbres = temp;
        (*tab_arbres)[*nb_arbres]= *arbre; // Ajouter le nouvel arbre à la fin du tableau
        (*nb_arbres)++; // Incrémenter le nombre d'arbres
    }else{
        printf("Erreur de réallocation de mémoire.\n");
    }
}

/*Fonction qui vérifie si le nombre est un entier supérieur à 0*/
int lire_entier(const char *prompt){
    char chaine[32];
    int valeur, stop = 1;
    while (stop){//Boucle jusqu'à ce que l'utilisateur entre une valeur valide
        printf("%s", prompt);
        if (fgets(chaine, sizeof(chaine), stdin) != NULL){
           
            chaine[strcspn(chaine, "\n")] = '\0';// Supprimer le \n sinon problème à l'affichage
            
            if (sscanf(chaine, "%d", &valeur) == 1){//On vérifie que la chaine contient bien un entier
                if (valeur > 0) {
                    return valeur;//On vérifie aussi que l'entier est bien supérieur à 0
                }
            } 
            printf("Entrée invalide. Veuillez entrer un entier valide.\n");
            
        }else{
            /*Gestion de l'erreur si la saisie n'est pas faite*/
            printf("Erreur de lecture. Veuillez réessayer.\n");
        }
    }
}

/*Fonction qui vérifie que le nombre saisie est un flottant supérieur à 0*/
float lire_flottant(const char *prompt){
    char chaine[32];
    int  stop = 1;
    float valeur;
    while (stop){//Boucle jusqu'à ce que l'utilisateur entre une valeur valide
        printf("%s", prompt);
        if (fgets(chaine, sizeof(chaine), stdin) != NULL){

            chaine[strcspn(chaine, "\n")] = '\0'; // Supprimer le \n sinon problème à l'affichage

            if (sscanf(chaine, "%f", &valeur) == 1){//On vérifie que la chaine contient bien un flottant
                if (valeur > 0) {//On vérifie aussi que le flottant est bien supérieur à 0
                    return valeur; 
                }
            } 
            printf("Entrée invalide. Veuillez entrer un flottant valide.\n");
            
        }else{
            /*Gestion de l'erreur si la saisie n'est pas faite*/
            printf("Erreur de lecture. Veuillez réessayer.\n");
        }
    }
}


/*Procédure qui permet à l'utilisateur d'écrire dans le fichier csv*/
void ecrire_fichier(const char *nom_fichier, int nba, ARBRE **tab_arbres){
    FILE *fichier = NULL;// pointeur de fichier
    ARBRE arbre;// déclaration d'une variable de type ARBRE pour stocker les données saisies pour chaque arbre
    char hauteur_str[32], volume_str[32],diametre_str[32], chaine[TAILLE_MAX];//chaine pour stocker l'arbre formaté en chaîne de caractère et trois chaînes pour stocker les trois attributs flottants
    int i, compteur = nb_arbres + 1;// compteur pour l'identifiant des arbres à saisir
    fichier = fopen(nom_fichier, "a+");//a+ pour ajouter à la fin du fichier sans écraser les données existantes, sert aussi à lire le fichier
    if (fichier != NULL){
        for (i = 0; i < nba; i++){
            printf("\n---Saisie de l'arbre %d---\n", i + 1);
            /*Saisie des attributs  de l'arbre*/
            snprintf(arbre.identifiant,sizeof(arbre.identifiant),"AR%03d",compteur); //auto intcrémentation de l'id de l'arbre, snprintf permet de formater l'identifiant avec la forme ARXXX du fichier csv 
            printf("Rentrez son espèce :");
            fgets(arbre.espece, sizeof(arbre.espece), stdin);
            arbre.espece[0] = toupper(arbre.espece[0]);
            arbre.espece[strcspn(arbre.espece, "\n")] = '\0'; // Supprimer le \n sinon problème à l'affichage, strcspn renvoie l'index du premier caractère trouvé dans la chaîne (ici le \n)
            /*Fonctions de vérification qui affecte une valeur correcte à l'attribut correspondant de l'arbre*/
            arbre.age = lire_entier("Rentrez son âge :");
            arbre.hauteur = lire_flottant("Rentrez sa hauteur :");
            arbre.diametre = lire_flottant("Rentrez son diamètre :");
            arbre.volume = lire_flottant("Rentrez son volume :");
            arbre.sante = lire_entier("Rentrez son indice de sante sur 10 :");
            /*Transformer les flottants en chaîne pour mettre les virgules comme dans le fichier csv*/
            flottant_chaine(arbre.hauteur, hauteur_str);
            flottant_chaine(arbre.volume, volume_str);
            flottant_chaine(arbre.diametre, diametre_str);
            /*Arbre placé dans une chaîne de caractère*/
            sprintf(chaine,"\n%s;%s;%d;%s;%s;%s;%d;",
                arbre.identifiant,
                arbre.espece,
                arbre.age,
                hauteur_str,
                diametre_str,
                volume_str,
                arbre.sante
            );
            /*Ecriture de l'arbre dans le fichier*/
            fprintf(fichier, "%s", chaine);
            ajouter_arbre(tab_arbres, &arbre, &nb_arbres);//Ajout de l'arbre dans le tableau dynamique
            compteur++;// Incrémentation du compteur pour l'identifiant à chaque nouvel arbre
        }
        fclose(fichier);  
    }else{
        /*Gestion de l'erreur si le fichier n'est pas ouvrable*/
        perror("Erreur avec ecrire_fichier lors de l'ouverture du fichier.");
        exit(EXIT_FAILURE);
    }

}

/*Fonction principale*/
int main(){
    SetConsoleOutputCP(CP_UTF8);//Permet l'affichage des caractères spéciaux
    SetConsoleCP(CP_UTF8);//Permet la saisie des caractères spéciaux
    const char *nom_fichier = "foret_arbres_50_V1.csv";
    int stop = 1, saisie_arbres;
    ARBRE *tab_arbres = NULL;// déclaration du tableau dynamique d'arbres qu'on utilise pour charger les données du fichier csv
    char  cherche_espece[20] = "", demarrage[20]="";
    compte_arbres(nom_fichier, &nb_arbres);//Procédure qui compte le nombre d'arbres dans le fichier
    tab_arbres = malloc(nb_arbres * sizeof (ARBRE)); // allocation  de mémoire pour le tableau des arbres
    lirecharger_fichier(nom_fichier, &tab_arbres);//Procédure qui lit et charge les arbres du fichier dans le tableau dynamique
    if (nb_arbres != 0){

        printf("Les données du tableau sont :\n");
        affiche_tableau(tab_arbres);//Affichage du tableau des arbres

        while (stop){//Boucle principale du programme
            printf("\nQue voulez vous faire ?(Afficher/Saisir/Rechercher/Trier/Rien) :");
            fgets(demarrage, sizeof(demarrage), stdin);
            demarrage[strcspn(demarrage, "\n")] = '\0'; // Supprimer le \n sinon problème à l'affichage
            demarrage[0] = toupper(demarrage[0]);// Mettre la première lettre en majuscule si minuscule sinon strcmp ne retourne pas 0
            /* Comparaison de la saisie et des différentes options*/
            if (strcmp(demarrage, "Saisir") == 0){
                saisie_arbres = lire_entier("Combien d'arbres souhaitez-vous saisir ? :");//Fonction qui vérifie que la saisie est un bien entier ET qu'il est supérieur à 0
                ecrire_fichier(nom_fichier, saisie_arbres, &tab_arbres);//Fonction qui permet d'écrire dans le fichier csv et de rajouter les arbres dans le tableau dynamique

            }else if (strcmp(demarrage, "Rechercher") == 0){
                printf("\n Quelle espece d'arbre souhaitez vous rechercher ? :");
                fgets(cherche_espece, sizeof(cherche_espece), stdin);
                cherche_espece[strcspn(cherche_espece, "\n")] = '\0'; // Supprimer le \n sinon problème à l'affichage
                recherche(tab_arbres,cherche_espece);//Procédure qui recherche une espèce dans le tableau dynamique et affiche tous les arbres correspondants
                
            }else if (strcmp(demarrage, "Trier") == 0){
                tri(tab_arbres);//Procédure qui trie le tableau dynamique selon l'age ou la sante et affiche une copie du tableau trié
            }else if (strcmp(demarrage, "Rien") == 0){
                printf("Aurevoir !\n");
                stop = 0;// Arrête la boucle principale donc l'utilisateur quitte le programme
            }else if(strcmp(demarrage, "Afficher") == 0){
                affiche_tableau(tab_arbres);//Procédure qui affiche les données du  tableau dynamique donc le fichier csv
            }else{
                printf("Ce n'est pas possible.\n");// Message d'erreur si la saisie ne correspond à aucune option
            }
        }
    }else{
        /*Si la procédure compte_arbre n'en compte aucun*/
        printf("Les données du tableau sont :");
        printf("Il n'y a pas de données disponibles.\n");
    }
    
    free(tab_arbres); // libération de la mémoire allouée au tableau dynamique
    return 0;
    
}
