#pragma once
#include "job_1.h"

// Spécifiques à job
int get_job_iDegree(job_t* J);
int get_job_oDegree(job_t* J);
void incr_job_iDegree(job_t* J);
void incr_job_oDegree(job_t* J);
void decr_job_iDegree(job_t* J);
void decr_job_oDegree(job_t* J);
