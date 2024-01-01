#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000


typedef struct enregistrement*champ; //alors j ai declarer l enregistrement de cette maniere psq le prof nous a demander
typedef struct enregistrement{       //de laisser l utilisateur definir le nombre de champs qu il veut
    char nom[15];                     // de cette maniere lors de lexecution il definir le nbr de champs puis
    int taille;                        // grace a l allocation il cree le nombre de champs qu il veut et de la taille 
    char* donnee;                     //qu'il veut mais si vous voulais qu on definisse le nombre de champs on change   
    champ svt;
}enregistrement;

typedef struct type* typebloc
typedef struct type{
    typebloc adr;   // ici nrmlm les blocs sont chainee psq le fichier est de type liste donc on le declare 
    champ Tab[max]; // de type pointeur
      }type;

typedef struct typebloc buffer;

typedef struct entete{
    int nbr-pre; //le num du premier bloc
    int nbr-ins; // le nombre de l'element insereé
    int nbr-sup; //le nombre d'element suprimé
    int nbr-der; //le num du dernier bloc
    int pos-vide-lb; // la premiere position vide dans le dernier bloc
    unsigned long long last_key; //c est un type qui peut stocker 64bits nrmlm on aura besoin de lui sinon on l enleve on verra
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
    void Aff_Entete_F(FILE *f, int p, int i){
    entete e;
    if(f!=NULL){
            rewind(f);
            fread(&e,sizeof(entete),1,f); // pour lire le bloc 
            if(p==1){ e.nbr_pre = i ;} // | Le numero du premier bloc 
            if(p==2){ e.nbr_ins =i ;} // | Le nombre d'elements inseres
            if(p==3){ e.nbr_sup =i ;} // | Le nombre d'elements supprimes 
            if(p==4){ e.nbr_der =i ;} // | Le numero du dernier bloc
            if(p==5){ e.pos_vide_db = i;} // | La premiere position vide dans le dernier bloc
            if(p==6){ e.last_key = i;}
            if ((p < 1) || (p > 6)) {
                printf("\nnumero de caracteristique n'existe pas!! \n");
            }
            rewind(f);
            fwrite(&e,sizeof(entete),1,f);
        }
}


int main(){

}