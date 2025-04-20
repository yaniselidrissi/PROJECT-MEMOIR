#pragma once

// === Degrés d'entrée (input) ===
int get_job_iDegree(job_t* J);
void set_job_iDegree(job_t* J, int iDegree);
void incr_job_iDegree(job_t* J);
void decr_job_iDegree(job_t* J);

// === Degrés de sortie (output) ===
int get_job_oDegree(job_t* J);
void set_job_oDegree(job_t* J, int oDegree);
void incr_job_oDegree(job_t* J);
void decr_job_oDegree(job_t* J);

// === Titre et durée ===
char* get_job_title(job_t* J);
void set_job_title(job_t* J, char* title);

double get_job_life(job_t* J);
void set_job_life(job_t* J, double life);

// === Rang ===
int get_job_rank(job_t* J);
void set_rank(job_t* J, int rank);

// === Fonctions de comparaison ===
int titleJobCmp(void* A, void* B);
int iDegreeJobCmp(void* A, void* B);
int oDegreeJobCmp(job_t* J1, job_t* J2);
int rangJobCmp(job_t* J1, job_t* J2);
