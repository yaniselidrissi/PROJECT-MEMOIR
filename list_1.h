#pragma once

#include <stdbool.h>

typedef struct list_elm {
    void* data;
    struct list_elm* pred;
    struct list_elm* suc;
} list_elm_t;

typedef struct {
    list_elm_t* head;
    list_elm_t* tail;
    int numelm;
} list_t;

// Fonctions de base
list_t* new_list();
void del_list(list_t** ptrL, void (*ptrf)(void*));
void clean(list_t* L);
bool is_empty(list_t* L);

// Accès
list_elm_t* get_head(list_t* L);
list_elm_t* get_tail(list_t* L);
list_elm_t* get_suc(list_elm_t* E);
list_elm_t* get_pred(list_elm_t* E);
void* get_data(list_elm_t* E);

// File
void* take_out(list_t* L);
void queue(list_t* L, void* data);

// Ajouté ici
void set_suc(list_elm_t* E, list_elm_t* suc);
