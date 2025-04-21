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
        if (cmpFct(data, pivot->data) < 0) {
            queue(smaller, data);
        }
        else {
            queue(greater, data);
        }
    }

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

    del_list(&smaller, NULL);
    del_list(&greater, NULL);
}  // Fin correcte de quick_sort

// Lecture d'un fichier .dta et construction du graphe
list_t* read_graph(char* path) {
    FILE* f = fopen(path, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    int nb_jobs;
    fscanf(f, "%d\n", &nb_jobs);

    list_t* G = new_list();
    job_t** jobs = malloc(nb_jobs * sizeof(job_t*));

    // Lecture des jobs
    for (int i = 0; i < nb_jobs; i++) {
        char name[100];
        double life;
        fscanf(f, "%s %lf\n", name, &life);
        jobs[i] = new_job(name);
        set_job_life(jobs[i], life);
        queue(G, jobs[i]);
    }

    // Lecture des dépendances
    int pred, succ;
    while (fscanf(f, "%d %d", &pred, &succ) == 2) {
        job_t* J1 = jobs[pred];
        job_t* J2 = jobs[succ];
        ordered_insert(J1->posteriority, J2, &titleJobCmp);
        ordered_insert(J2->precedence, J1, &titleJobCmp);
        incr_job_oDegree(J1);
        incr_job_iDegree(J2);
    }

    free(jobs);
    fclose(f);
    return G;
}
