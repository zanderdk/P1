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


/**
 * @brief Returns the quickest Path from start to destination.
 * @details This should only be called when start and dest is on same floor.
 *
 * @param start This is a pointer to a vertex that is the start
 * @param dest This is a pointer to a vertex that is the destination
 * @param path A pointer to a Path. This Path gets populated with ids in path
                and the weight
 * @return Returns the path calculated through a Path
 */
Path *AStar(Vertex *start, Vertex *dest, int numVertices);


Path *ReconstructPath(WorkVertex *end, int numVertices);

/**
 * @brief Gets all the nabors of wv
 * @details [long description]
 *
 * @param wv the WorkVertex to get the nabors of
 * @param workVertices an array of all pointers to workVertices created
 * @param numVertices the number of elements of workVertices array
 * @param outNeighborWorkVertex array of pointers to workVertices.
                                This array gets filled with all neighbours
                                of wv.
 * @return the number of nabors of wv.
 */
int GetNeighbors(WorkVertex *wv, WorkVertex **workVertices, int numVertices,
                 WorkVertex **outNeighborWorkVertex);

/**
 * @brief Creates a workVertex pointer based on a Vertex pointer
 * @details [long description]
 *
 * @param src Which Vertex pointer to base the to be created workVertex

 * @return a pointer to the created workVertex
 */
WorkVertex *CreateWorkVertex(Vertex *src);

/**
 * @brief sets in which set a given WorkVertex is in.
 * @details [long description]
 *
 * @param value mode to set. Can be 0 (no set), 1 (closed set), 2 (open set)
 * @param wv the WorkVertex to set the which set
 */
void SetSetMode(int value, WorkVertex *wv);

/**
 * @brief Sets the g value of a workVertex
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
 * @param wv the WorkVertex to set a g value to
 * @return return g value of wv
 */
unsigned int GetGValue(WorkVertex *wv);

/**
 * @brief Calculates the euclidean "ordinary" distance between two vertices. This only considers x and y coordinates.
 * @details [long description]
 *
 * @param src an vertex pointer of a source
 * @param goal an vertex pointer of a goal

 * @return The H value from src to goal
 */
double DistBetween(Vertex *src, Vertex *goal);

/**
 * @brief Sets the h value of a WorkVertex
 * @details [long description]
 *
 * @param value the value to set
 * @param wv the WorkVertex to set a h value to
 */
void SetHValue(double value, WorkVertex *wv);

/**
 * @brief Returns the h value of a vertex
 * @details [long description]
 *
 * @param wv the WorkVertex to get h value from
 * @return [description]
 */
double GetHValue(WorkVertex *wv);

/**
 * @brief Calculates the f value of a vertex
 * @details [long description]
 *
 * @param src the WorkVertex to get h and g values from
 * @param goal
 * @return [description]
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
 * @brief returns wether a wv is in workVertices
 * @details [long description]
 *
 * @param wv the WorkVertex to look for
 * @param workVertices an array of all pointers to workVertices created
 * @param numVertices the number of elements of workVertices array
 * @return 0 if wv is not in workVertices.
            1 if wv is in workVertices
 */
int IsInWorkVertices(WorkVertex *wv, WorkVertex **workVertices, int numVertices);

/**
 * @brief Finds the WorkVertex in workVertices with the lowest f value in open set
 * @details [long description]
 *
 * @param workVertices an array of all pointers to workVertices created
 * @param numVertices the number of elements of workVertices array
 * @return the workVertex with the lowest f value in open set
 */
WorkVertex *GetVertexLowestFOpenSet(WorkVertex **workVertices, int numVertices);

/**
 * @brief Add wv to workVertices
 * @details [long description]
 *
 * @param wv the WorkVertex to add to workVertices
 * @param workVertices an array of all pointers to workVertices created
 * @param numVertices the number of elements of workVertices array
 */
void AddToWorkVertices(WorkVertex *wv, WorkVertex **workVertices, int numVertices);

/**
 * @brief gets a weight from a neighbor
 * @details [long description]
 *
 * @param src [description]
 * @param targetNeighbor [description]
 * @param workVertices [description]
 * @param numVertices [description]
 * @param outNeighborWorkVertex [description]
 * @return [description]
 */
unsigned int GetWeight(WorkVertex *src, WorkVertex *targetNeighbor);

/**
 * @brief returns the number of vertices in a given set
 * @details [long description]
 *
 * @param setMode which set to search in. C
 * an be 0 means WorkVertex is not in a set.
 * 1 means WorkVertex is in closed set.
 * 2 means WorkVertex is in open set.
 *
 * @param workVertices an array of all pointers to workVertices created
 * @param numVertices the number of elements of workVertices array
 * @return the number of WorkVertices in the given set
 */
int GetVerticesInSet(int setMode, WorkVertex **workVertices, int numVertices);
