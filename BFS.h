 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>//to estimate the runing time
#include "adjarray.h"
#include <stdbool.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

//#define NLINKS 100000000000 //maximum number of edges for memory allocation, will increase if needed


// A structure to represent a queue 
struct Queue { 
	int front, rear, size; 
	unsigned capacity; 
	int* array; 
}; 

typedef struct {
	unsigned long int maxDist;
	unsigned long int furtherPoint;
} pointDistance;


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
pointDistance * BFSlower(adjlist* g, int s) {
    unsigned long int nbNodes = g->n;   
    bool *visited = malloc((g->n+1)*sizeof(bool));
    unsigned long int *distance = malloc((g->n+1)*sizeof(unsigned long int));
    pointDistance* result= malloc(sizeof(pointDistance));
    for (unsigned long int i = 0; i < nbNodes; i++)
    {
        visited[i]=0;
        distance[i]=0;
    }
    // file
    visited[s]=1;
    struct Queue* queue = createQueue(nbNodes+1);
    enqueue(queue,s);
	result->maxDist = 0;
	result->furtherPoint = s;
    while (!isEmpty(queue)) {
        unsigned long int currentElement = dequeue(queue);
        for (unsigned long int i = g->cd[currentElement]; i < g->cd[currentElement + 1]; i++)
            {unsigned long int neigh = g->adj[i];
            if (!visited[neigh])
            {
                visited[neigh] = 1;
                enqueue(queue,neigh);
                distance[neigh] = distance[currentElement] + 1;
                if (distance[neigh]>result->maxDist){
                    result->maxDist = distance[neigh];
					result->furtherPoint = neigh;
                }
            }            
        }        
    }
    free(visited);
    free(distance);
    return result;
}

unsigned long int loopLowerBFS(adjlist* g){
	//100 itérations dans la boucle
	unsigned int nbIter;
	nbIter = MIN(200, g->n - 1);
	bool * treated = malloc((g->n+1)*sizeof(bool));
	for (int i = 0; i < g->n+1; i++){
		treated[i]=0;
	}
	unsigned long int dist = 0;
	unsigned long int currentSommet = g->n - 1;
	bool possible = 0;
	int iter = 0;
	for (int i = 0; i < nbIter; i++){
		// voir si sommet courant est isolé ou déjà traité
		while (!possible && iter < 100){
			// printf("currentSommet  %lu\n", currentSommet);
			//test si sommet déjà traité
			// si dernier sommet de la liste et déjà traité on recommence à 0
			if ((treated[i]) && (currentSommet + 1 == g->n)){
				currentSommet = 0;
			} else {
				if (treated[i]==0){
					possible = 1;
				} else {
					currentSommet = currentSommet + 1;
				}
			}
			iter = iter +1;
		}
		// si on a atteint le nombre d'itérations on initialise par un random
		if (iter == 100) {
			currentSommet = rand() % g->n ;
		}
		// si dernier sommet
		pointDistance * maxDistance = BFSlower(g, currentSommet);
		treated[currentSommet] = 1;
		if (maxDistance->maxDist > dist){
			dist = maxDistance->maxDist;
		}
		currentSommet = maxDistance->furtherPoint;
		free(maxDistance);
		possible = 0;
		iter = 0;
	}

	free(treated);
	return dist;
}

void free_pointDistance(pointDistance *g){
	free(g);
}

