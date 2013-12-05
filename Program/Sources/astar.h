#include "graph.h"

typedef struct WorkVertex WorkVertex;

struct WorkVertex {
    unsigned int g;
    double h;
    double f;

    /**
     * 0 means WorkVertex is not in a set.
     * 1 means WorkVertex is in closed set.
     * 2 means WorkVertex is in open set.
     */
    int setMode;

    /**
     * A pointer to the vertex this WorkVertex corresponds to.
     * The originVertex is used to read values like edges, ids etc.
     */
    Vertex *originVertex;
    /**
     * Used in the A* algorithm for backtracking the shortest route.
     * Parent is the node before the current in the set which specifies the shortest route to the origin.
     */
    WorkVertex *parentVertex;
};

void setSetMode(int value, WorkVertex *wv);

/**
 * @brief Sets the g value of a vertex
 * @details [long description]
 *
 * @param value [description]
 * @param vertex [description]
 */
void SetGValue(unsigned int value, WorkVertex *wv);

/**
 * @brief Returns the g value of a vertex
 * @details [long description]
 *
 * @param vertex [description]
 */
unsigned int GetGValue(WorkVertex *wv);

/**
 * @brief Calculates the euclidean "ordinary" distance between two vertices. This only considers x and y coordinates.
 * @details [long description]
 *
 * @param stc [description]
 * @param goal [description]
 * @return The H value from WorkVertex to Goal
 */
double CalcHValue(Vertex *src, Vertex *goal);

/**
 * @brief Sets the h value of a vertex
 * @details [long description]
 *
 * @param value [description]
 * @param vertex [description]
 */
void SetHValue(double value, WorkVertex *wv);

/**
 * @brief Returns the h value of a vertex
 * @details [long description]
 *
 * @param vertex [description]
 */
double GetHValue(WorkVertex *wv);

/**
 * @brief Calculates the f value of a vertex
 * @details This function will calculate the f value of a vertex from the g and h value.
 * It is meant to only be called in the SetGValue function.
 *
 * @param value [description]
 * @param vertex [description]
 */
double CalcFValue(WorkVertex *src, Vertex *goal);

/**
 * @brief Sets the f value of a vertex
 * @details [long description]
 *
 * @param value The value to set
 * @param vertex The vertex to set the value for
 */
void SetFValue(double f, WorkVertex *wv);

/**
 * @brief Returns the f value of a vertex
 * @details [long description]
 *
 * @param vertex [description]
 */
double GetFValue(WorkVertex *wv);

/**
 * @brief Sets the parent of a vertex
 * @details Sets the parent of a vertex as a step in calculating the shortest route.
 * The parent will later be used for backtracking the shortest route.
 *
 * @param child The child that gets a parent
 * @param parent The parent to be set
 */
void SetParentVertex(WorkVertex *child, WorkVertex *parent);

/**
 * @brief Finds the most optimal route from start to dest vertices on the same floor
 * based on mode
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
void GetNeighbourVertices(WorkVertex *v, Vertex **neighbours);

Path *reconstruct_path(unsigned int verticesInPath, WorkVertex *end,
                       WorkVertex **workVertices, int numVertices,
                       WorkVertex **outNeighborWorkVertex);

WorkVertex *createWorkVertex(Vertex *src);

WorkVertex *getVertexLowestFOpenSet(WorkVertex **workVertices, int numVertices);

int getNeighbors(WorkVertex *wv, WorkVertex **workVertices, int numVertices,
                 WorkVertex **outNeighborWorkVertex);

unsigned int getWeight(WorkVertex *src, WorkVertex *targetNeighbor,
                       WorkVertex **workVertices,
                       int numVertices, WorkVertex **outNeighborWorkVertex);

int getVerticesInSet(int setMode, WorkVertex **workVertices, int numVertices);