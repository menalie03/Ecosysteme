#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20





int main(void) {

  /* A Completer. */
  /* Part 1, exercice 5, question 3 */
  Animal *Liste_proie;
  Animal *Liste_predateur;
  for (int i=0;i<(rand()%(NB_PROIES+1));i++){
    ajouter_animal((rand()%(SIZE_X+1)),(rand()%(SIZE_X+1)),rand(),&Liste_proie);
  }
  for (int i=0;i<(rand()%(NB_PREDATEURS+1));i++){
    ajouter_animal((rand()%(SIZE_X+1)),(rand()%(SIZE_X+1)),rand(),&Liste_predateur);
  }
  assert(compte_animal_rec(Liste_proie));
  assert(compte_animal_rec(Liste_predateur));

  afficher_ecosys(Liste_proie, Liste_predateur);
  Liste_predateur=liberer_liste_animaux(Liste_predateur);
  Liste_proie=liberer_liste_animaux(Liste_proie);
  return 0;
}
