#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "XML.h"
#include "graph.h"

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("demo2.xml", "r");
	Floor *graph = readXml(fp);
	fclose(fp);

	Vertex *t = GetVertexFromId("10013", graph);

	printf("%d \n", CountVertices(1, graph));

	return 0;
}