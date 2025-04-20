#pragma once

#include "list_1.h"

// Insertion tri�e
void ordered_insert(list_t* L, void* data, int (*cmp_ptrf)(void*, void*));

// Recherche avec suppression optionnelle
void find(list_t* L, void** ptrKey, int (*cmpFct)(void*, void*), void (*delFct)(void*));

// Suppression d�un �l�ment sp�cifique
void remove_item(list_t* L, void* data);
