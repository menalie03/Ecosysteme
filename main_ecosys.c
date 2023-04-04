#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
//float p_ch_dir=0.01;
//float p_reproduce_proie=0.4;
//float p_reproduce_predateur=0.5;
//int temps_repousse_herbe=-15;


int main(void) {
  /* A completer. Part 2:*/
  /* exercice 4, questions 2 et 4*/
  Animal *A=creer_animal (10,10,10.0);
  Animal *la=ajouter_en_tete_animal(la, A);
  bouger_animaux(la);
  reproduce(&la,1.0);
  //EX5 Q1
  int tab[SIZE_X][SIZE_Y];
  for (int i=0;i<SIZE_X;i++){
    for (int j=0;j<SIZE_Y;j++){
      tab[i][j]=0;
    }
  }
   /* exercice 6, question 2*/
    Animal **liste_proie=NULL;
    for (int i=0;i<20;i++){
      int x=(int)(rand()% SIZE_X);
      int y=(int)(rand()% SIZE_Y);
      float energie=rand()%10;
      ajouter_animal(x, y, energie, liste_proie);
    }
    for (int cpt=0;cpt<200;cpt++){
      afficher_ecosys(*liste_proie, NULL);
      rafraichir_monde(tab);
      rafraichir_proies(liste_proie,tab);
      if (liste_proie == NULL){
        break;
      }
    }
   /* exercice 7, question 3*/
   Animal **liste_predateur=NULL;
   for (int i=0;i<20;i++){
      int x=(int)(rand()% SIZE_X);
      int y=(int)(rand()% SIZE_Y);
      float energie=rand()%10;
      ajouter_animal(x, y, energie, liste_predateur);
    }
    for (int cpt=0;cpt<200;cpt++){
      afficher_ecosys(*liste_proie,*liste_predateur);
      rafraichir_monde(tab);
      rafraichir_proies(liste_proie,tab);
      rafraichir_predateurs(liste_predateur,liste_proie);
      if (liste_proie == NULL || liste_predateur == NULL){
        break;
      }
    }
    liberer_liste_animaux(*liste_predateur);
    liberer_liste_animaux(*liste_proie);

   /* exercice 8, question 1
   */

  return 0;
}

