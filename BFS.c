 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include "adjarray.h"
#include <stdbool.h>

//#define NLINKS 100000000000 //maximum number of edges for memory allocation, will increase if needed


// A structure to represent a queue 
struct Queue { 
	int front, rear, size; 
	unsigned capacity; 
	int* array; 
}; 

// function to create a queue 
// of given capacity. 
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity) 
{ 
	struct Queue* queue = (struct Queue*)malloc( 
		sizeof(struct Queue)); 
	queue->capacity = capacity; 
	queue->front = queue->size = 0; 

	// This is important, see the enqueue 
	queue->rear = capacity - 1; 
	queue->array = (int*)malloc( 
		queue->capacity * sizeof(int)); 
	return queue; 
} 

// Queue is full when size becomes 
// equal to the capacity 
int isFull(struct Queue* queue) 
{ 
	return (queue->size == queue->capacity); 
} 

// Queue is empty when size is 0 
int isEmpty(struct Queue* queue) 
{ 
	return (queue->size == 0); 
} 

// Function to add an item to the queue. 
// It changes rear and size 
void enqueue(struct Queue* queue, int item) 
{ 
	if (isFull(queue)) 
		return; 
	queue->rear = (queue->rear + 1) 
				% queue->capacity; 
	queue->array[queue->rear] = item; 
	queue->size = queue->size + 1;
} 

// Function to remove an item from queue. 
// It changes front and size 
int dequeue(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return 0; 
	int item = queue->array[queue->front]; 
	queue->front = (queue->front + 1) 
				% queue->capacity; 
	queue->size = queue->size - 1; 
	return item; 
} 

// Function to get front of queue 
int front(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return 0; 
	return queue->array[queue->front]; 
} 

// Function to get rear of queue 
int rear(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return 0; 
	return queue->array[queue->rear]; 
} 




//compute BFS algorithm
int BFSlower(adjlist* g, int s) {
    printf("debut");
    int nbNodes = g->n;   
    
    //int distance[nbNodes];
    // bool visited[nbNodes];
    bool *visited = malloc((g->n+1)*sizeof(bool));
    int *distance = malloc((g->n+1)*sizeof(int));
    
    for (int i = 0; i < nbNodes; i++)
    {
        visited[i]=0;
        distance[i]=0;
    }
    // file
    visited[s]=1;
    printf("passage");
    struct Queue* queue = createQueue(nbNodes+1);
    enqueue(queue,s);
    int maxDistance =0;
    while (!isEmpty(queue)) {
        int currentElement = dequeue(queue);
        for (int i = g->cd[currentElement]; i < g->cd[currentElement + 1]; i++)
            {int neigh = g->adj[i];
            if (!visited[neigh])
            {
                visited[neigh] = 1;
                enqueue(queue,neigh);
                distance[neigh] = distance[currentElement] + 1;
                if (distance[neigh]>maxDistance){
                    maxDistance = distance[neigh];
                }
            }            
        }        
    }
    free(visited);
    free(distance);
    return maxDistance;
}


int main(int argc,char** argv){
	adjlist* g;

	printf("Reading edgelist from file %s\n",argv[1]);
	g=readedgelist(argv[1]);

	printf("Number of nodes: %lu\n",g->n);
	printf("Number of edges: %lu\n",g->e);

	printf("Building the adjacency list\n");
	mkadjlist(g);
    int s = 1;
    int maxDist = BFSlower(g, s);
    printf("%d\n", maxDist);
	free_adjlist(g);

	return 0;
}