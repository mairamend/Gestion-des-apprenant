#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
//Definition des structures
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
    char mat[20];
    char nom[20];
    char prenom[30];
    Date ddn;
    char classe[10];

}Etudiant;



//declaration des fonctions
User SaisiIdentifiant();
int connexion(User);
void afficherMenuadmin();
void afficherMenuapprenant();
void marquerpresenceEtudiant(char []);
void recupChaine(char [],char []);
Etudiant verifietudiant(Etudiant[],int,char[]);
int recuplisteEtudiant(Etudiant [],int );
int ecrisListepresence(Etudiant );
int siEnapasemarge(Etudiant E[],int nbres,Etudiant e1);
//definitions des fonctions
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
        Etudiant e1;
    int maxE = 300;
    Etudiant E[maxE],E1[maxE];
    
    int nbres;
    
    recupChaine(matricule,"");
     nbres=recuplisteEtudiant(E,maxE);
    e1=verifietudiant(E,nbres,matricule);
    if (siEnapasemarge(E1,maxE,e1)==1)
    {
        ecrisListepresence(e1);
        
    }
    else
    {
        puts("Vous avez deja emarger");
        
    }   
    
} 
Etudiant verifietudiant(Etudiant E[],int nbres,char matricule[])
{
    Etudiant e1;
    int ct=0;
    for (int i = 0; i < nbres; i++)
      {
        if  (strcmp(matricule, E[i].mat) == 0)
        { 
            strcpy(e1.mat, E[i].mat);
            strcpy(e1.nom, E[i].nom);
            strcpy(e1.prenom, E[i].prenom);
            strcpy(e1.classe, E[i].classe);
           return e1;
           ct++; 
        } 
      }   

        if(ct==0 && strcmp(matricule,"q")!=0)
            printf("Vous ne faite pas parti de l'ecole, ou votre matricules est incorect\n");

}    
int siEnapasemarge(Etudiant E[],int nbres,Etudiant e1)
{
    
    
    int cmptE=0;
    FILE *fichierSortie; 
    fichierSortie = fopen("listepresences.txt", "r");

    if (fichierSortie == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        return 1;
    }
       
     while(fscanf(fichierSortie, "%s %s %s %s",E[cmptE].mat, E[cmptE].nom, E[cmptE].prenom, E[cmptE].classe)!=EOF)
     {
        cmptE++;
     }
     for (int i = 0; i <= cmptE; i++)
      {
        if  (strcmp(e1.mat, E[i].mat) != 0)
        { 
            return 1;//l'etudiant n'a pas encore emarger
        } 
        else
        return 0;
      }  
     
    fclose(fichierSortie);
}
int ecrisListepresence(Etudiant e1)
{
    FILE *fichierSortie; 
    fichierSortie = fopen("listepresences.txt", "a");

    if (fichierSortie == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        return 1;
    }
            time_t heuredemarquage = time(NULL);
            struct tm *tempsLocal = localtime(&heuredemarquage);
            fprintf(fichierSortie, "\n%s %s %s %s %s %02d:%02d:%02d\n", e1.mat,e1.nom,e1.prenom,e1.classe,"present",tempsLocal->tm_hour, tempsLocal->tm_min, tempsLocal->tm_sec);
    
       
    
    fclose(fichierSortie);   
}

int recuplisteEtudiant(Etudiant E[],int nbres)
{
     int cmptE = 0;   
    FILE *fichierEntree;
    
     fichierEntree = fopen("listeetudiant.txt", "r");
    if (fichierEntree == NULL) {
        perror("Erreur lors de l'ouverture du fichier d'entrée");
        return 1;
    }
    while(fscanf(fichierEntree, "%s %s %s %s",E[cmptE].mat, E[cmptE].nom, E[cmptE].prenom, E[cmptE].classe)!=EOF)
    {
        
       cmptE++;
    }
    fclose(fichierEntree);
    nbres=cmptE;
    return nbres;
}
#endif 
   