#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "job.h"
#include "list.h"

job_t* new_empty_job() {
    job_t* J = calloc(1, sizeof(job_t));
    assert(J);
    J->precedence = new_list();
    J->posteriority = new_list();
    J->rank = UNDEF;
    J->au_plus_tard = UNDEF;
    J->au_plus_tot = UNDEF;
    J->marge_totale = UNDEF;
    J->critique = false;
    return J;
}

job_t* new_job(char* title) {
    job_t* J = new_empty_job();
    J->title = strdup(title);
    return J;
}

void free_job(job_t** ptrJ) {
    assert(ptrJ && *ptrJ);
    if ((*ptrJ)->title) free((*ptrJ)->title);
    free(*ptrJ);
    *ptrJ = NULL;
}

void view_job(void* ptrJ) {
    job_t* J = (job_t*)ptrJ;
    printf("JOB %s\n\tpreceeded by [", get_job_title(J));
    for (list_elm_t* E = get_head(J->precedence); E; E = get_suc(E)) {
        printf(" %s", get_job_title(get_data(E)));
    }
    printf(" ]\n");
    printf("\tfollowed by [");
    for (list_elm_t* E = get_head(J->posteriority); E; E = get_suc(E)) {
        printf(" %s", get_job_title(get_data(E)));
    }
    printf(" ]\n");
    printf("\tiDeg=%d\toDeg=%d\tlife=%2.2lf", J->input_degree, J->output_degree, J->life);
    printf("\trank=");
    if (J->rank == UNDEF) printf("U"); else printf("%d", J->rank);
    printf("\tearly=");
    if (J->au_plus_tot == UNDEF) printf("U"); else printf("%2.2lf", J->au_plus_tot);
    printf("\tlate=");
    if (J->au_plus_tard == UNDEF) printf("U"); else printf("%2.2lf", J->au_plus_tard);
    printf("\ttotale= ");
    if (J->marge_totale == UNDEF) printf("U"); else printf("%2.2lf", J->marge_totale);
    printf("\tcritical= ");
    if (J->critique) printf("Y\n"); else printf("N\n");
}

// === Fonctions utilitaires ===
int get_job_iDegree(job_t* J) { return J->input_degree; }
void set_job_iDegree(job_t* J, int iDegree) { J->input_degree = iDegree; }
void incr_job_iDegree(job_t* J) { J->input_degree++; }
void decr_job_iDegree(job_t* J) { J->input_degree--; }

int get_job_oDegree(job_t* J) { return J->output_degree; }
void set_job_oDegree(job_t* J, int oDegree) { J->output_degree = oDegree; }
void incr_job_oDegree(job_t* J) { J->output_degree++; }
void decr_job_oDegree(job_t* J) { J->output_degree--; }

char* get_job_title(job_t* J) { return J->title; }
void set_job_title(job_t* J, char* title) {
    if (J->title) free(J->title);
    J->title = strdup(title);
}

double get_job_life(job_t* J) { return J->life; }
void set_job_life(job_t* J, double life) { J->life = life; }

int get_job_rank(job_t* J) { return J->rank; }
void set_rank(job_t* J, int rank) { J->rank = rank; }

int iDegreeJobCmp(void* A, void* B) {
    job_t* J1 = (job_t*)A;
    job_t* J2 = (job_t*)B;
    return J1->input_degree - J2->input_degree;
}

int titleJobCmp(void* A, void* B) {
    job_t* J1 = (job_t*)A;
    job_t* J2 = (job_t*)B;
    return strcmp(J1->title, J2->title);
}