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
typedef struct Typebloc buffer; //(meriem) j'ai change de typebloc a Typebloc
struct TypeBloc 
{
    char enrg[max];
    int suivant;
};

typedef struct entete entete;
struct entete
{
    int nbrpre; //le num du premier bloc
    int nbrins; // le num de l'element qu'on veut insérer
    int nbrsup; //le num de l'element  a suprimé
    int nbrder; //le num du dernier bloc
    int posvidelb; // la premiere position vide dans le dernier bloc
    int nb_bloc // nombre total des blocs
    unsigned long long last_key; // WHY THIS ????
};
// la declaration du fichier 
typedef struct Fichier Fichier;
struct Fichier
{
    entete head; // champs de l'entete 
    FILE *file 
};

int Entete(int i, Fichier* fichier  )
{
    switch (i)
    {
    case 1 : return fichier->entete.nbrpre;
    case 2 : return fichier->entete.nbins;
    case 3 : return fichier->entete.nbrsup;
    case 4:  return fichier->entete.nbrder;
    case 5: return fichier->entete.nb_bloc;
    case 6: return fichier->entete.posvidelb;
    default:
        printf(" ERROR !! ");
        return 0;
    }

}
void Aff_Entete( Fichier *fichier , int i,int valeur)
{
    switch (i)
    {
        case 1: {
            fichier->entete.nbrpre = valeur;
            break;
        }
        case 2: {
            fichier->entete.nbins = valeur;
            break;
        }
        case 3: {
            fichier->entete.nbsup = valeur;
            break;
        }
        case 4: {
            fichier->entete.nbrder= valeur;
            break;
        }
        case 5: {
            fichier->entete.nb_bloc = valeur;
            break;
        }
        case 6: {
            fichier->entete.posvidelb = valeur;
            break;
        }
        default {
            printf(" ERROR !!\n  ");
            break;
        }
    }
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

//operations de lecture ecriture (meriem)

void Liredir(FILE *f, int i, buffer* Buf){
    entete e;
    fseek(f, sizeof(e)+(i-1)*sizeof(Typebloc),SEEK_SET);
    fread(&(*Buf),sizeof(Typebloc),1,f);
}

void Ecriredir(FILE **f, int i, Typebloc Buf){
    entete e;
    fseek(*f, sizeof(e)+(i-1)*sizeof(Typebloc),SEEK_SET);
    fwrite(&Buf,sizeof(Typebloc),1,*f);
}


int main(){

}
