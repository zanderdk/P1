/**
return 0 for no valid route.
return 1 for a route can be found using one floor
return 2 for a route can be found crossing floors
*/

int validate(char *str1, char *str2, Vertex **vp1, Vertex **vp2, Graph *graph) {
    *vp1 = GetVertexFromId(str1, graph);
    *vp2 = GetVertexFromId(str2, graph);

    if ((*vp1) == NULL || (*vp2) == NULL)
        return 0;

    int max = graph->numOfFloors;
    if ((*vp1)->floorId <= max || (*vp2)->floorId <= max) {
        if ((*vp1)->floorId == (*vp2)->floorId)
            return 1;
        else
            return 2;
    }

    return 0;
}

void printPath(Path *path) {
    int i;
    printf("number of vertices: %d, total weight: %d \n",
           path->numVertices,
           path->weight);

    for (i = 0; i < path->numVertices; i++) {
        printf("%d \n", path->pathVerticeIds[i]);
    }
}

Path *recreconstruct(Path *p1, Path *p2, Path *p3, int t) {
    int ids;

    if (t == 1)
        ids = p1->numVertices + p2->numVertices + p3->numVertices;
    else if (t == 2)
        ids = p2->numVertices + p3->numVertices;
    else if (t == 3)
        ids = p2->numVertices;
    else
        ids = p1->numVertices + p2->numVertices;

    int size = ids * sizeof(int) + sizeof(Path);
    Path *ret = malloc(size);
    unsigned int *weights = (unsigned int *)(ret + 1);

    int i;
    int count = 0;
    int tcount = 0;

    ret->numVertices = ids;

    if (t == 3)
        ret->targetId = p2->targetId;
    else if (t == 2)
        ret->targetId = p3->targetId;
    else
        ret->targetId = p1->targetId;

    if (t == 1)
        ret->weight = p1->weight + p2->weight + p3->weight;
    else if (t == 2)
        ret->weight = p2->weight + p3->weight;
    else if (t == 3)
        ret->weight = p2->weight;
    else
        ret->weight = p1->weight + p2->weight;

    ret->pathVerticeIds = weights;

    if (t != 2 && t != 3)
        for (i = 0; i < p1->numVertices; i++) {
            weights[i] = p1->pathVerticeIds[i];
            count++;
        }

    tcount = count;

    for (i = 0; i < p2->numVertices; i++) {
        weights[tcount + i] = p2->pathVerticeIds[i];
        count++;
    }

    tcount = count;

    if (t != 0 && t != 3) {
        for (i = 0; i < p3->numVertices; i++) {
            weights[tcount + i] = p3->pathVerticeIds[i];
            count++;
        }
    }

    if (t != 2 && t != 3)
        free(p1);

    if (t != 3 && t != 0)
        free(p3);




    return ret;
}

Path *findOptimalPath(Vertex *scr, Vertex *dst, int mode, int sameFloor,
                      Graph *graph, SourcePaths *srcPath, int paths) {
    Path *buf;
    Vertex *bufVp;
    SourcePaths *sp;
    Path *Lbuf;

    int i, j;
    int state = 1;

    int exits;
    unsigned currentCost;

    unsigned int record = (unsigned int)(-1);
    Path *recPath1;
    Path *recPath2;
    Path *recPath3;


    if (sameFloor == 1) {
        int floor = scr->floorId - 1;
        return AStar(scr, dst, graph->floors[floor].amountOfVertecies);
    } else if (sameFloor == 2) {
        int startFloor = scr->floorId - 1;
        int endFloor = dst->floorId - 1;
        //printf("%d \n", endFloor);


        for (i = 0; i < paths; i++) {
            sp = &srcPath[i];
            if (GetFloor(sp->sourceId) - 1 == startFloor) {

                exits = sp->sourceId;
                bufVp = GetVertexFromIdInt(exits, graph);

                if (scr->type == 1) {
                    buf = AStar(scr, bufVp, graph->floors[startFloor].amountOfVertecies);
                    currentCost = buf->weight;
                } else
                    state = 2;


                for (j = 0; j < sp->numPaths; j++) {

                    if (scr->type > 1 && dst->type > 1)
                        state = 3;


                    if ((GetFloor(sp->paths[j].targetId) - 1) == endFloor) {

                        Vertex *source = GetVertexFromIdInt(sp->paths[j].targetId, graph);

                        if (source->vertexId == dst->vertexId && state != 3) {
                            recPath1 = buf;
                            recPath2 = &(sp->paths[j]);
                            recPath3 = NULL;
                            return recreconstruct(recPath1, recPath2, recPath3, 0);
                        }

                        if (state != 3)
                            Lbuf = AStar(source, dst, graph->floors[endFloor].amountOfVertecies);

                        currentCost += Lbuf->weight;
                        currentCost += sp->paths[j].weight;

                        if (currentCost < record) {
                            recPath1 = buf;
                            recPath2 = &(sp->paths[j]);
                            recPath3 = Lbuf;
                        }
                    }
                }

            }
        }

    }

    return recreconstruct(recPath1, recPath2, recPath3, state);

}