#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "job.h"
#include "list.h"

// Fonction locale pour copier une chaîne (équivalent de strdup)
static char* my_strdup(const char* s) {
    if (!s) return NULL;
    char* dup = malloc(strlen(s) + 1);
    if (dup) strcpy(dup, s);
    return dup;
}

// Comparateur pour trier par degré d'entrée
int iDegreeJobCmp(void* A, void* B) {
    job_t* j1 = A;
    job_t* j2 = B;
    return j1->dyn_input_degree - j2->dyn_input_degree;
}

// Comparateur pour trier par titre
int titleJobCmp(void* A, void* B) {
    job_t* j1 = A;
    job_t* j2 = B;
    return strcmp(j1->title, j2->title);
}

// Crée un nouveau job
job_t* new_job(char* title) {
    assert(title);  // sécurité

    job_t* J = malloc(sizeof(job_t));
    assert(J);  // sécurité

    J->title = my_strdup(title);  // on copie la chaîne pour ne pas perdre le contenu
    J->precedence = new_list();
    J->posteriority = new_list();
    J->input_degree = 0;
    J->output_degree = 0;
    J->dyn_input_degree = 0;
    J->rank = -1;
    J->life = 0;
    J->au_plus_tot = -1;
    J->au_plus_tard = -1;
    J->marge_totale = 0;
    J->marge_libre = 0;
    J->critique = false;

    return J;
}

// Libère un job
void free_job(void* ptr) {
    job_t* J = ptr;
    if (!J) return;

    free(J->title);
    del_list(&J->precedence, NULL);
    del_list(&J->posteriority, NULL);
    free(J);
}

// Affiche un job
void view_job(void* ptrJ) {
    job_t* J = ptrJ;
    if (!J || !J->title) {
        printf("Job invalide\n");
        return;
    }

    printf("Job %s (durée: %.2f) - rang: %d, marge totale: %.2f, marge libre: %.2f%s\n",
        J->title, J->life, J->rank,
        J->marge_totale, J->marge_libre,
        J->critique ? " [CRITIQUE]" : "");
}

// Accesseurs
const char* get_job_title(job_t* J) { return J ? J->title : NULL; }
int get_job_iDegree(job_t* J) { return J ? J->input_degree : -1; }
int get_job_oDegree(job_t* J) { return J ? J->output_degree : -1; }

// Modificateurs
void set_job_title(job_t* J, char* title) {
    if (!J) return;
    free(J->title);
    J->title = my_strdup(title);
}

void set_job_life(job_t* J, double life) {
    if (J) J->life = life;
}

void incr_job_iDegree(job_t* J) { if (J) J->input_degree++; }
void incr_job_oDegree(job_t* J) { if (J) J->output_degree++; }
void decr_job_iDegree(job_t* J) { if (J) J->input_degree--; }
void decr_job_oDegree(job_t* J) { if (J) J->output_degree--; }
