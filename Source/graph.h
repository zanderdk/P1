#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Structure containing a floor
 *
 */
typedef struct Floor {
    /**
     * The floor number.
     * Two different floors, cannot have the same floor number
     */
    unsigned int floor;

    /**
     * A pointer to a vertex that is on the floor.
     */
    Vertex *vp;

    /**
     * A pointer to another floor.
     */
    Floor *fp;
} Floor;


/**
 * @brief A vertex in a graph
 *
 */
typedef struct Vertex {
    /**
     * An id of a vertex. Two vertices cannot have the same id.
     */
    unsigned int id;

    /**
     * Local x coordinate in the hospital.
     */
    unsigned int x;

    /**
     * Local y coordinate in the hospital.
     */
    unsigned int y;

    /**
     * Describes which type the vertex is.
     * For example could 1 be stairs, 2 be an elevator
     */
    unsigned int type;

    /**
     * Which floor id the vertex is on.
     */
    unsigned int floor;

    /**
     * A pointer to an EdgePointer.
     */
    EdgePointer *ep;

    /**
     * A pointer to the next vertex.
     * This could be on the same floor,
     * or on another floor so the floor id must be checked.
     */
    Vertex *vp;

    /**
     * Used in A* algorithm.
     * parent is the vertex where this struct vertex came from
     */
    Vertex *parent;
} Vertex;

/**
 * @brief An EdgePointer points to an edge
 * and to the next EdgePointer in the linked list
 *
 */
typedef struct EdgePointer {
    /**
     * A pointer to a edge
     */
    Edge *edge;

    /**
     * A pointer to the next EdgePointer. In this way it is a linked list.
     */
    EdgePointer *next;
} EdgePointer;

/**
 * @brief An edge is connecting two vertices
 *
 */
typedef struct Edge {
    /**
    * An id of an edge. Two edges cannot have the same id.
    */
    unsigned int id;

    /**
     * The weight of this edge. Could be meters or seconds.
     */
    unsigned int weight;

    /**
     * First vertex this edge connects.
     */
    Vertex *vertex1;

    /**
     * Second vertex this edge connects.
     */
    Vertex *vertex2;
} Edge;

