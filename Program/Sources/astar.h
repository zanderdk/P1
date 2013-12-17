typedef struct WorkVertex WorkVertex;

struct WorkVertex {
    unsigned int g;
    double f;

    /**
     * 0 means WorkVertex is not in a set.
     * 1 means WorkVertex is in closed set.
     * 2 means WorkVertex is in open set.
     */
    int setMode;

    /**
     * A pointer to the vertex this WorkVertex is based upon.
     * The originVertex is used to read values like edges, ids etc.
     */
    Vertex *originVertex;
    /**
     * Used in the A* algorithm for backtracking the shortest route.
     * Parent is the vertex, that gives originVertex the lowest f value.
     */
    WorkVertex *parentVertex;
};

Path *AStar(Vertex *start, Vertex *dest, int numVertices);

void CleanUp(WorkVertex **workVertices, int numVertices);

Path *ReconstructPath(WorkVertex *end, int numVertices);

int GetNeighbors(WorkVertex *wv, WorkVertex **workVertices, int numVertices,
                 WorkVertex **outNeighborWorkVertex, int *createdWorkVertices);

WorkVertex *CreateWorkVertex(Vertex *src, int *createdWorkVertices);

void SetSetMode(int value, WorkVertex *wv);

void SetGValue(unsigned int value, WorkVertex *wv);

unsigned int GetGValue(WorkVertex *wv);

double DistBetween(Vertex *src, Vertex *goal);

double CalcFValue(WorkVertex *src, Vertex *goal);

void SetFValue(double f, WorkVertex *wv);

double GetFValue(WorkVertex *wv);

void SetParentVertex(WorkVertex *child, WorkVertex *parent);

int IsInWorkVertices(WorkVertex *wv, WorkVertex **workVertices, int numVertices);

WorkVertex *GetVertexLowestFOpenSet(WorkVertex **workVertices, int numVertices);

void AddToWorkVertices(WorkVertex *wv, WorkVertex **workVertices, int numVertices);

unsigned int GetWeight(WorkVertex *src, WorkVertex *targetNeighbor);

WorkVertex *GetFromWorkVertices(int targetId, WorkVertex **workVertices,
                                int numVertices);

int GetVerticesInSet(int setMode, WorkVertex **workVertices, int numVertices);
