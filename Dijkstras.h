#ifndef __DIJKSTRA_H
#define __DIJKSTRA_H

#include "heapTest.h"

typedef struct adjMatrix{
    int *matrix;
    int len;
    int wid;
}adjMatrix;
double weight(int a, int b);
int dijkstras(adjMatrix *adjmatrix, int path[]);

#endif