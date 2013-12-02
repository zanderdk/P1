/**
 * @brief Contains information about which preferences where whosen
 * @details [long description]
 *
 * @param value [description]
 * @param vertex [description]
 */
typedef struct RoutePreferences {
    unsigned int useElevators;
    unsigned int useStairs;
} RoutePreferences;


/**
 * @brief Sets g value to an vertex
 * @details [long description]
 *
 * @param value [description]
 * @param vertex [description]
 */
void setGValue(int value, Vertex *vertex);

/**
 * @brief Sets h value to an vertex
 * @details [long description]
 *
 * @param value [description]
 * @param vertex [description]
 */
void setHValue(int value, Vertex *vertex);

/**
 * @brief Sets f value to an vertex
 * @details [long description]
 *
 * @param value [description]
 * @param vertex [description]
 */
void setFValue(int value, Vertex *vertex);

/**
 * @brief Sets parent to a vertex
 * @details [long description]
 *
 * @param child The child that gets a parent
 * @param parent The parent to be set
 */
void setParentVertex(Vertex *child, Vertex *parent);


/**
 * @brief Adds a vertex to the closed list
 * @details [long description]
 *
 * @param closedList The closed list containing already visited vertices.
 * @param v The vertex to add to closedList.
 */
void addToClosedList(Vertex **closedList, Vertex *v);

/**
 * @brief Adds a vertex to the open list
 * @details [long description]
 *
 * @param openList The open list containing already visited vertices.
 * @param v The vertex to add to openList.
 */
void addToOpenList(Vertex **openList, Vertex *v);

/**
 * @brief Removes a vertex from a closed list
 * @details [long description]
 *
 * @param closedList [description]
 * @param v [description]
 */
void RemoveFromClosedList(Vertex **closedList, Vertex *v);

/**
 * @brief Removes a vertex from an open list
 * @details [long description]
 *
 * @param openList [description]
 * @param v [description]
 */
void RemoveFromOpenList(Vertex **openList, Vertex *v);

/**
 * @brief Is the vertex in closed list?
 * @details [long description]
 *
 * @param closedList [description]
 * @param v [description]
 * @return 0 if vertex is not in list.
 * 1 if vertex is in list.
 */
int isInClosedList(Vertex **closedList, Vertex *v);

/**
 * @brief Is the vertex in open list?
 * @details [long description]
 *
 * @param openList [description]
 * @param v [description]
 * @return 0 if vertex is not in list.
 * 1 if vertex is in list.
 */
int isInOpenList(Vertex **openList, Vertex *v);

/**
 * @brief Finds the most optimal route from start to dest vertices
 * based on route preferences.
 * @details [long description]
 *
 * @param g [description]
 * @param start [description]
 * @param dest [description]
 * @param RoutePreferences [description]
 */
void findOptimalRoute(Graph *g, Vertex *start, Vertex *dest,
                      RoutePreferences *rp);

/**
 * @brief Calculates h value using euclidean distance
 * of v1 and v2.
 * @details [long description]
 *
 * @param v1 [description]
 * @param v2 [description]
 * @return h value from v1 to v2
 */
int calcHValue(Vertex *v1, Vertex *v2);

/**
 * @brief Adds all the neighbour vertices of v to the array.
 * neighbours must be allocated big enough to hold all vertices.
 *
 * @param v [description]
 * @param neighbours [description]
 */
void getNeighbourVertices(Vertex *v, Vertex **neighbours);