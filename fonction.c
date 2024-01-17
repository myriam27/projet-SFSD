#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000
#define taille 20


typedef struct enregistrement* champ; 
typedef struct enregistrement{
    char nom[15];
    char size[taille]; //Un champ pour sauvegarder la taille de l'enregistrement
    char* donnee;
    char matricule[10];
    char obvs; // obvs c'est observasion on va procéder A = admis et D = doublons 
    champ svt;
    char sup; // si sup=0 on ne supprime pas sup=1 c'est le contraire ( puisque on va faire suppression logique ) 
    int uniqueCode;
}enregistrement;

typedef struct Typebloc{
    char enrg[max];
    int suivant;
}Typebloc;
typedef struct Typebloc Buffer;


typedef struct entete entete;
typedef struct entete{
    int nbrpre; // l'adress du premier bloc
    int nbrins; // le nbr d'elements qu'on veut insérer
    int nbrsup; //le nbr d'elements  supprime
    int nbrder; //l'adresse du dernier bloc
    int posvidelb; // la premiere position vide dans le dernier bloc //meriem: c'est quoi le but?
    int nb_bloc; // nombre total des blocs
}entete;
// la declaration du fichier 
typedef struct Fichier Fichier;
typedef struct Fichier{
    entete head; // champs de l'entete 
    FILE *file ;
} Fichier; 

