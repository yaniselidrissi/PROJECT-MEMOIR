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

    list_elm_t* head = get_head(L);
    void* pivot = get_data(head);

    list_t* left = new_list();
    list_t* right = new_list();

    // Partition
    for (list_elm_t* E = get_suc(head); E; E = get_suc(E)) {
        void* data = get_data(E);
        if (cmpFct(data, pivot) < 0)
            queue(left, data);
        else
            queue(right, data);
    }

    // Recurse
    quick_sort(left, cmpFct);
    quick_sort(right, cmpFct);

    // Rebuild L
    clean(L);
    for (list_elm_t* E = get_head(left); E; E = get_suc(E))
        queue(L, get_data(E));
    queue(L, pivot);
    for (list_elm_t* E = get_head(right); E; E = get_suc(E))
        queue(L, get_data(E));

    del_list(&left, NULL);
    del_list(&right, NULL);
}

// Lecture d'un fichier .dta et construction du graphe
list_t* read_graph(char* path) {
    FILE* f = fopen(path, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    int nb_jobs;
    if (fscanf(f, "%d", &nb_jobs) != 1) {
        fclose(f);
        return NULL;
    }

    list_t* G = new_list();
    job_t** jobs = malloc(nb_jobs * sizeof(job_t*));
    assert(jobs);

    // Lecture des jobs
    for (int i = 0; i < nb_jobs; i++) {
        char name[100];
        double life;
        fscanf(f, "%s %lf", name, &life);
        jobs[i] = new_job(name);
        set_job_life(jobs[i], life);
        queue(G, jobs[i]);
    }

    // Lecture des dépendances (indices)
    int pred, succ;
    while (fscanf(f, "%d %d", &pred, &succ) == 2) {
        if (pred >= 0 && pred < nb_jobs && succ >= 0 && succ < nb_jobs) {
            job_t* J1 = jobs[pred];
            job_t* J2 = jobs[succ];
            ordered_insert(J1->posteriority, J2, &titleJobCmp);
            ordered_insert(J2->precedence, J1, &titleJobCmp);
            incr_job_oDegree(J1);
            incr_job_iDegree(J2);
        }
    }

    free(jobs);
    fclose(f);
    return G;
}
