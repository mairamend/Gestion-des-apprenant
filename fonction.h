#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
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

//definitions des fonctions
User SaisiIdentifiant()
{
        User u1;
        int space;
        puts("Entrer votre login et mot de pass ");
        
       do
        {
             puts("Login");
             fgets(u1.nameuser, sizeof(u1.nameuser), stdin);
             size_t len = strlen(u1.nameuser);
            if (len > 0 && u1.nameuser[len - 1] == '\n') 
            {
                u1.nameuser[len - 1] = '\0';
            }
            if (len==0)
            {
                puts("Le login est obligatoire");
            }
            
        
        }while(strlen(u1.nameuser)==0);
        do
        {
            puts("Mot de pass");
            //fgets(u1.mdp, sizeof(u1.mdp), stdin);
            strncpy(u1.mdp, getpass(""), sizeof(u1.mdp) - 1);
             size_t len = strlen(u1.mdp);
              u1.mdp[sizeof(u1.mdp) - 1] = '\0';
            if (len > 0 && u1.mdp[len - 1] == '\n') 
            {
                u1.mdp[len - 1] = '\0';
                
            }
             if (len==0 && u1.mdp[len - 1] == '\n')
            {
               puts("Le mot de pass est obligatoire");
            }
            
        }while(strlen(u1.mdp)==0);  
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
void marquerpresence()
{
    int choix;
    Etudiant e;
    puts("Pour Marquer presence entrer la classe");
    puts("1- Dev Data");
    puts("2- Dev web");
    puts("3- Ref dig");
    do
    {
        scanf("%d",&choix);
    } while (choix!=1 && choix!=2 &&choix!=3);
    switch (choix)
    {
    case 1:
      do
        {
             puts("Entrer la matricule pour marquer la presence");
             fgets(e.mat, sizeof(e.mat), stdin);
             size_t len = strlen(e.mat);
            if (len > 0 && e.mat[len - 1] == '\n') 
            {
                e.mat[len - 1] = '\0';
            }
            if (len==0)
            {
                puts("La matricule est obligatoire");
            }
         
        }while(strlen(e.mat)==0);
        break;
    case 2:
        break;
    default:
        break;
    }

}

 #endif 
   