int Entete(Fichier* fichier,int i)
{
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
void Aff_Entete( Fichier *fichier , int i,int valeur)
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

void Ouvrir(Fichier *f,char* nomf,char mode){
    if((mode=='A')||(mode=='a'))
           {f->file = fopen(nomf,"rb+"); //Ouvrir le fichier en mode lecture/ecriture
            fread(&(f->head),sizeof(entete),1,f->file); 
           }
    else{
         if((mode=='N')||(mode=='n')){
            
             f->file = fopen(nomf,"wb+");                       
             Aff_Entete(f,1,0);                        
             Aff_Entete(f,2,0);                         
             Aff_Entete(f,3,0);                        
             Aff_Entete(f,4,0);                         
             Aff_Entete(f,5,0);                      
             Aff_Entete(f,6,0);
             fwrite(&(f->head),sizeof(entete),1,f->file); //Sauvegarder l'entete dans le fichier
        }

         }
    }
/*void fermer_f(Fichier *f){
        rewind(*f);
        fclose(*f);
    }*/
    // new fucntion fermer 
    void fermer_f(Fichier*f)
    {
    fseek(f->file,0,SEEK_SET); //Positionne le curseur au début du fichier
    fwrite(&(f->head),sizeof(entete),1,f->file); //Sauvegarde l'entete
    fclose(f->file); //Ferme le fichier
    }
    //operations de lecture ecriture (meriem)

void LireDir(Fichier* fichier, int i, Buffer* buf)
{
    fseek(fichier->file,(sizeof(entete)+sizeof(Buffer)*(i-1)),SEEK_SET); //Positionner le curseur à l'adresse i
    fread(buf,sizeof(Buffer),1,fichier->file); //Lire le bloc
}

//Ecrire le bloc à l'adresse i
void EcrireDir(Fichier* fichier, int i, Buffer *buf)
{
    fseek(fichier->file,(sizeof(entete)+sizeof(Buffer)*(i-1)),SEEK_SET); //Positionner le curseur à l'adresse i
    fwrite(buf,sizeof(Buffer),1,fichier->file); //Ecrire le bloc
}

void AllocBloc(Fichier* fichier)
{
    Buffer* buf = malloc(sizeof(Buffer)); //Allouer de l'espace mémoire pour le buffer
    LireDir(fichier,Entete(fichier,5),buf); //Lire le dernier bloc de la liste
    buf->suivant = Entete(fichier,4) + 1; //Mettre à jour le champ suivant avec le nombre de blocs total de la liste + 1 (une nouvelle adresse)
    EcrireDir(fichier,Entete(fichier,5),buf); //Ecrire le dernier bloc
    strcpy(buf->enrg,""); //Initialiser le buffer à une chaine de caractères vide
    buf->suivant = -1; //Initialiser le champ suivant à -1 (NIL)
    EcrireDir(fichier,Entete(fichier,4) + 1,buf); //Ecrire le buffer à l'adresse (nombre de blocs total de la liste + 1)
    Aff_Entete(fichier,4,Entete(fichier,4)+1); //Incrémenter le nombre total de blocs de la liste
    Aff_Entete(fichier,5,Entete(fichier,4)); //Mettre à jour le champ qui correspond à l'adresse du dernier bloc de la liste
}
//Initialiser les enregistrements avec des séparateurs
void Initialisation(enregistrement* enrg)
{
    strcpy(enrg->matricule,"||||||||||");
    strcpy(enrg->nom,"|||||||||||||||");
    strcpy(enrg->obvs,"|");
    enrg->uniqueCode=0;
    enrg->size[0] = '0';
    for(int i=1;i<taille;i++)
        enrg->size[i] = '|';
    enrg->sup = 0;
}
//  recuperer le champs d'un enregistrement
void ChampRecup(Fichier* fichier,int n,Buffer* buf,int* i,int* j,char* donnee[])
{
    int k = 0;
    while(k<n)
    {
        if(buf->enrg[*j]!='|') // si le caractére n'est pas un separateur puisque on a initalisé les champs avec des separateurs
        {
            donnee[k] = buf->enrg[*j];
        }
        else 
        {
            donnee[k] = '\0';
        }
        (*j)+=1;
        k+=1;
    }
}

// cette function on va chercher le champs matricule
// et cette function vas retourner @ du bloc et sa position

int SearchLOVnonC(Fichier* fichier, char*nom_physique, int valeur, int* i,int* j,int* trouve )
{
    Buffer buffer ; // to read and write blocs 
     int stop ; // like a boolean variable when it equal to zero it's false 
     int sauvgardej, sauvgardei ; // pour sauvgarder i et j 
     char sup;
     int nb_taille;
     int matricule; //reference a matricule  
     Ouvrir(fichier,nom_physique,'A'); // Ouvrir le fichier en mode " ancien"
     *trouve =0;
     stop = 0; // for these two we initalise it to false
     *i=Entete(fichier , 1); // on a affecte a i l'adresse du premier bloc 
     *j=0;
     // on rappelle que i c'est l'adresse du bloc 
     // et j c'est la position du bloc
     //donc ici pour *i on la initaliser avec l'adress du premier bloc et pour j c'est la position du premier bloc 
      LireDir(fichier,*i,&buffer); // to read  the first bloc 
       // on va traiter le cas de si le fichier est vide 
       if ((*j>= Entete(fichier ,6)) && (*i>= Entete(fichier,5)))
       {
        stop =1; // true 
        return 0; // on n'a pas trouvé 
       }  
       while ((trouve ==0 )&& (stop==0)) // tant que on a pas trouver la valeur rechercher 
       {
        // on va sauvgarder l'adresse du bloc et sa position 
        sauvgardei = *i;
        sauvgardej = *j;
        ChampRecup(fichier,1,&buffer,i,j,&sup); // recupurer la valeur du champs efface pour savoir sa valeur est ce que c'est 1 ou bien c'est 0
        ChampRecup(fichier,sizeof(int),&buffer,i,j,&matricule); // pour savoir la valeur du matricule comme ça on peut la comparer avec la valeur entrée en parametre 
        // dans la function ChampsRecup on a un parametre n 
        // ce parametre c'est la taille de la variable efface c'est char donc c'est 1 et pour int on a utilisé la fonction sizeof
        if ( matricule== valeur ) // we found the value that we search 
        {
        // we will check if it wasn't deleted 
        if (sup ==0 )// false donc c'est pas supprimé
       {
        trouve=1;
        return 1; // we've found the value that we search about 
       }
       else // ça été supprimé 
       stop =1; // stop = true  
       *i=sauvgardei;
       *j=sauvgardej;
       return 0; // false
       } 
       else if (matricule >valeur) // no need to continue si la valeur rechercher est < a la valeur lue ( we didn't find matricule that we search about ) 
       {
        stop =1; // stop = true  
       *i=sauvgardei;
       *j=sauvgardej;
       return 0; //return false 
       }
       else if ((*j>= Entete(fichier ,6)) && (*i>= Entete(fichier,5))) // we reached the end of the file techinecally we didn't find the value 
       { 
        stop = 1;
        return 0;
       }
       (*j)+=1;
       (*i)+=1;
    
       }
       fermer_f(fichier);
}
void ChainePr(char chaine[], char cle[]) {
    char nom[15];
    char matricule[10];
    char obvs;
    scanf("%s",&nom);
    while (strlen(nom) < 15)         
    {
        strcat(nom, "@");
    }
   scanf("%s",&matricule);
   while (strlen(matricule) < 15)         
    {
        strcat(matricule, "@");
    }   
   scanf("%c",&obvs);                         

    
    sprintf(chaine, "%s%s%s%c", nom, cle, matricule, obvs); // concatenation des  champs
}
void inserer(Fichier* fichier, char cle[]){
     int trouv =0, i =1, j =0, h =1, rest;

     Buffer buff;
     char key[max];                // chaine a inserer
     char key1[max];  
       if(fichier!=NULL){

     if (Entete(fichier->file, 6) == 0) // cas fichier vide
    {
        LireDir(fichier, 1, &buff);                                     // on lit le premier bloc
        ChainePr(key, cle);                                                   // genere une chaine a inseret
        strcpy(buff.enrg, key);                                                // on l'affect au bloc
        Aff_Entete(fichier->file, 6,Entete(fichier->file, 6) + strlen(key)); 
        Aff_Entete(fichier->file, 4, strlen(key));                            // mise a jour de la derniere position
        EcrireDir(fichier->file, 1, &buff);
        printf("\ninsertion effectuee avec succes\n");
    }
     else
     {
        SearchLOVnonC(fichier->file,char* nomphysique,cle, &i, &j,&trouv); // on cherche la cle donnée

        if (trouv == 1) // si la cle est trouvé
        {
            LireDir(fichier->file, i, &buff); // on lit le bloc ou elle se trouve notre cle
            if (buff.enrg[j + 5] == '1')       // enregistrement supprimé
            {
                buff.enrg[j + 5] = '0';              // mise a jour du champ supprimer de l'enregistrement
                EcrireDir(fichier->file, i, &buff); // mise a jour du bloc
                printf("\ninsertion effectuee avec succes\n");
            }
            else // cle deja existant
            {
                printf("\ncle deja existant\n");
            }
        }
        else // cle non trouvé
        {
            ChainePr(key, cle);                                      // on genere notre chaine a inserer
            Aff_Entete(fichier->file, 6,Entete(fichier, 6) +strlen(key)); // mise a jour de nombre de caractere inseré

             LireDir(fichier->file, Entete(fichier->file, 6), &buff); // on lit notre bloc
                    
                        alloc_bloc(fichier->file);               // on alloue un nouveau bloc
                        buff.suivant = Entete(fichier->file, 3); // on chaine l'ancien baff avec le nouveau bloc alloué
                        ecriredir(*fichier, Entete(fichier->file, 6), &buff);      // on ecrire notre buff
                                
                    i++; // on incremente l'indice de parcour des bloc cette instrucion est equivalante a i=buff.suivant;
                    // i=buff.suivant;
                    liredir(fichier->file,  Entete(fichier->file, 6), &buff); // on lit le nouveau bloc

            aff_entete(*fichier, 4,(*fichier, 6) % max); // mise a jour de la postion libre dans le bloc de queue
            ecriredir(*fichier, i, &buff);                                // ecriture du dernier blloc
            printf("\ninsertion effectuee avec succes\n");
        }
     }
    }
      else{ 
        char* nomf;
        char mode;
        scanf("%s",&nomf);
        scanf("%c",&mode);       
        Ouvrire(fichier,nomf,mode);
        Aff_Entete(fichier,1,1);
        Aff_Entete(fichier,2,strlen(ChainePr));
        Aff_Entete(fichier,3,0);
        Aff_Entete(fichier,4,1);
        Buffer buf;
        sprintf(buf.enrg,"%s",ChainePr);
        buf.suivant=-1;
        EcrireDir(fichier,1,&buf);
        fermer_f(fichier);


    }
}


