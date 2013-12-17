struct Vertex {
    unsigned int vertexId;
    unsigned int x;
    unsigned int y;
    unsigned int type;
    unsigned int floorId;
    EdgePointer *ep;
    Vertex *nextVp;
};
