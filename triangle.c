#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include "adjarray.h"
#include <stdbool.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/*struct triangle {
  unsigned long int a;   
  unsigned long int b;
  unsigned long int c;
} */

typedef struct {
  unsigned long int a;   /* A triangle is defined by its three vertices */
  unsigned long int b;
  unsigned long int c;
} triangle;

typedef struct {
	unsigned long int nbTri;//number of triangle
	triangle * tri;//concatenated lists of neighbors of all nodes
} triangleList;

/*void display_triangle(struct triangle tr){
	printf("%d ", tr.a);
	printf("%d ", tr.b);
	printf("%d ", tr.c);
	printf("\n");
}*/

void free_triangleList(triangleList *triangles){
	free(triangles->tri);
	free(triangles);
}

void mkadjlistSolo(adjlist* g){
	unsigned long i,u,v;
	unsigned long *d=calloc(g->n,sizeof(unsigned long));

	for (i=0;i<g->e;i++) {
		d[MIN(g->edges[i].s, g->edges[i].t)]++;
		// d[g->edges[i].t]++;
	}

	g->cd=malloc((g->n+1)*sizeof(unsigned long));
	g->cd[0]=0;
	for (i=1;i<g->n+1;i++) {
		g->cd[i]=g->cd[i-1]+d[i-1];
		d[i-1]=0;
	}

	g->adj=malloc(g->e*sizeof(unsigned long));

	for (i=0;i<g->e;i++) {
		u=g->edges[i].s;
		v=g->edges[i].t;
		g->adj[ g->cd[u] + d[u]++ ]=v;
	}

	free(d);
	// free(g->edges);
}

int compare (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b ); 
}

triangleList * getTriangleList(adjlist * g){
    triangleList * triList = malloc(sizeof(triangleList));
    unsigned long e1=g->e;
    triList -> tri = malloc(e1*sizeof(triangle));
    triList->nbTri=0;
    // sort la liste par noeud
    for (int i = 0; i < g->n; i++)
    {
        if(g->cd[i+1]-g->cd[i] > 1){
            qsort(&g->adj[g->cd[i]], g->cd[i+1]-g->cd[i], sizeof(&g->adj[g->cd[1]]), compare);
        }
    }
    for (int j = 0; j < g->n; j++)
    {
        if (g->cd[j+1]-g->cd[j]>1)
        {
            for (int  k = g->cd[j]; k < g->cd[j+1]; k++)
            {
                int neigh = g->adj[k];
                // calcul de l'intersection
                //int jparc = 0;
                //int kparc = 0;
                if ((g->adj[g->cd[j]+g->cd[j+1]-g->cd[j]-1] >=  g->adj[g->cd[neigh]]) ||
                (g->adj[g->cd[j]] <= g->adj[g->cd[neigh]+g->cd[neigh+1]-g->cd[neigh]-1])){
                    int i = k - g->cd[j];
                    int l = 0;
                    while((i < g->cd[j+1]-g->cd[j]) && (l <g->cd[neigh+1]-g->cd[neigh])) {
                        if(g->adj[g->cd[j]+i]==g->adj[g->cd[neigh]+l]){
                            triList->tri[triList->nbTri].a = j;
                            triList->tri[triList->nbTri].b = neigh;
                            triList->tri[triList->nbTri].c = g->adj[g->cd[j]+i];
                            // triList->nbTri++;
                            //reallocate
                            if (++(triList->nbTri)>e1/2) {//increase allocated RAM if needed
			                    e1+=g->e;
			                    triList->tri=realloc(triList->tri,e1*sizeof(edge));
		                    }
                            i++;
                            l++;
                        } else if (g->adj[g->cd[j]+i]<g->adj[g->cd[neigh]+l]){
                            i++;
                        } else {
                            l++;
                        }
                    }
                /*for (int i = k - g->cd[j]; i < g->cd[j+1]-g->cd[j]; i++){
                    for (int l=0; l < g->cd[neigh+1]-g->cd[neigh]; l++){
                        if(g->adj[g->cd[j]+i]==g->adj[g->cd[neigh]+l]){
                            //triList->tri[triList->nbTri].a = j;
                            //triList->tri[triList->nbTri].b = neigh;
                            //triList->tri[triList->nbTri].c = g->adj[g->cd[j]+i];
                            triList->nbTri++;
                        }
                    }
                }*/
                }

            }
            
        }
        
    }
    

   
    return triList;
}

                /*while((jparc<g->cd[j+1]-g->cd[j])&&(kparc<-g->cd[neigh+1]-g->cd[neigh]-1)){
                    printf("first : %lu", g->adj[g->cd[j]+jparc]);
                    printf("second : %lu\n", g->adj[g->cd[neigh]+kparc]);
                    printf("%d", jparc);
                    if (g->adj[g->cd[j]+jparc]==g->adj[g->cd[neigh]+kparc]){
                        printf("triangle trouvé");
                        triList->tri[triList->nbTri].a = j;
                        triList->tri[triList->nbTri].b = neigh;
                        triList->tri[triList->nbTri].c = g->adj[g->cd[j]+jparc];
                        triList->nbTri++;
                        printf("%lu", triList->tri[triList->nbTri].a);
                        printf("%lu", triList->tri[triList->nbTri].b);
                        printf("%lu\n", triList->tri[triList->nbTri].c);
                        jparc++;
                        kparc++;
                    } else if (g->adj[g->cd[j]+jparc]>g->adj[g->cd[neigh]+kparc]){
                        kparc++;
                    } else {
                        jparc++;
                    }
                }*/

int main(int argc, char** argv)
{
    adjlist* g;
    triangleList * triList;
	time_t t1,t2;
	printf("Reading edgelist from file %s\n",argv[1]);
	g=readedgelist(argv[1]);
    // mkadjlist(g);
	t1=time(NULL);
    
	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);
	mkadjlistSolo(g);
    triList = getTriangleList(g);
    printf("%lu", triList->tri[0].a);
    printf("%lu", triList->tri[0].b);
    printf("%lu", triList->tri[0].c);
    printf("\n%lu nbre de Triangles trouvés \n", triList->nbTri);
	free_adjlist(g);
    free_triangleList(triList);
	t2=time(NULL);
	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
    return 0;
}
