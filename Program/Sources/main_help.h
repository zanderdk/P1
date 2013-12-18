int validate(char *str1, char *str2, Vertex **vp1, Vertex **vp2, Graph *graph);
void printPath(Path *path);
Path *recreconstruct(Path *p1, Path *p2, Path *p3, int t);
Path *findOptimalPath(Vertex *scr, Vertex *dst, int mode, int sameFloor,
                      Graph *graph, SourcePaths *srcPath, int paths);