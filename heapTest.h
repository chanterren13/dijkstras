#ifndef __HEAPTEST_H
#define __HEAPTEST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct heapNode{
  int index;
  int num; //The node "number" used to keep track of position in heap
  double cost;
  int pred;
  int *neighbours; //Node "number" of the node's neighbours
}heapNode;

typedef struct minHeap{
  heapNode *heap;
  int *pos; //Keeps track of where each heapNode is in the heap ie pos[nodeNum] gets the position of the heapNode nodeNum in the heap
  int currSize;
  int maxSize;
}Heap;

heapNode *newHeapNode(int index, int sx, double cost);
heapNode *extractMin(Heap *h);
Heap *newHeap(int max);
Heap *swap(Heap *h, int posA, int posB);
Heap *heapInsert(Heap *h, heapNode *v);
Heap *decreasePrio(Heap *h, int nodeNum, double newPrio);
void heapify(Heap *h, int start);
void percolate(Heap *h, int i);

#endif