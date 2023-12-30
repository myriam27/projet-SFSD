#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000


typedef struct enregistrement*champ;
typedef struct enregistrement{
    char nom[15];
    int taille;
    char* donnee;
    champ svt;
}enregistrement;

typedef struct type* typebloc
typedef struct type{
    typebloc adr;
    champ Tab[max];
      }type;

typedef struct typebloc buffer;

typedef struct entete{
    int nbr-pre; //le num du premier bloc
    int nbr-ins; // le num de l'element insereé
    int nbr-sup; //le num de l'element suprimé
    int nbr-der; //le num du dernier bloc
    int pos-vide-lb; // la premiere position vide dans le dernier bloc
    unsigned long long last_key;
}
void ouvrir_f(FILE* f,char* nomf,char mode){
    if((mode=='A')||(mode=='a'))
        *f=fopen(nomf,"rb+");
    else{
         if((mode=='N')||(mode=='n')){
            
             *f = fopen(nomF,"wb+");                       
             Aff_Entete_F(*f,1,NULL);                        
             Aff_Entete_F(*f,2,0);                         
             Aff_Entete_F(*f,3,0);                        
             Aff_Entete_F(*f,4,NULL);                         
             Aff_Entete_F(*f,5,0);                         
             unsigned long long initial_key = 0;
             Aff_Entete_F(*f,6,initial_key);
        }

         }
    }
    void fermer-f(FILE* f,){
        rewind(*f);
        fclose(*f);
    }

int main(){

}