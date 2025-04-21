#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include "job.h"
#include "rank.h"
#include "io.h"


int main(int argc, char ** argv){
    if(argc < 2) exit(-1);

    list_t * G = read_graph(argv[1]);
    printf("Liste des taches lue\n");
    view_list(G, &view_job);

    printf("Liste des taches triee par degre d'entree croissant\n");
    quick_sort(G, &iDegreeJobCmp);
    view_list(G,&view_job);

    printf("Liste des taches triee par rang croissant\n");
    ranking(G);
    view_list(G,&view_job);

    printf("Prune edges\n");
    prune(G);
    view_list(G,&view_job);

    printf("\nMarges totales des taches\n");
    marges(G);
    view_list(G,&view_job);
    return 0;
}
