#include "job.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

void ranking(list_t* G) {
    list_t* ready = new_list();

    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        J->dyn_input_degree = J->input_degree;
        if (J->dyn_input_degree == 0) {
            queue(ready, J);
        }
    }

    while (!is_empty(ready)) {
        job_t* J = get_data(get_head(ready));
        take_out(ready, J);

        int max_rank = -1;
        for (list_elm_t* E = get_head(J->precedence); E; E = get_suc(E)) {
            job_t* pred = get_data(E);
            if (pred->rank > max_rank)
                max_rank = pred->rank;
        }
        J->rank = max_rank + 1;

        for (list_elm_t* E = get_head(J->posteriority); E; E = get_suc(E)) {
            job_t* succ = get_data(E);
            succ->dyn_input_degree--;
            if (succ->dyn_input_degree == 0) {
                queue(ready, succ);
            }
        }
    }

    free(ready);
}

static bool reachable(job_t* src, job_t* target) {
    if (src == target) return true;

    for (list_elm_t* E = get_head(src->posteriority); E; E = get_suc(E)) {
        job_t* succ = get_data(E);
        if (reachable(succ, target)) return true;
    }

    return false;
}

void prune(list_t* G) {
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        list_elm_t* next = NULL;

        for (list_elm_t* S = get_head(J->posteriority); S; S = next) {
            next = get_suc(S);
            job_t* succ = get_data(S);

            take_out(J->posteriority, succ);
            take_out(succ->precedence, J);
            decr_job_oDegree(J);
            decr_job_iDegree(succ);

            if (!reachable(J, succ)) {
                ordered_insert(J->posteriority, succ, &titleJobCmp);
                ordered_insert(succ->precedence, J, &titleJobCmp);
                incr_job_oDegree(J);
                incr_job_iDegree(succ);
            }
        }
    }
}

void marges(list_t* G) {
    // Initialiser au_plus_tot et au_plus_tard
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        J->au_plus_tot = UNDEF;
        J->au_plus_tard = UNDEF;
    }

    // Étape 1 : calcul au plus tôt (forward)
    bool changed;
    do {
        changed = false;
        for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
            job_t* J = get_data(E);
            if (get_job_iDegree(J) == 0) {
                if (J->au_plus_tot == UNDEF) {
                    J->au_plus_tot = 0;
                    changed = true;
                }
            }
            else {
                double max_pred = -1;
                bool all_pred_ready = true;
                for (list_elm_t* P = get_head(J->precedence); P; P = get_suc(P)) {
                    job_t* pred = get_data(P);
                    if (pred->au_plus_tot == UNDEF) {
                        all_pred_ready = false;
                        break;
                    }
                    double fin_pred = pred->au_plus_tot + pred->life;
                    if (fin_pred > max_pred) max_pred = fin_pred;
                }
                if (all_pred_ready && J->au_plus_tot != max_pred) {
                    J->au_plus_tot = max_pred;
                    changed = true;
                }
            }
        }
    } while (changed);

    // Étape 2 : calcul au plus tard (backward)
    double max_end = 0;
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        double fin = J->au_plus_tot + J->life;
        if (fin > max_end) max_end = fin;
    }
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        if (get_job_oDegree(J) == 0) {
            J->au_plus_tard = max_end - J->life;
        }
    }

    do {
        changed = false;
        for (list_elm_t* E = get_tail(G); E; E = get_pred(E)) {
            job_t* J = get_data(E);
            if (get_job_oDegree(J) == 0) continue;

            bool all_succ_ready = true;
            double min_succ = DBL_MAX;
            for (list_elm_t* S = get_head(J->posteriority); S; S = get_suc(S)) {
                job_t* succ = get_data(S);
                if (succ->au_plus_tard == UNDEF) {
                    all_succ_ready = false;
                    break;
                }
                double tard = succ->au_plus_tard - J->life;
                if (tard < min_succ) min_succ = tard;
            }
            if (all_succ_ready && J->au_plus_tard != min_succ) {
                J->au_plus_tard = min_succ;
                changed = true;
            }
        }
    } while (changed);

    // Étape 3 : marges et chemin critique
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        J->marge_totale = J->au_plus_tard - J->au_plus_tot;

        double min_succ_start = DBL_MAX;
        for (list_elm_t* S = get_head(J->posteriority); S; S = get_suc(S)) {
            job_t* succ = get_data(S);
            double val = succ->au_plus_tot;
            if (val < min_succ_start) min_succ_start = val;
        }

        if (get_job_oDegree(J) == 0) {
            J->marge_libre = J->marge_totale;
        }
        else {
            J->marge_libre = min_succ_start - J->au_plus_tot - J->life;
        }

        J->critique = (J->marge_totale == 0);
    }
}