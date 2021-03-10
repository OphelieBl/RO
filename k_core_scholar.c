#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "adjarray.h"

unsigned long *degree_list(adjlist* g){
  unsigned long *d=calloc(g->n,sizeof(unsigned long));
  for (int i=0;i<g->n;i++){
    d[i] = g->cd[i+1] - g->cd[i];
  }
  return d;
}

int search_min(adjlist* g, unsigned long *d){
  int min_node = 0;
  int min_d = d[0];
  for (int i=1;i<g->n;i++){
      if (d[i]<min_d){
        min_d = d[i];
        min_node = i;
      }
  }
  return min_node;
}

int k_core(adjlist* g){
  unsigned long *d = degree_list(g);
  unsigned long *deg = degree_list(g);
  int min_node = 0;
  int min_deg = 0;
  int i = g->n;
  int c = 0;
  FILE* fichier = NULL;
  fichier = fopen("coreness.txt", "w");
  while(i>0){
    min_node = search_min(g, d);
    min_deg = d[min_node];
    c = (min_deg>c) ? min_deg : c;
    if (fichier != NULL){
      fprintf(fichier, "%lu", deg[min_node]);
      fprintf(fichier, ",");
      fprintf(fichier, "%d\n", c);
    }
    d[min_node] = g->n;
    for (int j = g->cd[min_node]; j < g->cd[min_node + 1]; j++){
      int neigh = g->adj[j];
      d[neigh] = d[neigh] - 1;
    }
    int eta = i;
    i = i - 1;
  }
  fclose(fichier);
  free(d);
  return c;
}

int main(int argc,char** argv)
    {
      adjlist* g;
      time_t t1,t2;
      t1=time(NULL);
      g=readedgelist(argv[1]);
      mkadjlist(g);
      //unsigned long *d = degree_list(g);
      //int node= search_min(g, d);

      printf("min deg: %d\n",k_core(g));
      free_adjlist(g);
      t2=time(NULL);

    	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
      return 0;
    }
