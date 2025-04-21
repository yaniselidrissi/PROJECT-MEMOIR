#pragma once
#include "list.h"
#include <stdbool.h>

typedef struct job {
    char* title;
    list_t* precedence;
    list_t* posteriority;
    int input_degree;
    int output_degree;
    int dyn_input_degree;
    int rank;
    double life;
    double au_plus_tot;
    double au_plus_tard;
    double marge_totale;
    double marge_libre;
    bool critique;
} job_t;


void free_job(void* ptr);
void view_job(void* ptr);
const char* get_job_title(job_t* J);
