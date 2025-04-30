
#include "job.h"
#include "list.h"
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>

// Calcul des rangs selon algorithme topologique
void ranking(list_t* G) {
    // File des prêts à traiter
    list_t* ready = new_list();

    // Initialisation des degrés entrants dynamiques
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        J->dyn_input_degree = J->input_degree;
        if (J->dyn_input_degree == 0) {
            queue(ready, J);
        }
    }

    // Parcours en ordre topo
    while (!is_empty(ready)) {
        job_t* J = take_out(ready);
        // Calcul du rang : max des prédécesseurs +1
        int max_rank = -1;
        for (list_elm_t* P = get_head(J->precedence); P; P = get_suc(P)) {
            job_t* pred = get_data(P);
            if (pred->rank > max_rank) {
                max_rank = pred->rank;
            }
        }
        J->rank = max_rank + 1;
        // Mise à jour des successeurs
        for (list_elm_t* S = get_head(J->posteriority); S; S = get_suc(S)) {
            job_t* succ = get_data(S);
            succ->dyn_input_degree--;
            if (succ->dyn_input_degree == 0) {
                queue(ready, succ);
            }
        }
    }

    // Libération de la file
    del_list(&ready, NULL);
}

// Test récursif pour élagage
static bool reachable(job_t* src, job_t* target) {
    if (src == target) return true;
    for (list_elm_t* E = get_head(src->posteriority); E; E = get_suc(E)) {
        if (reachable(get_data(E), target)) return true;
    }
    return false;
}

// Suppression des arcs redondants
void prune(list_t* G) {
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        list_elm_t* cur = get_head(J->posteriority);
        while (cur) {
            list_elm_t* next = get_suc(cur);
            job_t* succ = get_data(cur);
            // Temporarily remove
            take_out(J->posteriority);
            remove_item(succ->precedence, J);
            J->output_degree--;
            succ->input_degree--;
            // Reinsert if still necessary
            if (!reachable(J, succ)) {
                ordered_insert(J->posteriority, succ, &titleJobCmp);
                ordered_insert(succ->precedence, J, &titleJobCmp);
                J->output_degree++;
                succ->input_degree++;
            }
            cur = next;
        }
    }
}

// Calcul des dates et marges
void marges(list_t* G) {
    // Initialisation au plus tôt
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        J->au_plus_tot = 0;
    }
    // Propagation au plus tôt
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        for (list_elm_t* S = get_head(J->posteriority); S; S = get_suc(S)) {
            job_t* succ = get_data(S);
            double candidate = J->au_plus_tot + J->life;
            if (candidate > succ->au_plus_tot) {
                succ->au_plus_tot = candidate;
            }
        }
    }
    // Date de fin du projet
    double project_end = 0;
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        double end = J->au_plus_tot + J->life;
        if (end > project_end) project_end = end;
    }
    // Initialisation au plus tard
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        if (J->posteriority->numelm == 0) {
            J->au_plus_tard = project_end - J->life;
        }
        else {
            J->au_plus_tard = project_end;
        }
    }
    // Propagation au plus tard
    for (list_elm_t* E = get_tail(G); E; E = get_pred(E)) {
        job_t* J = get_data(E);
        for (list_elm_t* P = get_head(J->posteriority); P; P = get_suc(P)) {
            job_t* succ = get_data(P);
            double candidate = succ->au_plus_tard - J->life;
            if (candidate < J->au_plus_tard) {
                J->au_plus_tard = candidate;
            }
        }
    }
    // Calcul des marges
    for (list_elm_t* E = get_head(G); E; E = get_suc(E)) {
        job_t* J = get_data(E);
        J->marge_totale = J->au_plus_tard - J->au_plus_tot;
        if (J->posteriority->numelm == 0) {
            J->marge_libre = J->marge_totale;
        }
        else {
            double min_start = DBL_MAX;
            for (list_elm_t* S = get_head(J->posteriority); S; S = get_suc(S)) {
                job_t* succ = get_data(S);
                if (succ->au_plus_tot < min_start) min_start = succ->au_plus_tot;
            }
            J->marge_libre = min_start - (J->au_plus_tot + J->life);
        }
        J->critique = (J->marge_totale == 0);
    }
}
