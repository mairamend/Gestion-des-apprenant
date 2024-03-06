#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
int main()
{
   int choix;
    User u1=SaisiIdentifiant();
    if (connexion(u1)==1)
    {
            afficherMenuadmin();
            choix=choice();
            switch (choix)
            {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;        
            default:
                break;
            }
    }        
    else if(connexion(u1)==2)
        {
           
                afficherMenuapprenant();
        }
        else if(connexion(u1)==3)
                puts("Vous ete bloque,Vous ne pouvez plus acceder a votre compte");
            
    
        
        
        //puts("Connexion reussi");
    else
        puts("mot de pass ou nom d'utilisateur incorrect"); 
    
    
    
    return 0;
}