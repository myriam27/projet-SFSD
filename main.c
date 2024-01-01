#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000


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
 
typedef struct type* typebloc;
typedef struct type{
    typebloc adr;   // ici nrmlm les blocs sont chainee psq le fichier est de type liste donc on le declare 
    champ Tab[max]; // de type pointeur
      }type;

typedef struct typebloc buffer;

typedef struct entete{
    int nbrpre; //le num du premier bloc
    int nbrins; // le nombre de l'element insereé
    int nbrsup; //le nombre d'element suprimé
    int nbrder; //le num du dernier bloc
    int posvidelb; // la premiere position vide dans le dernier bloc
    unsigned long long last_key; 
}entete;

void ouvrirf(FILE* f,char* nomf,char mode){//j ai un probleme ici et je n ai pa su le regler     
    if((mode=='A')||(mode=='a'))
        f=fopen(nomf,"rb+");
    else{
         if((mode=='N')||(mode=='n')){
            
             f = fopen(nomf,"wb+");                       
             Aff_Entete(*f,1,-1);       // iici aussi                
             Aff_Entete(*f,2,0);                         
             Aff_Entete(*f,3,0);                        
             Aff_Entete(*f,4,-1);                         
             Aff_Entete(f,5,0);                         
             unsigned long long initial_key = 0;
             Aff_Entete(f,6,initial_key);
        }

         }
    }
    void fermerf(FILE* f){
        rewind(f);
        fclose(f);
    }
   void Aff_Entete(FILE* f, int p, int i){
    entete e;
    if(f!=(NULL  )){
            rewind(f);
            fread(&e,sizeof(entete),1,f); // pour lire le bloc 
            if(p==1){ e.nbrpre = i ;} //  Le numero du premier bloc 
            if(p==2){ e.nbrins =i ;} //  Le nombre d'elements inseres
            if(p==3){ e.nbrsup =i ;} //  Le nombre d'elements supprimes 
            if(p==4){ e.nbrder =i ;} //  Le numero du dernier bloc
            if(p==5){ e.posvidelb = i;} //  La premiere position vide dans le dernier bloc
            if(p==6){ e.last_key = i;}
            if ((p < 1) || (p > 6)) {
                printf("\n");
                printf("numero de caracteristique n'existe pas! \n");
            }
            rewind(f);
            fwrite(&e,sizeof(entete),1,f);
        }
}
int Entete_F(FILE* f,int p){
    entete e;
    if(f!=NULL){
            rewind(f);
            fread(&e,sizeof(e),1,f);
            if(p==1){return e.nbrpre;} // | Le numero du premier bloc
            if(p==2){return e.nbrins;} // | Le nombre d'elements inseres
            if(p==3){return e.nbrsup;} // | Le nombre d'elements supprimes logiquement
            if(p==4){return e.nbrder;} // | Le numero du dernier bloc
            if(p==5){return e.posvidelb;} // | la premiere position vide dans le dernier bloc
            if(p==6){return e.last_key;}
            if ((p < 1) || (p > 6)) {
                printf("\n");
                printf("numero de caracteristique n'existe pas! \n");
            }
        }
}

void lirebloc(FILE* f,int i,typebloc* buff){
    entete e;
    fseek(f,sizeof(e)+(i-1)*sizeof(typebloc),SEEK_SET);
    fread(&(*buff),sizeof(typebloc),1,f);
}
void ecrirebloc(FILE* f,int i,typebloc buff){
    entete e;
     fseek(f,sizeof(e)+(i-1)*sizeof(typebloc),SEEK_SET);
    fwrite(&buff,sizeof(typebloc),1,f);
}

 void AllocBloc(FILE* fichier){

    buffer* buf = (buffer)malloc(sizeof(buffer)); //Allouer de l'espace mémoire pour le buffer//ici je ne sais pas prq il y a une erreur
    lirebloc(fichier,Entete_F(fichier,5),buf); //Lire le dernier bloc de la liste
    buf->svt = Entete_F(fichier,4) + 1; //Mettre à jour le champ suivant avec le nombre de blocs total de la liste + 1 (une nouvelle adresse)
    ecrirebloc(fichier,Entete_F(fichier,5),buf); //Ecrire le dernier bloc
    strcpy(buf->tab,""); //Initialiser le buffer à une chaine de caractères vide
    buf->svt= -1; //Initialiser le champ suivant à -1 (NIL)
    ecrirebloc(fichier,Entete_F(fichier,4) + 1,buf); //Ecrire le buffer à l'adresse (nombre de blocs total de la liste + 1)
    Aff_Entete(fichier,4,Entete_F(fichier,4)+1); //Incrémenter le nombre total de blocs de la liste
    Aff_Entete(fichier,5,Entete_F(fichier,4)); //Mettre à jour le champ qui correspond à l'adresse du dernier bloc de la liste
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

    // Afficher les champs
    champ cree;
      cree = tete;
    while (cree != NULL) {// a partir d ici le programme ne fontionne pas 
        printf("Nom: %s, Valeur: %s\n", cree->nom, cree->donnee);
        cree = cree->svt;
    }

    // Libération de la mémoire
    champ temp;
    while (tete != NULL) {
        temp = tete;
        tete = tete->svt;
        free(temp->donnee);
        free(temp);
    }

    return 0;
}
