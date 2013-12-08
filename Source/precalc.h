
/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param graph [description]
 */
//void PreCalcPaths(Floor *graph);

/**
 * @brief
 * @details [long description]
 *
 * @param v1 [description]
 * @param v2 [description]
 * @return [description]
 */
//int isRouteable(Vertex *v1, Vertex *v2);

/**
 * @brief Return the optimal path from pre calculated paths.
 *
 * @param v1 Vertex 1
 * @param v2 Vertex 2
 * @return Returns a path struct
 */
//Path getPath(Vertex *v1, Vertex *v2);

/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param v1 [description]
 * @param v2 [description]
 * @param list [description]
 * @param weight [description]
 */
//void addPath(Vertex *v1, Vertex *v2, Vertex *list, int weight);


int Contains(unsigned int id, unsigned int *k, unsigned int V);

int smallestT(unsigned int *t, unsigned int *p, unsigned int V);

void Dijkstra(Graph *graph, int source, int dest);