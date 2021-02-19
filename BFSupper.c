 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
// #include "adjarray.h"
#include <stdbool.h>
#include "BFS.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/*void permuter(unsigned long int *a, unsigned long int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void triRapid(unsigned long int tab[], unsigned long int rank[], unsigned long int first, unsigned long int last) {
    unsigned long int pivot, i, j;
    if(first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while(tab[i] <= tab[pivot] && i < last)
                i++;
            while(tab[j] > tab[pivot])
                j--;
            if(i < j) {
                permuter(&tab[i], &tab[j]);
                permuter(&rank[i], &rank[j]);
            }
        }
        permuter(&tab[pivot], &tab[j]);
        permuter(&rank[pivot], &rank[j]);
        triRapid(tab, rank, first, j - 1);
        triRapid(tab, rank, j + 1, last);
    }
}*/

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

int compare_function(const void *a,const void *b) {
int *x = (int *) a;
int *y = (int *) b;
return -(*x - *y);
}

struct Neigh {
    unsigned long int id;
    unsigned long int nbNeigh;
};

unsigned long int loopUpperBFS(adjlist* g){
    //unsigned long int * nbNeigh = malloc((g->n+1)*sizeof(unsigned long int));
    //unsigned long int * id = malloc((g->n+1)*sizeof(unsigned long int));
    struct PlayerScore ps[N]
    unsigned long int maxMinDist = 0;
    unsigned long int nbNodes = g->n;
    // pointDistance * maxDistance = malloc(sizeof(pointDistance));
    ///récupère nombre de voisins par noeud
    for (unsigned long int i = 0; i < g->n; i++)
    {
        id[i]=i;
        nbNeigh[i]=g->cd[i+1]-g->cd[i];
    }
    // tri de la liste
    //triRapid(nbNeigh, id, 0, g->n -1);
    qsort(nbNeigh,nbNodes,sizeof(unsigned long int),compare_function);
    // qsort(nbNeigh, id, nbNodes);
    printf("fin du tri");
    printf("nbNeigh %lu\n", nbNeigh[0]);
    printf("nbNeigh %lu\n", nbNeigh[1]);
    printf("nbNeigh %lu\n", nbNeigh[2]);
    // on prend les 100 qui ont le plus de voisins
    // int nbIter = MIN(100, g->n - 1);
    /*for ( int i = 0; i < nbIter; i++)
    {
        maxDistance = BFSlower(g, id[i]);
        if (maxDistance->maxDist>maxMinDist){
            maxMinDist = maxDistance->maxDist;
        }
    }  */ 
    free(id);
    free(nbNeigh);
    // free(maxDistance);
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