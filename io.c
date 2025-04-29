#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "job.h"
#include "io.h"

// Affichage des éléments d'une liste
void view_list(list_t* L, void (*ptrf)(void*)) {
    for (list_elm_t* E = get_head(L); E; E = get_suc(E)) {
        ptrf(get_data(E));
    }
}

// Tri rapide (quicksort) d'une liste
void quick_sort(list_t* L, int (*cmpFct)(void*, void*)) {
    if (!L || L->numelm <= 1) return;

    list_elm_t* pivot = get_head(L);
    list_t* smaller = new_list();
    list_t* greater = new_list();

    for (list_elm_t* E = get_suc(pivot); E; E = get_suc(E)) {
        void* data = get_data(E);
        if (cmpFct(data, pivot->data) < 0)
            queue(smaller, data);
        else
            queue(greater, data);
    }

    quick_sort(smaller, cmpFct);
    quick_sort(greater, cmpFct);

    clean(L);
    for (list_elm_t* E = get_head(smaller); E; E = get_suc(E))
        queue(L, get_data(E));
    queue(L, pivot->data);
    for (list_elm_t* E = get_head(greater); E; E = get_suc(E))
        queue(L, get_data(E));

    del_list(&smaller, NULL);
    del_list(&greater, NULL);
}

// Lecture d’un graphe depuis un fichier au format “Nom Durée [Liste de noms prédécesseurs] NIL”
list_t* read_graph(char* path) {
    FILE* f = fopen(path, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    list_t* G = new_list();
    char name[128], token[128];
    double life;

    // Pour chaque ligne jusqu'à EOF
    while (fscanf(f, "%127s %lf", name, &life) == 2) {
        // 1) Création du job
        job_t* J = new_job(name);
        set_job_life(J, life);
        queue(G, J);

        // 2) Lecture de la liste des prédécesseurs, jusqu’à "NIL"
        while (fscanf(f, "%127s", token) == 1 && strcmp(token, "NIL") != 0) {
            // Recherche du job prédécesseur par nom
            job_t* pred = NULL;
            for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
                job_t* tmp = get_data(E);
                if (strcmp(get_job_title(tmp), token) == 0) {
                    pred = tmp;
                    break;
                }
            }
            if (pred) {
                // Ajout de l’arête pred → J
                ordered_insert(pred->posteriority, J, &titleJobCmp);
                ordered_insert(J->precedence, pred, &titleJobCmp);
                incr_job_oDegree(pred);
                incr_job_iDegree(J);
            }
        }
    }

    fclose(f);
    return G;
}
