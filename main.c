#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000

//essai de cration enregistrement
<<<<<<< HEAD
typedef struct CHAMP*champ; 
typedef struct CHAMP{       
    char* nom;                    
    char* donnee;                     
    champ svt;
}CHAMP;
void ajouter(champ tete,char nom[],char donnee[]){
    champ nouv,p;
    nouv=(champ)malloc(sizeof(champ));// allocation d un champ
    snprintf(nouv->nom,sizeof(nouv->nom),"%s",nom);// ecririt une chaine
    nouv->donnee=(char*)malloc(strlen(donnee)+1);// alocation d un espace memoire
    strcpy(nouv->donnee,donnee);
     if (tete==NULL){
        nouv->svt=tete;
        tete=nouv;
    }
    else{
            p=tete;
        while(p->svt!=NULL){
            p=p->svt;
        }
        nouv->svt=NULL;
        p->svt=nouv;
    }
    }
 #define taille 20


typedef struct enregistrement*champ; 
typedef struct enregistrement{
    char nom[15];
    char size[taille]; //Un champ pour sauvegarder la taille de l'enregistrement
    int matricule;
    char obvs; // obvs c'est observasion on va procéder A = admis et D = doublons 
    champ svt;
    char sup; // si sup=0 on ne supprime pas sup=1 c'est le contraire ( puisque on va faire suppression logique ) 
}enregistrement;

typedef struct Typebloc Buffer;
Typedef struct TypeBloc{
    char enrg[max];
    int suivant;
}Typebloc;


typedef struct entete{
    int nbrpre; // l'adress du premier bloc
    int nbrins; // le nbr d'elements qu'on veut insérer
    int nbrsup; //le nbr d'elements  supprime
    int nbrder; //l'adresse du dernier bloc
    int posvidelb; // la premiere position vide dans le dernier bloc //meriem: c'est quoi le but?
    int nb_bloc; // nombre total des blocs
}entete;

// la declaration du fichier 
typedef struct Fichier{
    entete head; // champs de l'entete 
    FILE *file;
}Fichier;

int Entete(Fichier* fichier,int i){
    switch (i)
    {
    case 1 : return fichier->head.nbrpre;
    case 2 : return fichier->head.nbrins;
    case 3 : return fichier->head.nbrsup;
    case 4:  return fichier->head.nbrder;
    case 5: return fichier->head.nb_bloc;
    case 6: return fichier->head.posvidelb;
    default:
        printf(" ERROR !! ");
        return 0;
    }

}
void Aff_Entete( Fichier *fichier , int i, int valeur)
{
    switch (i)
    {
        case 1: {
            fichier->head.nbrpre = valeur;
            break;
        }
        case 2: {
            fichier->head.nbrins = valeur;
            break;
        }
        case 3: {
            fichier->head.nbrsup = valeur;
            break;
        }
        case 4: {
            fichier->head.nbrder= valeur;
            break;
        }
        case 5: {
            fichier->head.nb_bloc = valeur;
            break;
        }
        case 6: {
            fichier->head.posvidelb = valeur;
            break;
        }
        default: {
            printf(" ERROR !!\n  ");
            break;
        }
    }
}

void ouvrir_f(Fichier* f,char* nomf,char mode){
    if((mode=='A')||(mode=='a'))
        f->file =fopen(nomf,"rb+");
    else{
         if((mode=='N')||(mode=='n')){
            
             f->file = fopen(nomf,"wb+");                       
             Aff_Entete(f,1,-1);                        
             Aff_Entete(f,2,0);                         
             Aff_Entete(f,3,0);                        
             Aff_Entete(f,4,-1);                         
             Aff_Entete(f,5,0);                         
             unsigned long long initial_key = 0;
             Aff_Entete(f,6,initial_key);
        }

         }
    }
void fermer_f(Fichier* f){
        rewind(f->file);
        fwrite(&(f->head),sizeof(Entete),1,f->file);//sauvgarder l'entete
        rewind(f->file);
         fclose(f->file);
    }
    //operations de lecture ecriture (meriem)

//lire le bloc
void LireDir(Fichier* f, int i, Buffer* buf)
{
    fseek(f->file,(sizeof(f->head)+sizeof(buf)*(i-1)),SEEK_SET); //Positionner le curseur à l'adresse i
    fread(buf,sizeof(buf),1,f->file); //Lire le bloc
}

//Ecrire le bloc à l'adresse i
void EcrireDir(Fichier* f, int i, Buffer* buf)
{
    fseek(f->file,(sizeof(f->head)+sizeof(buf)*(i-1)),SEEK_SET); //Positionner le curseur à l'adresse i
    fwrite(buf,sizeof(buf),1,f->file); //Ecrire le bloc
}



    int main() {
        //creation enregistrement
    champ tete = NULL;
    char nomChamp[50];
    char valeurChamp[100];
    int cpt=0;

    //entrer des champs
    printf("Entrez le nom du champ (ou 'exit' pour quitter) : ");
    while (scanf("%s", nomChamp) == 1 && strcmp(nomChamp, "exit") != 0) {
        printf("Entrez la valeur du champ : ");
        scanf("%s", valeurChamp);
       cpt++;
       ajouter(tete, nomChamp, valeurChamp);

        // entrer le prochain champ
        printf("Entrez le nom du champ (ou 'exit' pour quitter) : ");
    }
    }