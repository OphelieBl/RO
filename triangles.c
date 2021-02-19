#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "adjarray.h"

#define SIZE 10
struct queue {
  int size;
  int* elements;
  unsigned capacity;
  int head;
  int tail;
};

struct queue* create_queue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);



struct queue* create_queue(unsigned capacity) {
  struct queue* q = malloc(sizeof(struct queue));
  q->capacity = capacity;
  q->head = 0;
  q->tail = capacity - 1;
  q->size = 0;
  q->elements = (int*)malloc(q->capacity * sizeof(int));
  return q;
};


int isEmpty(struct queue* q) {
  return q->size == 0;
};

void enqueue(struct queue* q, int x)
{
    if (q->size == q->capacity)
        printf("\nFull!!");
    else {
		q->tail = (q->tail + 1) % q->capacity;
        q->elements[q->tail] = x;
		q->size = q->size+1;
    }
}

int dequeue(struct queue* q){
    int x;
	if (isEmpty(q)){
		printf("\nEmpty!!");
        x = -1;
	} else {
		x = q->elements[q->head];
		q->head = (q->head + 1) % q->capacity;
        q->size = q->size - 1;
	}
	return x;
	}

struct triangle {
  int a;   /* A triangle is defined by its three vertices */
  int b;
  int c;
};

struct triangle get_triangle(int, int, int);

struct triangle get_triangle(int i, int j, int k)
{ struct triangle tr;
  tr.a = i;
  tr.b = j;
  tr.c = k;
  return tr;              /* Return triangle with vertices i, j, k */
}
void display_triangle(struct triangle tr){
	printf("%d ", tr.a);
	printf("%d ", tr.b);
	printf("%d ", tr.c);
	printf("\n");
}
//Represent a node of the singly linked list
struct node{
    int data;
    struct node *next;
};

//Represent the head and tail of the singly linked list
struct node *head, *tail = NULL;

//addNode() will add a new node to the list
void addNode(int data) {
    //Create a new node
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    //Checks if the list is empty
    if(head == NULL) {
        //If list is empty, both head and tail will point to new node
        head = newNode;
        tail = newNode;
    }
    else {
        //newNode will be added after tail such that tail's next will point to newNode
        tail->next = newNode;
        //newNode will become new tail of the list
        tail = newNode;
    }
}

 //sortList() will sort nodes of the list in ascending order
void sortList() {
        //Node current will point to head
        struct node *current = head, *index = NULL;
        int temp;

        if(head == NULL) {
            return;
        }
        else {
            while(current != NULL ) {
                //Node index will point to node next to current
                index = current->next;
                while(index != NULL) {
                    //If current node's data is greater than index's node data, swap the data between them
                    if(current->data > index->data ) {
                        temp = current->data;
                        current->data = index->data;
                        index->data = temp;
                    }
                    index = index->next;
                }
                current = current->next;
            }
        }
    }
	void sortList_(adjlist* G ) {
	        //Node current will point to head
	        //struct node *head, *tail = NULL;
	        struct node *current = head, *index = NULL;
	        int temp;

	        if(head == NULL) {
	            return;
	        }
	        else {
	            while(current != NULL) {
	                //Node index will point to node next to current
	                index = current->next;

	                while(index != NULL) {
	                    //If current node's data is greater than index's node data, swap the data between them
	                    if(G->cd[current->data+1]- G->cd[current->data]< G->cd[index->data+1]-G->cd[index->data]) {
	                        temp = current->data;
	                        current->data = index->data;
	                        index->data = temp;
	                    }
	                    index = index->next;
	                }
	                current = current->next;
	            }

	        }
	    }
    //display() will display all the nodes present in the list
    void display() {
        //Node current will point to head
        struct node *current = head;
        if(head == NULL) {
            printf("List is empty \n");
            return;
        }
        while(current != NULL) {
            //Prints each node by incrementing pointer
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
    struct queue* TSI (adjlist* G, unsigned long i) {
        //Node current will point to head
        head = NULL;
        tail = NULL;
        int e = 0;
        for (int j = G->cd[i]; j < G->cd[i + 1]; j++){
            e++;
            int neigh = G->adj[j];
            //printf("The neighbor is: %d\n",neigh);
            addNode(neigh);
        }
        //printf("Original list: \n");
        //display();
        //sortList();
				//sortList_(G);
				struct node *curr = head;
				while(curr!=NULL & head->data < i){
					head = curr->next;
					curr = curr->next;
				}
        //printf("Sorted list: \n");
        //display();
        int *list = malloc((e+1)*sizeof(int));
        struct node *current = head;
				int N = G->n;
        struct queue* queue = create_queue(N+1);

        while(current != NULL) {
            //Prints each node by incrementing pointer
            //printf("%d ", current->data);
						enqueue(queue,current->data);
            current = current->next;

        }
        return queue;
    }

struct queue* inter_list(struct queue* q1, struct queue* q2){
	int s;

	if (q1->size<q2->size){
		s = q1->size;
	}
	else{
		s = q2->size;
	}

	struct queue* queue = create_queue(s+1);
	for(int i=0; i<q1->size; i++){
		for (int j=0; j<q2->size; j++){
			if (q1->elements[i] == q2->elements[j]){
				enqueue(queue, q1->elements[i]);
			}
		}
	}

	return queue;
}

void TRList(adjlist* G){
    for (int i=0;i<G->e;i++){
        struct queue* TSI_U = TSI (G, G->edges[i].s);
        struct queue* TSI_V = TSI (G, G->edges[i].t);
				if((!isEmpty(TSI_U))&(!isEmpty(TSI_V))){
					struct queue* W = inter_list(TSI_U, TSI_V);
					for (int j=0; j<W->size;j++){
							struct triangle tr = get_triangle(G->edges[i].s, G->edges[i].t, W->elements[j]);
							display_triangle(tr);
					}
					free(TSI_U);
					free(TSI_V);
					free(W);

				}
    }

}

int main(int argc,char** argv)
    {
        adjlist* g;
        g=readedgelist(argv[1]);
        mkadjlist(g);

        TRList(g);
        free_adjlist(g);
        return 0;
    }
