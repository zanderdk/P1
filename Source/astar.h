#include "graph.h"

/**
 * @brief Sets the g value of a vertex
 * @details [long description]
 *
 * @param value [description]
 * @param vertex [description]
 */
void SetGValue(int value, Vertex *vertex);

/**
 * @brief Returns the g value of a vertex
 * @details [long description]
 *
 * @param vertex [description]
 */
int GetGValue(Vertex *vertex);

/**
 * @brief Calculates the h value
 * @details [long description]
 *
 * @param vertex [description]
 * @param goal [description]
 * @param mode Sets the mode to be used ie. 0 for normal mode
 * @return h value from v1 to v2
 */
void CalcHValue(Vertex *vertex, Vertex *goal, int mode);

/**
 * @brief Sets the h value of a vertex
 * @details [long description]
 *
 * @param value [description]
 * @param vertex [description]
 */
void SetHValue(int value, Vertex *vertex);

/**
 * @brief Returns the h value of a vertex
 * @details [long description]
 *
 * @param vertex [description]
 */
int GetHValue(Vertex *vertex);

/**
 * @brief Calculates the f value of a vertex
 * @details This function will calculate the f value of a vertex from the g and h value.
 * It is meant to only be called in the SetGValue function.
 *
 * @param value [description]
 * @param vertex [description]
 */
void CalcFValue(Vertex *vertex);

/**
 * @brief Sets the f value of a vertex
 * @details [long description]
 *
 * @param value The value to set
 * @param vertex The vertex to set the value for
 */
int SetFValue(int value, Vertex *vertex);

/**
 * @brief Returns the f value of a vertex
 * @details [long description]
 *
 * @param vertex [description]
 */
int GetFValue(Vertex *vertex);

/**
 * @brief Sets the parent of a vertex
 * @details Sets the parent of a vertex as a step in calculating the shortest route.
 * The parent will later be used for backtracking the shortest route.
 *
 * @param child The child that gets a parent
 * @param parent The parent to be set
 */
void SetParentVertex(Vertex *child, Vertex *parent);

/**
 * @brief Adds a vertex to the closed list
 * @details [long description]
 *
 * @param closedList The closed list containing already visited vertices.
 * @param v The vertex to add to closedList.
 */
void AddToClosedList(Vertex **closedList, Vertex *v);

/**
 * @brief Adds a vertex to the open list
 * @details [long description]
 *
 * @param openList The open list containing already visited vertices.
 * @param v The vertex to add to openList.
 */
void AddToOpenList(Vertex **openList, Vertex *v);

/**
 * @brief Removes a vertex from the open list
 * @details [long description]
 *
 * @param openList [description]
 * @param v [description]
 */
void RemoveFromOpenList(Vertex **openList, Vertex *v);

/**
 * @brief Is the vertex in closed list
 * @details [long description]
 *
 * @param closedList [description]
 * @param v [description]
 * @return 0 if vertex is not in list.
 * 1 if vertex is in list.
 */
int IsInClosedList(Vertex **closedList, Vertex *v);

/**
 * @brief Is the vertex in open list
 * @details [long description]
 *
 * @param openList [description]
 * @param v [description]
 * @return 0 if vertex is not in list.
 * 1 if vertex is in list.
 */
int IsInOpenList(Vertex **openList, Vertex *v);

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
void findOptimalRoute(Floor *f, Vertex *start, Vertex *dest,
                      int mode);

/**
 * @brief Adds all the neighbour vertices of v to the array.
 * neighbours must be allocated big enough to hold all vertices.
 *
 * @param v [description]
 * @param neighbours [description]
 */
void GetNeighbourVertices(Vertex *v, Vertex **neighbours);

/**
 * @brief Calculates the "ordinary" distance between two vertices. This only considers x and y coordinates.
 *
 * @param v1 Pointer to a vertex
 * @param v2 Pointer to a vertex
 * @return Ordinary distance between v1 and v2 as a double.
 */
double DistanceEuclid(Vertex *v1, Vertex *v2);