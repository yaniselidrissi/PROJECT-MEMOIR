#pragma once
#include <stdbool.h>
#include "list.h"
#define UNDEF -2


/** Des redondances possibles avec d'autres TAs ! */
typedef struct {
  char * title;                 // Nom de la tâche
  double life;                  // Durée de la tâche
  int input_degree;             // Son degré de dépendance
  int output_degree;            // Les tâches qui en dépendent
  int rank;                     // Rang de la tâche
  int dyn_input_degree;         // Facilité de prog
  list_t * precedence;   // Les tâches précédentes
  list_t * posteriority; // Les tâches ultérieures
  double au_plus_tot;           // Date au plus tôt
  double au_plus_tard;          // Date au plus tard
  double marge_totale;          // Marge totale
  double marge_libre;           // Marge libre
  bool critique;                // Une tâche critique ?
} job_t;
