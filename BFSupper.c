 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
// #include "adjarray.h"
#include <stdbool.h>
#include "BFS.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


void tri_rapide (unsigned long int **nbNeigh, unsigned long int **id, unsigned long int taille) {
    unsigned long int otherElement, currentElement;
    unsigned long int pivot, temporaryValue;
    if (taille < 2) return;
    // On prend comme pivot l element le plus a droite
    pivot = *nbNeigh[taille - 1];
    otherElement  = currentElement = 0;
    while (currentElement<taille ) {
        if (pivot <= *nbNeigh[currentElement] ) {
            if (otherElement != currentElement) {
                temporaryValue=*nbNeigh[currentElement];
                *nbNeigh[currentElement]=*nbNeigh[otherElement];
                *nbNeigh[otherElement]=temporaryValue;  
                temporaryValue = *id[currentElement];
                *id[currentElement]=*id[otherElement];
                *id[otherElement]=temporaryValue;            
            }
            otherElement ++;
        }
        currentElement ++;
    }
    tri_rapide(nbNeigh, id, otherElement - 1);
    tri_rapide(nbNeigh + otherElement - 1,  id, taille - otherElement + 1);
}

struct Neigh {
    unsigned long int id;
    unsigned long int nbNeigh;
};


int compare (const void * a, const void * b)
{
    return ( (*(struct Neigh*)b).nbNeigh - (*(struct Neigh*)a).nbNeigh );
}

unsigned long int loopUpperBFS(adjlist* g){
    struct Neigh * neigh = (struct Neigh *)malloc((g->n+1)*sizeof(struct Neigh));
    unsigned long int maxMinDist = 0;
    unsigned long int nbNodes = g->n;
    pointDistance * maxDistance = malloc(sizeof(pointDistance));
    ///récupère nombre de voisins par noeud
    for (unsigned long int i = 0; i < g->n; i++)
    {
        neigh[i].id=i;
        neigh[i].nbNeigh=g->cd[i+1]-g->cd[i];
    }
    // tri de la liste
    //triRapid(nbNeigh, id, 0, g->n -1);
    qsort(neigh,nbNodes,sizeof(struct Neigh),compare);
    // qsort(nbNeigh, id, nbNodes);
    printf("fin du tri");
    // on prend les 100 qui ont le plus de voisins
    int nbIter = MIN(100, g->n - 1);
    for ( int i = 0; i < nbIter; i++)
    {
        maxDistance = BFSlower(g, neigh[i].id);
        if (maxDistance->maxDist>maxMinDist){
            maxMinDist = maxDistance->maxDist;
        }
    }
    free(neigh);
    free(maxDistance);
    return maxMinDist;
}

int main(int argc,char** argv){
	adjlist* g;

	printf("Reading edgelist from file %s\n",argv[1]);
	g=readedgelist(argv[1]);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building the adjacency list\n");
	mkadjlist(g);
	time_t t1,t2;

	t1=time(NULL);
    unsigned long int maxDist = loopUpperBFS(g);
    printf("%lu\n", maxDist);

	free_adjlist(g);
	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}