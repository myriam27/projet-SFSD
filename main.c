#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000


typedef struct enregistrement*champ; // ALSO WHY POINTEUR ???
typedef struct enregistrement{
    char nom[15];
    int taille;
    char* donnee;
    int matricule;
    char obvs; // obvs c'est observasion on va procéder A = admis et D = doublons 
    champ svt;
    int sup; // si sup=0 on ne supprime pas sup=1 c'est le contraire ( puisque on va faire suppression logique ) 
}enregistrement;

typedef struct type* typebloc
typedef struct type{
    typebloc adr;
    champ Tab[max];
      }type;

// j'ai ajouté ça ( LUNA ) 
// there is diffrence between this two 
typedef struct typebloc buffer;
struct TypeBloc
{
    char enrg[max];
    int suivant;
};


typedef struct entete {
    int nbr-pre; //le num du premier bloc
    int nbr-ins; // le num de l'element qu'on veut insérer
    int nbr-sup; //le num de l'element  a suprimé
    int nbr-der; //le num du dernier bloc
    int pos-vide-lb; // la premiere position vide dans le dernier bloc
    int nb-bloc // nombre total des blocs
    unsigned long long last_key; // WHY THIS ????
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