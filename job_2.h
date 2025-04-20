#pragma once

job_t * new_empty_job();
job_t * new_job(char * title);
void free_job(job_t ** ptrJ);

void view_job(void* ptrJ);


char * get_job_title(job_t * J);
void set_job_title(job_t * J, char * title);

double get_job_life(job_t * J);
void set_job_life(job_t * J, double life);

int get_job_iDegree(job_t * J);
void set_job_iDegree(job_t * J, int iDegree);
void incr_job_iDegree(job_t * J);
void decr_job_iDegree(job_t * J);
