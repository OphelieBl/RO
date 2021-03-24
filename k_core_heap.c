#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "adjarray.h"
#include "minheap.h"


Heap *degree_list(adjlist* g){
  int HEAP_SIZE = g->n;
  Heap *heap = CreateHeap(HEAP_SIZE, 0); //Min Heap
  //int *d = malloc((HEAP_SIZE)*sizeof(int));
  node node = {};
  for (int i=0;i<g->n;i++){
    node.data = i;
    node.deg = g->cd[i+1] - g->cd[i];
    insert(heap, node);
  }
  return heap;
}

int *node_index(adjlist* g, Heap *degree_list){
  int *d = malloc((g->n)*sizeof(int));
  for (int i=0;i<g->n;i++){
    d[degree_list->arr[i].data] = i;
  }
  return d;
}

int *heapify_top_bottom(Heap *h, int parent_node, int *d){
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;
    node temp;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && h->arr[left].deg < h->arr[parent_node].deg)
        min=left;
    else
        min =parent_node;
    if(right != -1 && h->arr[right].deg < h->arr[min].deg)
        min = right;

    if(min != parent_node){
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;

        d[h->arr[parent_node].data] = parent_node;
        d[h->arr[min].data] = min;
        // recursive  call
        d = heapify_top_bottom(h, min, d);
    }
    //printf("min: %d \n", min);
    return d;
}

node PopMin(adjlist* g, Heap *h, int *d){
    node pop;
    if(h->count==0){
        printf("\n__Heap is Empty__\n");
        //return -1;
    }
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    d = heapify_top_bottom(h, 0, d);
    for (int j = g->cd[pop.data]; j < g->cd[pop.data + 1]; j++){
        int neigh = g->adj[j];
        h->arr[d[neigh]].deg = h->arr[d[neigh]].deg - 1;
    }
    return pop;
}
/*int search_min(adjlist* g, unsigned long *d){
  int min_node = 0;
  int min_d = d[0];
  for (int i=1;i<g->n;i++){
      if (d[i]<min_d){
        min_d = d[i];
        min_node = i;
      }
  }
  return min_node;
}*/

int k_core(adjlist* g){
  Heap *heap = degree_list(g);
  int * node_ind = node_index(g, heap);
  //int min_node = 0;
  node min_node = {0,0};
  int min_deg = 0;
  int i = g->n;
  int c = 0;
  int nbEdge = g->e;
  int nbNode = g->n;
  int size_densest_subG = nbNode;
  float ratio = (float)nbEdge/nbNode;
  float deg_den = (float)2*nbEdge/(nbNode*(nbNode-1));
  while(i>0){
    min_node = PopMin(g, heap, node_ind);
    min_deg = min_node.deg;
    nbEdge = nbEdge - min_deg;
    nbNode = nbNode - 1;
    if ((float)nbEdge/nbNode>=ratio){
      ratio = (float)nbEdge/nbNode;
      size_densest_subG = nbNode;
      deg_den = (float)2*nbEdge/(nbNode*(nbNode-1));
    }
    c = (min_deg>c) ? min_deg : c;
    //d[min_node] = g->n;
    /*for (int j = g->cd[min_node]; j < g->cd[min_node + 1]; j++){
      int neigh = g->adj[j];
      d[neigh] = d[neigh] - 1;
  }*/
    int eta = i;
    i = i - 1;
  }
  free(heap);
  printf("the size of a densest core ordering prefix: %d\n",size_densest_subG);
  printf("the average degree density: %.6f\n",ratio);

  printf("degree density: %.6f\n",deg_den);
  return c;
}


int main(int argc,char** argv)
    {
      adjlist* g;
      time_t t1,t2;
      t1=time(NULL);
      g=readedgelist(argv[1]);
      int N = g->n;
      int E = g->e;

      mkadjlist(g);
      //unsigned long *d = degree_list(g);
      //int node= search_min(g, d);

      printf("the core value: %d\n",k_core(g));


      free_adjlist(g);
      t2=time(NULL);

    	printf("- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));
      return 0;
    }
