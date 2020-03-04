#include "heapTest.h"


typedef struct heapNode{
  int index;//The node "number" used to keep track of position in heap
  double cost;
  int pred;
  int *neighbours; //Node "number" of the node's neighbours
}heapNode;

typedef struct minHeap{
  heapNode *heap;
  int *pos; //Keeps track of where each heapNode is in the heap ie pos[nodeNum] gets the position of the heapNode nodeNum in the heap
  int currSize;
}Heap;

heapNode *newHeapNode(int index, int sx, double cost){
  heapNode *new = (heapNode *)calloc(sizeof(heapNode), 1);
  new->index = index;
  new->cost = cost;
  new->pred = -1;
  new->neighbours = (int *)calloc(sizeof(int), 4);
  new->neighbours[0] = index-sx;
  new->neighbours[1] = index+1;
  new->neighbours[2] = index+sx;
  new->neighbours[3] = index-1;
  return new;
}

Heap *newHeap(int max){
  Heap *h = (Heap *)calloc(sizeof(Heap), 1);
  h->heap = (heapNode *)calloc(sizeof(heapNode), max);
  h->pos = (int *)calloc(sizeof(int), max);
  h->currSize = 0;
  //h->maxSize = max;
  return h;
}


Heap *swap(Heap *h, int posA, int posB){
    int temp;
    heapNode tempNode;
    temp = h->pos[h->heap[posA].index];
    /* printf("OG Pos of Node %d: %d\n", h->heap[posA].index,temp);
    printf("OG Pos of B: %d\n",h->pos[h->heap[posB].index]); */
    h->pos[h->heap[posA].index] = h->pos[h->heap[posB].index];
    h->pos[h->heap[posB].index] = temp;
    /* printf("Pos of A: %d\n",h->pos[h->heap[posA].index]);
    printf("Pos of B: %d\n",h->pos[h->heap[posB].index]);  */
    tempNode = h->heap[posA];
    /* printf("OG Cost of Node at pos %d: %f\n", posA, tempNode.cost);
    printf("OG Cost of B: %f\n", h->heap[posB].cost); */
    h->heap[posA] = h->heap[posB];
    h->heap[posB] = tempNode;
    /* printf("Cost of Node at pos %d: %f\n", posA, h->heap[posA].cost);
    printf("Cost of B: %f\n", h->heap[posB].cost); */
    return h;
}

void heapify(Heap *h, int start){
  //printf("Heapifying...\n");
  int min = start;
  int left = 2*start+1;
  int right = 2*start+2;
  if(h->heap[start].cost != -1 && h->heap[left].cost != -1 && h->heap[right].cost != -1){
    if(h->heap[right].cost != -1 && (left < h->currSize && h->heap[left].cost < h->heap[start].cost)){
      //printf("h1\n");
      min = left;
    }
    if(h->heap[right].cost != -1 && (right < h->currSize && h->heap[right].cost < h->heap[min].cost)){
      //printf("h2\n");
      min = right;
    }
  }else if(h->heap[start].cost == -1 && left < h->currSize && right < h->currSize){
    if(h->heap[left].cost != -1 && h->heap[right].cost != -1){
      if(h->heap[left].cost < h->heap[right].cost){
        //printf("h3\n");
        min = left;
      }else{
        //printf("h4\n");
        min = right;
      }
    }else if(h->heap[left].cost == -1 && h->heap[right].cost != -1){
      //printf("h5\n");
      min = right;
    }else{
      //printf("h6\n");
      min = left;
    }
  }
  if(min != start){
    swap(h, min, start);
    heapify(h, min);
  }
}

void percolate(Heap *h, int i){
    //printf("i: %d\n", i);
    int parent = (i-1)/2;
    /* printf("Parent Node %d w cost %f\n", parent, h->heap[parent].cost);
    printf("%f : %f \n", h->heap[parent].cost, h->heap[i].cost); */
    while(i != 0 && (h->heap[parent].cost > h->heap[i].cost || h->heap[parent].cost == -1)){
        //printf("Percolating...\n");
        //printf("i: %d\n", i);
        if(h->heap[i].cost != -1){
          h = swap(h,parent, i);
          /* printf("%f : %f \n", h->heap[(i-1)/2].cost, h->heap[i].cost);
          printf("%d : %d\n", h->pos[h->heap[(i-1)/2].index], h->pos[h->heap[i].index]); */ 
          i = parent;
          parent = (i-1)/2;
          //printf("Swapped, i=%d, parent=%d, parent cost=%f\n", i, (i-1)/2, h->heap[(i-1)/2].cost);
        }
    }
}

Heap *heapInsert(Heap *h, heapNode *v){
  h->currSize++;
  //printf("Size: %d\n", h->currSize);
  h->heap[h->currSize-1] = *(v);
  h->pos[v->index] = h->currSize-1;
  if(v->cost != -1){
    percolate(h, h->currSize-1);
  }
  return h;
}

heapNode *extractMin(Heap *h){
  if(h->currSize == 0){ //Heap has nothing in it, should never happen
    //printf("empty\n");
    return NULL;
  }else if(h->currSize == 1){ //Heap has only one item
    //printf("1 item\n");
    h->currSize--;
    return &h->heap[0];
  }
  //printf("Extracting...\n");
  heapNode temp = h->heap[0];
  //printf("Extracting node with cost: %f\n", h->heap[0].cost);
  h->heap[0] = h->heap[h->currSize-1]; //Farthest Leaf
  h->heap[h->currSize-1] = temp;
  h->pos[h->heap[0].index] = 0;
  h->pos[h->heap[h->currSize-1].index] = h->currSize-1;
  heapNode *min = &h->heap[h->currSize-1];
  h->currSize--;
  //printf("Size: %d\n", h->currSize);
  heapify(h, 0); //Call heapify on root
  /* printf("Extracting min with cost: %f\n", min->cost);
  printf("New root cost: %f\n", h->heap[0].cost); */
  return min;
}


Heap *decreasePrio(Heap *h, int nodeNum, double newPrio){
    //Decrease the prio of node located at h->heap[i] with newPrio
  //printf("decreasing prio of node %d located at %d, to %f\n", nodeNum, h->pos[nodeNum], newPrio);
  h->heap[h->pos[nodeNum]].cost = newPrio;
  percolate(h, h->pos[nodeNum]);
  //printf("completing decreasePrio\n");
  return h;
}
