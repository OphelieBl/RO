/* Sudhanshu Patel sudhanshuptl13@gmail.com */
/*
Min Heap implementation in c
*/
#include<stdio.h>
#include<stdlib.h>
/*
 Array Implementation of MinHeap data Structure
*/

int HEAP_SIZE = 20;
typedef struct node {
    int data ;
    int deg;
    int *neigh;
} node ;

struct Heap{
    node *arr;
    int count;
    int capacity;
    int heap_type; // for min heap , 1 for max heap
};
typedef struct Heap Heap;

Heap *CreateHeap(int capacity,int heap_type);
void insert(Heap *h, node key);
void print(Heap *h);
void heapify_bottom_top(Heap *h,int index);
void heapify_top_bottom(Heap *h, int parent_node, int *d);
node PopMin(adjlist* g, Heap *h, int *d);



Heap *CreateHeap(int capacity,int heap_type){
    Heap *h = (Heap * ) malloc(sizeof(Heap)); //one is number of heap

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error!");
        //return -1;
    }
    h->heap_type = heap_type;
    h->count=0;
    h->capacity = capacity;
    h->arr = (node *) malloc(capacity*sizeof(node)); //size in bytes

    //check if allocation succeed
    if ( h->arr == NULL){
        printf("Memory Error!");
        //return -1;
    }
    return h;
}

void insert(Heap *h, node key){
    if( h->count < h->capacity){
        h->arr[h->count] = key;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}

void heapify_bottom_top(Heap *h,int index){
    node temp;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node].deg > h->arr[index].deg){
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = temp;
        heapify_bottom_top(h,parent_node);
    }
}
/*
void heapify_top_bottom(Heap *h, int parent_node, int d){
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
        d[parent_node] = h->arr[parent_node].data;
        d[index] = h->arr[index].data;
        // recursive  call
        heapify_top_bottom(h, min, d);
    }
    //printf("min: %d \n", min);
}

node PopMin(Heap *h){
    node pop;
    if(h->count==0){
        printf("\n__Heap is Empty__\n");
        //return -1;
    }
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    heapify_top_bottom(h, 0, d);
    return pop;
}
*/
void print(Heap *h){
    int i;
    printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        printf("-> %d ",h->arr[i].deg);
    }
    printf("->__/\\__\n");
}
/*int main(){
    int i;
    Heap *heap = CreateHeap(HEAP_SIZE, 0); //Min Heap
    node n = {0,0};
    if( heap == NULL ){
        printf("__Memory Issue____\n");
        return -1;
    }

    for(i =9;i>0;i--){
        n.data = i*1000;
        n.deg = i;
        insert(heap, n);
    }
    print(heap);

    for(i=9;i>=0;i--){
        node pope =  PopMin(heap);
        printf(" Pop Minima : %d\n", pope.deg);
        printf("min : %d\n", pope.data);
        print(heap);
    }
    return 0;
}*/
