#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <regex.h>
//Definition des structures
typedef struct 
{
    int h,mn,sec;
}heure;
typedef struct 
{
    char nameuser[20];
    char mdp[15];
    int type;
    int etat;
}User;
typedef struct 
{
    int j;
    int m;
    int a;
}Date;
typedef struct 
{
   char dest[20];
   char source[20];
   char contenue[1000];
   Date date_en;
   char etat[20];

}Message;

typedef struct 
{
    char mat[20];
    char nom[20];
    char prenom[30];
    Date ddn;
    char classe[10];
    User identifiants;
    heure retard;
    int msglus;
    int msgnonlus;
    Message msgrecu;
}Etudiant;
typedef struct 
{
   char nom[20];
   char prenom[20];
   User login;
   Message msgenvoie;
}Admin;



//declaration des fonctions
User SaisiIdentifiant();
int connexion(User);
void afficherMenuadmin();
void afficherMenuapprenant();
void marquerpresenceEtudiant(char []);
void recupChaine(char [],char []);
int Presence(char mat[]);
//definitions des fonctions
void date_suivante(int *jour, int *mois, int *annee) {
    // Vérification des limites du mois
    if (*mois < 1 || *mois > 12) {
        printf("Mois invalide\n");
        return;
    }

    // Vérification des limites du jour
    if (*jour < 1 || *jour > 31) {
        printf("Jour invalide\n");
        return;
    }

    // Passage à la date suivante
    (*jour)++;

    // Gestion des mois avec 30 jours
    if ((*mois == 4 || *mois == 6 || *mois == 9 || *mois == 11) && (*jour > 30)) {
        *jour = 1;
        (*mois)++;
    }
    // Gestion du mois de février
    else if (*mois == 2) {
        // Vérification si l'année est bissextile
        int bissextile = ((*annee % 4 == 0) && (*annee % 100 != 0)) || (*annee % 400 == 0);

        if (bissextile && (*jour > 29)) {
            *jour = 1;
            (*mois)++;
        } else if (!bissextile && (*jour > 28)) {
            *jour = 1;
            (*mois)++;
        }
    }
    // Gestion des mois avec 31 jours
    else if (*jour > 31) {
        *jour = 1;
        (*mois)++;
    }

    // Passage à l'année suivante
    if (*mois > 12) {
        *mois = 1;
        (*annee)++;
    }
}
void recupChaine(char chaine[],char msg[]) 
{
    printf("%s\n",msg);
    do {
        
        fgets(chaine, 50, stdin);
        size_t len = strlen(chaine);
        if (len > 0 && chaine[len - 1] == '\n') 
        {
            
            chaine[len - 1] = '\0';
        }
    } while (strlen(chaine) == 0 );
}
void saisiMdp(char pass[])
{
    int j = 0;
    do
    {
    printf("\nMot de passe : ");
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO); // Masquer les caractères saisis
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (1) {
        char c = getchar(); // Lire un caractère sans l'afficher

        if (c == '\r' || c == '\n') // Si l'utilisateur appuie sur Entrée
            break;

        pass[j] = c; // Stocker le caractère dans le mot de passe
        printf("*"); // Afficher une étoile à l'écran
        j++;
    }
    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaurer les paramètres d'origine
    pass[j] = '\0'; // Terminer la chaîne de caractères
    if (j==0)
    {
        puts("Le mot de pass est obligatoire");
    }
    
    } while (j==0);
    
}

