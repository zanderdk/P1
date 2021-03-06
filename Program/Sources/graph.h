#define NO_MODE 0
#define NO_STAIRS 1
#define NO_ELEVATORS 2
#define ID_CHAR_SIZE 10

typedef struct Floor Floor;
typedef struct Vertex Vertex;
typedef struct EdgePointer EdgePointer;
typedef struct Edge Edge;
typedef struct Path Path;
typedef struct SourcePaths SourcePaths;
typedef struct Graph Graph;

struct Graph {
    unsigned int numOfVertices;
    unsigned int numOfFloors;
    Floor *floors;
};

/*
ids:
1 vertex
2 stair vertex
3 elevator vertex
4 exit vertex (div exit)
5 Edge
*/

/**
 * @brief Structure containing a floor
 *
 */
struct Floor {
    /**
     * Floor identification number.
     * Two floors cannot have the same ID.
     */
    unsigned int floorId;

    unsigned int amountOfVertecies;
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
     * The ID of the vertex. Two vertices cannot have the same id.
     */
    unsigned int vertexId;

    /**
     * Local x coordinate.
     */
    unsigned int x;

    /**
     * Local y coordinate.
     */
    unsigned int y;

    /**
     * Describes the vertex' type ie. 2 for stairs, 3 for elevator etc.
     */
    unsigned int type;

    /**
     * ID of the floor the vertex is located on.
     */
    unsigned int floorId;

    /**
     * A pointer to the head of the linked list containing pointers to all edges connected to the vertice.
     */
    EdgePointer *ep;

    /**
     * A pointer to the next vertex.
     * Only used on startup.
     */
    Vertex *nextVp;
};

/**
 * @brief Used for creating a linked list of Edge *.
 * An EdgePointer points to an edge and to the next EdgePointer in the linked list.
 * Is NULL on end of list.
 */
struct EdgePointer {
    /**
     * A pointer to an edge
     */
    Edge *edge;

    /**
     * A pointer to the next EdgePointer.
     */
    EdgePointer *nextEp;
};

/**
 * @brief An edge connects two vertices.
 */
struct Edge {
    /**
     * The ID of the edge. Two edges cannot have the same ID.
     */
    unsigned int edgeId;
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
    int targetId;
    unsigned int weight;
    unsigned int *pathVerticeIds;
    int numVertices;
};

struct SourcePaths {
    Path *paths;
    unsigned int numPaths;
    int sourceId;
};

Vertex *GetVertexFromId(char *idStr, Graph *graph);
Vertex *GetVertexFromIdInt(int id, Graph *graph);
int CountVertices(int floorId, Graph *graph);
int GetFloor(int vertedId);
Vertex *NextVertex(Vertex *vp, int id);
