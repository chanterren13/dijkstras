#include "Dijkstras.h"
#include <math.h>


double weight(int a, int b){
    /* Any arbitrary weight function will work */
    int dist = (a*a)+(b*b);
    return sqrt(dist);
}

int dijkstras(adjMatrix *adjmatrix, int path[]){
    int matrixArea = adjmatrix->len*adjmatrix->wid;
    double *d = (double *)calloc(sizeof(double), matrixArea);
    int *predPath = (int *)calloc(sizeof(int), matrixArea);
    int pathLength = 0;
    heapNode *end = NULL;
    Heap *h = newHeap(matrixArea);
    h = heapInsert(h, newHeapNode(0,adjmatrix->len,0));
    h->heap[0].neighbours[3] = -1;
    h->heap[0].neighbours[0] = -1;

    for(int i = 0; i < adjmatrix->wid; i++){
        for(int j = 0; j < adjmatrix->len; j++){
            if(i != 0 || j != 0){
                heapNode *newNode = newHeapNode(i+j*adjmatrix->len, adjmatrix->len, -1);
                h = heapInsert(h, newNode);
                if(j == 0){
                    newNode->neighbours[0] = -1;
                }
                if(j == 2){
                    newNode->neighbours[2] = -1;
                }
                if(i == 0){
                    newNode->neighbours[3] = -1;
                }
                if(i == 2){
                    newNode->neighbours[1] = -1;
                }
            }
        }
    }
    
    for(int i = 0; i < 9; i++){
        d[i] = -1;
    }

    d[0] = 0;
    while(h->currSize > 0){
        heapNode *v = extractMin(h);
        
        for(int i = 0; i < 4; i++){
            if(v->neighbours[i] > 0 && v->neighbours[i] != v->pred){
                int distToNext = d[v->index] + weight(v->index, v->neighbours[i]);
                if(distToNext < d[v->neighbours[i]] || d[v->neighbours[i]] == -1){
                    
                    decreasePrio(h, v->neighbours[i], distToNext);
                    d[v->neighbours[i]] = distToNext;
                    h->heap[h->pos[v->neighbours[i]]].pred = v->num;
                }
            }
            if(v->neighbours[i] == (adjmatrix->len-1)+(adjmatrix->wid-1)*adjmatrix->len){
                end = &h->heap[h->pos[v->neighbours[i]]];
            }
        }
    }
    /* heapNode *end = &h->heap[h->pos[8]];
    int L = 0;
    while(end->pred != -1){
        path[L] = end->pred;
        end
    } */
    while(end->pred != -1){
        predPath[pathLength] = end->pred;
        pathLength++;
        end = &h->heap[h->pos[end->pred]];
    }

    return d[(adjmatrix->len-1)+(adjmatrix->wid-1)*adjmatrix->len];
}