 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
// #include "adjarray.h"
#include <stdbool.h>
#include "BFS.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

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
    unsigned long int maxDist = loopLowerBFS(g);
    printf("%lu\n", maxDist);

	free_adjlist(g);
	t2=time(NULL);

	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}