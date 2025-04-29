#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "job.h"

// Fonction locale pour dupliquer une chaîne (remplace strdup)
static char* my_strdup(const char* s) {
    char* dup = malloc(strlen(s) + 1);
    if (dup) strcpy(dup, s);
    return dup;
}

// Comparateur par degré entrant
int iDegreeJobCmp(void* A, void* B) {
    job_t* j1 = A;
    job_t* j2 = B;
    return j1->dyn_input_degree - j2->dyn_input_degree;
}

// Comparateur par titre
int titleJobCmp(void* A, void* B) {
    job_t* J1 = A;
    job_t* J2 = B;
    return strcmp(get_job_title(J1), get_job_title(J2));
}

// Crée un nouveau job
job_t* new_job(char* title) {
    job_t* J = malloc(sizeof(job_t));
    assert(J);
    J->title = my_strdup(title);
    J->precedence = new_list();
    J->posteriority = new_list();
    J->input_degree = 0;
    J->output_degree = 0;
    J->dyn_input_degree = 0;
    J->rank = -1;
    J->life = 0;
    J->au_plus_tot = -9999;
    J->au_plus_tard = -9999;
    J->marge_totale = 0;
    J->marge_libre = 0;
    J->critique = false;
    return J;
}

// Libère un job
void free_job(void* ptr) {
    job_t* J = (job_t*)ptr;
    free(J->title);
    del_list(&J->precedence, NULL);
    del_list(&J->posteriority, NULL);
    free(J);
}

// Affiche un job
void view_job(void* ptrJ) {
    job_t* J = (job_t*)ptrJ;
    printf("Job %s (durée: %.2f) - rang: %d, marge totale: %.2f, marge libre: %.2f%s\n",
        J->title, J->life, J->rank,
        J->marge_totale, J->marge_libre,
        J->critique ? " [CRITIQUE]" : "");
}

// Accesseurs
const char* get_job_title(job_t* J) { return J->title; }
int get_job_iDegree(job_t* J) { return J->input_degree; }
int get_job_oDegree(job_t* J) { return J->output_degree; }

// Modificateurs
void set_job_title(job_t* J, char* title) {
    free(J->title);
    J->title = my_strdup(title);
}

void set_job_life(job_t* J, double life) {
    J->life = life;
}

void incr_job_iDegree(job_t* J) { J->input_degree++; }
void incr_job_oDegree(job_t* J) { J->output_degree++; }
void decr_job_iDegree(job_t* J) { J->input_degree--; }
void decr_job_oDegree(job_t* J) { J->output_degree--; }
