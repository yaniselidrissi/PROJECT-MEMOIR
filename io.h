#pragma once

#include "list.h"
#include "job.h"

void view_list(list_t* L, void (*ptrf)(void*));
void quick_sort(list_t* L, int (*cmpFct)(void*, void*));
int iDegreeJobCmp(void* A, void* B);
list_t* read_graph(char* path);
