#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "job.h"
#include "io.h"

// Déclaration anticipée
void partition(list_t* L, list_elm_t* pivot, list_t* val_inf_pivot, list_t* val_sup_pivot, int (*cmpFct)(void*, void*));

// Affichage de la liste
void view_list(list_t* L, void (*ptrf)(void*)) {
    for (list_elm_t* E = get_head(L); E; E = get_suc(E)) {
        ptrf(get_data(E));
    }
}

void quick_sort(list_t* L, int (*cmpFct)(void*, void*)) {
    if (L->numelm <= 1) return;

    list_elm_t* pivot = L->head;
    list_t* smaller = new_list();
    list_t* greater = new_list();

    partition(L, pivot, smaller, greater, cmpFct);
    quick_sort(smaller, cmpFct);
    quick_sort(greater, cmpFct);

    clean(L);
    for (list_elm_t* E = get_head(smaller); E; E = get_suc(E)) {
        queue(L, get_data(E));
    }
    queue(L, pivot->data);
    for (list_elm_t* E = get_head(greater); E; E = get_suc(E)) {
        queue(L, get_data(E));
    }

    set_suc(pivot, greater->head);
    del_list(&smaller, NULL);
    del_list(&greater, NULL);
}

void partition(list_t* L, list_elm_t* pivot, list_t* val_inf_pivot, list_t* val_sup_pivot, int (*cmpFct)(void*, void*)) {
    for (list_elm_t* E = get_suc(pivot); E; E = get_suc(E)) {
        void* data = get_data(E);
        if (cmpFct(data, pivot->data) < 0) {
            queue(val_inf_pivot, data);
        }
        else {
            queue(val_sup_pivot, data);
        }
    }
}

int titleJobCmp(void* A, void* B) {
    job_t* J1 = A;
    job_t* J2 = B;
    return strcmp(get_job_title(J1), get_job_title(J2));
}
