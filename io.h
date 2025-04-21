#pragma once

#include "list.h"
#include "job.h"

// Affiche tous les éléments d'une liste en utilisant une fonction de callback
void view_list(list_t* L, void (*ptrf)(void*));

// Trie la liste avec un tri rapide (quicksort) et une fonction de comparaison
void quick_sort(list_t* L, int (*cmpFct)(void*, void*));

// Lecture d’un graphe de dépendances depuis un fichier .dta
list_t* read_graph(char* path);
