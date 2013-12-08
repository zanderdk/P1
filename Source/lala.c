#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "testGraph.h"

int SmallestDist(unsigned int *dist, unsigned int *visited, unsigned int V) {
    int i;
    int minValue = INT_MAX;
    int minIndex;
    for (i = 0; i < V; ++i) {
        if (dist[i] < minValue && visited[i] == 0) {
            minIndex = i;
        }
    }
    return minIndex;
}

int Contains(int *list, unsigned int id,  unsigned int V) {
    int i;
    for (i = 0; i < V; ++i) {
        if (list[i] == id) {
            return 1;
        }
    }
    return 0;
}

void InsertIntoList(int *list, unsigned int id, unsigned int V) {
    int i;
    for (i = 0; i < V ; ++i) {
        if (!Contains(list, id, V) && list[i] == -1)
            list[i] = id;
    }
}

void RemoveFromList(int *list, unsigned int id, unsigned int V) {
    int i;
    for (i = 0; i < V; ++i) {
        if (list[i] == id)
            list[i] = -1;
    }
}

int IsEmpty(int *list, unsigned int V) {
    int i;
    for (i = 0; i < V; ++i) {
        if (list[i] != -1)
            return 0;
    }
    return 1;
}

void PrintList(unsigned int *list, unsigned int V) {
    int i;
    for (i = 0; i < V; ++i ) {
        if (list[i] != 999) {
            printf("<- %u ", list[i]);
        }
    }
}

int Dijkstra(Graph *graph, int sourceId, int targetId, int *pathList) {
    unsigned int V = graph->numOfVertices;

    unsigned int dist[V];
    unsigned int visited[V];
    int previous[V];
    int Q[V];

    int i;
    for (i = 0; i < V; ++i) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = 999;
        Q[i] = -1;
    }

    unsigned int u = sourceId;
    dist[u] = 0;
    InsertIntoList(Q, u, V);

    while (!IsEmpty(Q, V)) {
        u = SmallestDist(dist, visited, V);
        RemoveFromList(Q, u, V);
        visited[u] = 1;

        Vertex *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            unsigned int alt = dist[u] + pCrawl->weight;
            unsigned int v = pCrawl->id;
            if (alt < dist[v]) {
                dist[v] = alt;
                previous[v] = u;
                if (!visited[v])
                    InsertIntoList(Q, v, V);
            }
            pCrawl = pCrawl->next;
        }
    }

    u = targetId;
    int j = 0;
    int reversed[V];
    do {
        u = previous[u];    // Traverse from target to source
        reversed[j] = u;     // Push the vertex into the stack
        j++;
    } while (previous[u] != sourceId);

    i = V;
    for (j = 0; j < V; ++j) {
        pathList[j] = reversed[i];
        i--;
    }

    return dist[targetId];
}