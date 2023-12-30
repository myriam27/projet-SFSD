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

int main(){

}