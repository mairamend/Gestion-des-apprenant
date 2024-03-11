#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
int main()
{
        retry:
        while(1)
    {
        int choix;
        User u1=SaisiIdentifiant();
        if (connexion(u1)==1)
        {
            MenuA:
                afficherMenuadmin();
                choix=choice();
                switch (choix)
                {
                case 1:
                    
                    break;
    

                case 2:
                    genererFichier();
                    break;
                case 3:
                char mat[20],pass[20];
                //char exit[20];
                retry2:
                do
                {
                    puts("Entrer le matricule ou q pour quitter");
                    marquerpresenceEtudiant(mat);
                    if (strcmp(mat,"q")==0)
                    {
                    saisiMdp(pass);
                    if (strcmp(pass,u1.mdp)!=0)
                    {
                        puts("mot de pass incorrect");
                            goto retry2;
                    }
                    else
                    goto MenuA;
                    }
                    
                } while (strcmp(mat,"q")!=0);
                
                
                
                    break;
                case 4:
                    
                    break;        
                default:
                goto retry;
                    break;
                }
        }        
        else if(connexion(u1)==2)
            {
                MenuE:
                int ch;
                char mat[20],rep;
                    afficherMenuapprenant();
                    ch=choice();
                    switch (ch)
                    {
                    case 1:
                        puts("Entrer votre matricule pour  confirmer votre presence");
                        marquerpresenceEtudiant( mat);
                        goto MenuE; 
                        
                    case 2:
                        
                        break;
                    case 3:
                        
                        break;
                    
                    default:
                    goto retry;
                        break;
                    }

            }
            else if(connexion(u1)==3)
                    puts("Vous ete bloque,Vous ne pouvez plus acceder a votre compte");
            else
            puts("mot de pass ou nom d'utilisateur incorrect"); 
        
        
        
        return 0;
    }
}