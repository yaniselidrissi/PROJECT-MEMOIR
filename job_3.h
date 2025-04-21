#pragma once
#include "job_1.h"

// Création et modif
job_t* new_job(char* title);
void set_job_title(job_t* J, char* title);
void set_job_life(job_t* J, double life);

// Comparateurs
int iDegreeJobCmp(void* A, void* B);
int titleJobCmp(void* A, void* B);
