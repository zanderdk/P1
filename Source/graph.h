typedef struct Floor Floor;
typedef struct Vertex Vertex;
typedef struct EdgePointer EdgePointer;
typedef struct Edge Edge;
typedef struct Path Path;

/**
 * @brief Structure containing a floor
 *
 */
struct Floor {
    /**
     * The floor number.
     * Two different floors, cannot have the same floor number
     */
    unsigned int floorId;
    /**
     * A pointer to the head of the linked list contaning all vertices on the floor. 
     * Pointer is NULL on end of floor.
     */
    Vertex *vp;
};


/**
 * @brief A vertex in a graph
 *
 */
struct Vertex {
    /**
     * An id of a vertex. Two vertices cannot have the same id.
     */
    unsigned int vertexId;

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
    unsigned int floorId;

    /**
     * A pointer to an EdgePointer.
     */
    EdgePointer *ep;

    /**
     * A pointer to the next vertex.
     * This could be on the same floor,
     * or on another floor so the floor id must be checked.
     */
    Vertex *nextVp;

    /**
     * Used in A* algorithm.
     * parent is the vertex where this struct vertex came from
     */
    Vertex *parent;
};

/**
 * @brief An EdgePointer points to an edge
 * and to the next EdgePointer in the linked list
 *
 */
struct EdgePointer {
    /**
     * A pointer to a edge
     */
    Edge *edge;

    /**
     * A pointer to the next EdgePointer. In this way it is a linked list.
     */
    EdgePointer *nextEp;
};

/**
 * @brief An edge is connecting two vertices
 *
 */
struct Edge {
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
};

struct Path {
  unsigned int weight;
  unsigned int *pathVertexIds;
};