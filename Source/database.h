/**
 * @brief [brief description]
 * @details [long description]
 *
 * @param  [description]
 */
void calcRoutesBetweenFloors(Graph *graph);

/**
 * @brief 
 * @details [long description]
 * 
 * @param v1 [description]
 * @param v2 [description]
 * @return [description]
 */
int isRouteable(Vertex *v1, Vertex *v2);

/**
 * @brief Returns optimal path.
 * @details Return the optimal path from pre calculated textfile.
 *
 *
 * @return Returns a path struct, from v1 and v2.
 */
Path getPath(Vertex *v1, Vertex *v2);