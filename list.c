#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

// Crée une nouvelle liste vide
list_t* new_list() {
    list_t* L = malloc(sizeof(list_t));
    assert(L);
    L->head = L->tail = NULL;
    L->numelm = 0;
    return L;
}

// Supprime la liste et libère ses éléments
// ptrf est appelé sur chaque donnée si non NULL
void del_list(list_t** ptrL, void (*ptrf)(void*)) {
    assert(ptrL && *ptrL);
    list_elm_t* E = (*ptrL)->head;
    while (E) {
        list_elm_t* next = E->suc;
        if (ptrf) ptrf(E->data);
        free(E);
        E = next;
    }
    free(*ptrL);
    *ptrL = NULL;
}

// Vide la liste mais conserve la structure
void clean(list_t* L) {
    assert(L);
    list_elm_t* E = L->head;
    while (E) {
        list_elm_t* next = E->suc;
        free(E);
        E = next;
    }
    L->head = L->tail = NULL;
    L->numelm = 0;
}

bool is_empty(list_t* L) {
    return (L->numelm == 0);
}

// Accès
list_elm_t* get_head(list_t* L) { return L->head; }
list_elm_t* get_tail(list_t* L) { return L->tail; }
list_elm_t* get_suc(list_elm_t* E) { return E->suc; }
list_elm_t* get_pred(list_elm_t* E) { return E->pred; }
void* get_data(list_elm_t* E) { return E->data; }

// Insertion ordonnée
void ordered_insert(list_t* L, void* data, int (*cmp_ptrf)(void*, void*)) {
    assert(L && cmp_ptrf);
    list_elm_t* new_elm = malloc(sizeof(list_elm_t));
    assert(new_elm);
    new_elm->data = data;
    new_elm->pred = new_elm->suc = NULL;

    if (is_empty(L)) {
        L->head = L->tail = new_elm;
    }
    else {
        list_elm_t* E = L->head;
        while (E && cmp_ptrf(E->data, data) < 0) {
            E = E->suc;
        }
        if (!E) {
            new_elm->pred = L->tail;
            L->tail->suc = new_elm;
            L->tail = new_elm;
        }
        else if (E == L->head) {
            new_elm->suc = L->head;
            L->head->pred = new_elm;
            L->head = new_elm;
        }
        else {
            new_elm->suc = E;
            new_elm->pred = E->pred;
            E->pred->suc = new_elm;
            E->pred = new_elm;
        }
    }
    L->numelm++;
}

// Retire et retourne l'élément en tête (FIFO)
void* take_out(list_t* L) {
    if (is_empty(L)) return NULL;
    list_elm_t* E = L->head;
    void* data = E->data;
    L->head = E->suc;
    if (L->head) L->head->pred = NULL;
    else L->tail = NULL;
    free(E);
    L->numelm--;
    return data;
}

// Suppression d'un élément spécifique
void remove_item(list_t* L, void* data) {
    assert(L);
    list_elm_t* E = L->head;
    while (E && E->data != data) {
        E = E->suc;
    }
    if (!E) return;
    if (E->pred) E->pred->suc = E->suc;
    else L->head = E->suc;
    if (E->suc) E->suc->pred = E->pred;
    else L->tail = E->pred;
    free(E);
    L->numelm--;
}

// Ajoute en fin de liste (queue)
void queue(list_t* L, void* data) {
    assert(L);
    list_elm_t* new_elm = malloc(sizeof(list_elm_t));
    assert(new_elm);
    new_elm->data = data;
    new_elm->suc = NULL;
    new_elm->pred = L->tail;
    if (is_empty(L)) {
        L->head = L->tail = new_elm;
    }
    else {
        L->tail->suc = new_elm;
        L->tail = new_elm;
    }
    L->numelm++;
}
