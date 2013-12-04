#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "testGraph.h"

int Contains(unsigned int id, unsigned int *k, unsigned int V) {
    int i;
    for (i = 0; i < V; ++i) {
        if (k[i] == id) {
            return 1;
        }
    }
    return 0;
}

int smallestT(unsigned int *t, unsigned int *p, unsigned int V) {
    int i;
    int minValue = INT_MAX;
    int minIndex;
    for (i = 0; i < V; ++i) {
        if (t[i] < minValue && p[i] == 0) {
            minIndex = i;
        }
    }
    return minIndex;
}

void Dijkstra(Graph *graph, int source, int dest) {
    unsigned int V = graph->numOfVertices;

    unsigned int p[V];
    unsigned int t[V];
    unsigned int k[V];

    int i, j = 0;
    for (i = 0; i < V; ++i) {
        p[i] = 0;
        t[i] = 4000;
        k[i] = INT_MAX;
    }

    unsigned int u = source;
    p[u] = 0;

    while (p[dest] == 0) {
        Vertex *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            unsigned int buf = p[u] + pCrawl->weight;
            if (buf < t[pCrawl->id] && p[pCrawl->id] == 0) {
                t[pCrawl->id] = buf;
            }
            pCrawl = pCrawl->next;
        }
        u = smallestT(t, p, V);
        p[u] = t[u];
    }
    u = dest;
    while (p[u] != 0) {
        Vertex *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            if (!Contains(pCrawl->id, k, V) && p[u] == p[pCrawl->id] + pCrawl->weight) {
                u = pCrawl->id;
                k[j++] = u;
                break;
            }
            pCrawl = pCrawl->next;
        }
    }
    printf("\n Cost from %d to %d == %d", source, dest, p[dest]);
    printf(" via Path = %d ", dest);
    unsigned int res = k[j];
    while (res != source) {
        res = k[j];
        j--;
        printf("<- %d ", res);
    }
}

/*
void PreCalcPaths(Floor *graph) {

}

int isRouteable(Vertex *v1, Vertex *v2) {

}

Path getPath(Vertex *v1, Vertex *v2) {

}

void addPath(Vertex *v1, Vertex *v2, Vertex *list, int weight) {

}*/