User SaisiIdentifiant()
{
        User u1;
        char login[50];
        char pass[20];
        puts("Entrer votre login et mot de pass ");
       recupChaine(login,"Login");
       saisiMdp(pass);
       strcpy(u1.nameuser,login);
       strcpy(u1.mdp,pass);
        return u1;
}
int connexion(User u1)
{
     FILE *file = fopen("login.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
     int maxUsers = 300;
    User users[maxUsers];
    int cmptusers = 0;
    while(fscanf(file, "%d %s %s %d",&users[cmptusers].type, users[cmptusers].nameuser, users[cmptusers].mdp, &users[cmptusers].etat)==4)
    {
        cmptusers++;
    }
    fclose(file);
    for (int i = 0; i < cmptusers; i++)
    {
       if (strcmp(users[i].nameuser, u1.nameuser) == 0 && strcmp(users[i].mdp,u1.mdp) == 0)
    
        //return 1;
        if (users[i].type==1)
        {
            return 1;//Pour que je puisse recuperer le type
            //puts("Vous ete connecter en tant que admin");
        }
        else
        {
             if(users[i].etat==1)// c'est un apprenant non bloque
            {
                return 2;
            }
            else
            {
                return 3;// l'apprenant est bloque
            }
            
        }
           
       
    }
       return 0;
 }
 void afficherMenuadmin()
 {
    puts("-----------------------------------------------------------------");
    puts("\t\tBienvenu cher Admin");
    printf("1………..GESTION DES ÉTUDIANTS\n2………..GÉNÉRATION DE FICHIERS\n3………..MARQUER LES PRÉSENCES\n4………..ENVOYER UN MESSAGE\n5………..QUITTER\n");
 }
 void afficherMenuapprenant()
 {
    puts("-----------------------------------------------------------------");
    puts("\t\tBienvenu cher Apprenant");
    printf("1………..MARQUER MA PRÉSENCE\n2………..NOMBRE DE MINUTES D’ABSENCE\n3………..MES MESSAGES (0)\n4………..QUITTER\n");
 }
 int choice()
 {
    int choice;
    puts("Que voullez vous faire");
    do
    {
        scanf("%d",&choice);
    } while (choice!=1 && choice!=2 && choice!=1 && choice!=3 && choice!=4 &&choice!=5);
}

void marquerpresenceEtudiant(char matricule[])
{
    
    recupChaine(matricule,"");
    if(Presence(matricule)==-1) 
    {
        puts("cet apprenant a deja emarge");
    }
    else if (Presence(matricule)==1)
    {
        puts("Avec succes");
    } 
} 
int Presence(char matricule[]) {
    FILE *fichierentree = fopen("listeetudiant.txt", "r");
    if (fichierentree == NULL) {
        printf("Erreur lors de l'ouverture du fichier listeetudiant.txt\n");
        return -1; // Indiquer une erreur
    }

    char ligne[200], nom[50], prenom[50], classe[50],mat[50];
    int exist = 0;

    while (fgets(ligne, sizeof(ligne), fichierentree)) {
        sscanf(ligne, "%s %s %s %s", mat, nom, prenom, classe);
        if (strcmp(mat, matricule) == 0) {
            exist = 1;
            break;
        }
    }

    fclose(fichierentree);

    if (exist) 
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        char date[30], date1[30], ligne1[150], mat1[30], classe1[30];
        char heure[30], nom1[30], prenom1[30], heure1[30];
        strftime(heure, sizeof(heure), "%H:%M:%S", &tm);
        char nomComplet[70];
        strftime(date, sizeof(date), "%d_%m_%Y", &tm);
        snprintf(nomComplet, sizeof(nomComplet), "%s_%s.txt","Listepresence", date);
        FILE *fichiersortie = fopen(nomComplet, "a");
        FILE *fichiersortie1 = fopen(nomComplet, "ra");
        if (fichiersortie == NULL) {
            printf("Erreur lors de l'ouverture du fichier %s\n",nomComplet);
            return 10; // Indiquer une erreur
        }
        if (strcmp(date, date1) != 0)
        {
            fprintf(fichiersortie, "------------------------------------------------------------------------------------\n");
            fprintf(fichiersortie, "               Liste présence du %s\n", date1);
            fprintf(fichiersortie, "------------------------------------------------------------------------------------\n");
            fprintf(fichiersortie, "| Matricule:\t|     NOM      \t|          PRÉNOM       \t|    Heure Marquage \t|      CLASSE      |\n");
            fprintf(fichiersortie, "------------------------------------------------------------------------------------\n");

        }
        
        while (fgets(ligne1, 100, fichiersortie1) != NULL) 
        {
            sscanf(ligne1, "%s %s %s %s %s \n", mat1, nom1, prenom1,heure1, classe1  );
            if (strcmp(date, date1) == 0 && strcmp(matricule, mat1) == 0) 
            {
                return -1; // L'étudiant a déjà été enregistré pour la même date
            }
        }

         fprintf(fichiersortie, "|%s         \t%s          \t%s                     \t%s          \t%s        \n",  matricule, nom, prenom, classe, heure);
        fprintf(fichiersortie, "+----------------------------------------------------------------------------------+\n");
        fclose(fichiersortie);
                puts("succes");
        return 1; // Succès, présence enregistrée
    } 
    else
     {
          if (strcmp(matricule,"q")!=0)
        {
           printf("Matricule non trouvé dans le fichier des étudiants\n");
           return 0; 
        }
         // L'étudiant n'a pas été trouvé dans le fichier des étudiants
    }
}
Date controleDate()
{
    
     Date d;
     char date[15];
     do
     {
         puts("Entrer la date pour le quel vous voullez voir la liste des presents");
            puts("Le format est j/m/a ou j-m-a");
        do {
            recupChaine(date,"");
            fflush(stdin);
            if (sscanf(date, "%d-%d-%d", &d.j, &d.m, &d.a) !=3 || sscanf(date, "%d/%d/%d", &d.j, &d.m, &d.a) !=3  )
            {
                printf("format de date invalide!!!\n");
            }
            
        } while(sscanf(date, "%d-%d-%d", &d.j, &d.m, &d.a) != 3 || sscanf(date, "%d/%d/%d", &d.j, &d.m, &d.a) !=3 );
     } while (d.j<0 || d.j>31 || d.m<0 || d.m>12 || d.a<=0);
     
     return d;

}
void genererFichierPresencepardate()
{
        Date d;
     char nomfich[50];
       d=controleDate();
       printf("La liste des etudiants present le %d-%d-%d est",d.j, d.m, d.a);
    snprintf(nomfich, "Listepresence_%d_%d_%d.txt", d.j, d.m, d.a);      
    FILE *fichier = fopen(nomfich, "r");
    if (fichier == NULL) {
        perror("Fichier introuvable");
        return 1;
    }

    int caractere;
    while ((caractere = fgetc(fichier))!= EOF) {
        putchar(caractere); 
    }
}
void generertoutlesFichierPresence(Date datefin)
{
   
    Date date;
    char d[15];
    time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        strftime(d, sizeof(date), "%d-%m-%Y", &tm);
        sscanf(d, "%d-%d-%d", &date.j, &date.m, &date.a);
        printf("-----------------------------------------------------------------------\n");
        printf("|                       LISTE DES PRESENCES                           |\n");
        printf("-----------------------------------------------------------------------\n\n");
    while (date.j != datefin.j && date.m != datefin.m && date.a != datefin.a)
    {
        genererFichierPresencepardate();
        date_suivante(&date.j,&date.m,&date.a);
    }
    
}
void genererFichier()
{
    int choix;
    
    puts("Voullez afficher la liste des presences par date ou toute la liste");
    printf("1- Liste des presences par date\n2- Liste de toutes les presences\n");
    do
    {
        scanf("%d",&choix);
        if(choix!=1 && choix!=2)
        puts("Entrer 1 ou 2");
    } while (choix!=1 && choix!=2);
    if (choix==1)
    {
        genererFichierPresencepardate();
      
    }
    else
    {
        Date date;
        puts("Entrer une date ,le programme vous affiche la liste des presence depuis ce jour");
        date=controleDate();
        generertoutlesFichierPresence(date);
    }
    

}
void Envoie
#endif