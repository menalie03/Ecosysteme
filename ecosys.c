#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;


/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(x>=0 && y>=0 && y<SIZE_Y && x<SIZE_X);
  Animal *A;
  A=creer_animal(x,y,energie);
  A=ajouter_en_tete_animal(*liste_animal,A);
  *liste_animal=A;  //case du tableau pointe vers A (si on mets 2étoiles c le 1er élement de la case qui pointe vers A)
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  if (*liste==animal){ //cas où la tête est à supprimer
    (*liste)=(*liste)->suivant;
    free(animal);
  }
  else{ 
    while ((*liste)->suivant !=NULL){
      if ((*liste)->suivant==animal){
        (*liste)->suivant=animal->suivant; //le suivant de liste se relie au suivant de son suivant (=animal) 
        free(animal); 
      }else{
        (*liste)=(*liste)->suivant;
      }
    }
  }
  return ;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal *pA;
  while (liste){
    pA=liste;
    liste=liste->suivant;
    free(pA);
  }
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_pro, Animal *liste_pre) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred=0,nbproie=0;

  /* on initialise le tableau */
  for (i=0;i<SIZE_X;i++){
    for (j=0;j<SIZE_Y;j++){
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  Animal*liste_proie=liste_pro;
  while (liste_proie){
    ecosys[liste_proie->x][liste_proie->y]='*';
    liste_proie=liste_proie->suivant;
    nbproie++;
  }


  /* on ajoute les predateurs */
  Animal *liste_predateur=liste_pre;
  while (liste_predateur){
    nbpred++;
    int a=liste_predateur->x, b=liste_predateur->y;
    if (ecosys[a][b]=='*'){
      ecosys[a][b]='@';
    }else{
      ecosys[a][b]='O';
    }
    liste_predateur=liste_predateur->suivant;
  }

  /* on affiche le tableau */
  for (int bord=0;bord<SIZE_X;bord++){
    printf("_");
  }
  printf("\n");
  for (int i=0;i<SIZE_X;i++){
    printf("| ");
    for (int j=0;j<SIZE_Y;j++){
      printf("%c   ",ecosys[i][j]);
    } 
    printf("|\n");
  }
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *La) {
  Animal *la=La;
  while (la){
  	assert(((la->x)>=0 && (la->x)<SIZE_X) && ((la->y)>=0 && (la->y)<SIZE_Y));
		if (p_ch_dir>(rand()%RAND_MAX)){ 
			if (la->x!=0 && la->x!=SIZE_X && la->y!=0 && la->y!=SIZE_Y){ //cas simple où x,y sont pas aux bords 
				la->x+=((-1)*la->dir[0]);
				la->y+=((-1)*la->dir[1]);
			}
			else if((la->x==0 && la->dir[0]!=1) ||(la->x==(SIZE_X-1) && la->dir[0]!=-1)){
				la->x+=((-1)*la->dir[0]);
			}
			else if((la->y==(SIZE_Y-1) && la->dir[1]!=-1)||(la->y==0 && la->dir[0]!=1)){
				la->y+=((-1)*la->dir[1]);
			}
		}
	la=la->suivant;
  }
}	


/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   Animal **liste=liste_animal;
   while (*liste){
	  float p=(float)(rand()%RAND_MAX);
	  if (p<p_reproduce){
		  Animal *ani=creer_animal((*liste)->x,(*liste)->y,((*liste)->energie)/2);
		  (*liste)->energie/=2;
		  (*liste)=ajouter_en_tete_animal(*liste,ani);
	    (*liste)=(*liste)->suivant;
	  }
	  (*liste)=(*liste)->suivant;
  }
  free(*liste);
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie);
  Animal **L=liste_proie, **Lnettoyage=liste_proie;
  while(*L){
    (*L)->energie-=1.0;
    if (monde[(*L)->x][(*L)->y]>=0){
      (*L)->energie+=monde[(*L)->x][(*L)->y];
      monde[(*L)->x][(*L)->y]=temps_repousse_herbe;
    }
    (*L)=(*L)->suivant;
  }
  free(*L);
  while (*Lnettoyage){ //débarras des proies morts sans energies
    if ((*Lnettoyage)->energie<0){
      enlever_animal(liste_proie, *Lnettoyage);
    }
    (*Lnettoyage)=(*Lnettoyage)->suivant;
  }
  free(*Lnettoyage);
  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *liste_proie, int dx, int dy) {
    while (liste_proie){
      if (liste_proie->x==dx && liste_proie->y==dy){
        return liste_proie;
      }
    }
    return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur);
  Animal **L=liste_predateur, **Lnettoyage=liste_predateur;
  while(*L){
    (*L)->energie-=1.0;
    Animal *exists=animal_en_XY(*liste_proie,(*L)->x,(*L)->y);
    if (exists!=NULL){ //si une proie existe à la du predateur *L
      (*L)->energie+=exists->energie;
      enlever_animal(liste_proie, exists);
    }
    (*L)=(*L)->suivant;
    free(exists);
  }
  while(*Lnettoyage){ //débarras des predateurs morts, sans energie
    if ((*Lnettoyage)->energie<0){
      enlever_animal(liste_predateur,(*Lnettoyage));
    }
    (*Lnettoyage)=(*Lnettoyage)->suivant;
  }
  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for (int i=0;i<SIZE_X;i++){
    for (int j=0;j<SIZE_Y;j++){
      monde[i][j]+=1;
    }
  }
}

