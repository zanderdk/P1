#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "XML.h"

Floor *readXml(FILE *fp)
{
	Floor *floors;
	int i = 0;
	char c = 0;
	char buf[8];
	int edgesCount, verticesCount, floorsCount;


	while((c = getc(fp)) != EOF)
	{
		if(c == '<')
			break;
	}
	fscanf(fp, "%6s", buf);
	if(strcmp(buf, "graph"))
	{
		error();
		return NULL;
	}

	readDefaultAtributes(&edgesCount, &verticesCount, &floorsCount, fp);
	unsigned long amountToAlloc = floorsCount * sizeof(Floor) +
		verticesCount * sizeof(Vertex) +	
		edgesCount * sizeof(Edge) + 
		edgesCount * 2 * sizeof(EdgePointer);

	floors = malloc(amountToAlloc);
	memset(floors, 0, amountToAlloc);


	Edge *edges = (Edge *)(floors+floorsCount);
	Vertex *vertices = (Vertex *)(edges+edgesCount); 

	reachChar('>', fp);

	readEdges(fp, edges, edgesCount);
	readvertices(fp, vertices, verticesCount, edges, edgesCount);

	nextElement(buf, fp);

	if(strcmp(buf,"graph"))
		error();

	crawlEdges(&edges, vertices, edgesCount, verticesCount);
	crawVertices(&vertices, verticesCount, &floors);
	crawlFloors(&floors, vertices, floorsCount, verticesCount);

	return floors;
}

void crawlFloors(Floor **floors, Vertex *vertices, int numberOfFloors, int numberOfvertices)
{
	int i, j; 
	for(i = 0; i < numberOfFloors; i++)
	{
		(*floors)[i].floorId = i+1;
		for(j = 0; j < numberOfvertices; j++)
		{
			if((vertices)[j].floorId == i+1){
				((*floors)[i].vp = &(vertices)[j]);
				break;
			}
		}
	}
}


void crawVertices(Vertex **vertices, int last, Floor **floors)
{
	int i;
    int flId;
	for(i = 0; i < last-1; i++){
        flId = (*vertices)[i].floorId-1;
        (*floors)[flId].amountOfVertecies++;

		if(flId == (*vertices)[i+1].floorId-1){
			(*vertices)[i].nextVp = &(*vertices)[i+1];
		}
		else{
			(*vertices)[i].nextVp = NULL; 
        }
	}

    flId = (*vertices)[i].floorId-1;
    (*floors)[flId].amountOfVertecies++;

	(*vertices)[last-1].nextVp = NULL;
	getFloorAndtype((*vertices)[last-1].vertexId,&(*vertices)[last-1].floorId , &(*vertices)[last-1].type);	
}

void getFloorAndtype(int id, int *floor, int *type)
{
	char str[11]; //int max char size + \0.
	char floorStr[4]; //max floor id size + \0.
	memset(str, 0, 11);
	sprintf(str, "%d", id);

	*type = str[0] - '0';
	strncpy(floorStr, &str[1], 3);
	floorStr[3] = 0;
	sscanf(floorStr, "%d", floor);
}

void crawlEdges(Edge **edges, Vertex *vertices, int numberOfEdges, int numberOfvertices)
{
	int i, j, k;
	long vId1, vId2;

	for(i = 0; i < numberOfEdges; i++)
	{
		k = 0;
		vId1 = (long)(*edges)[i].vertex1;
		vId2 = (long)(*edges)[i].vertex2;
		
		for(j = 0; j < numberOfvertices; j++)
		{
			if((vertices)[j].vertexId == (int)vId1){
				(*edges)[i].vertex1 = &(vertices)[j];
				k++;
			}
			if((vertices)[j].vertexId == (int)vId2){
				(*edges)[i].vertex2 = &(vertices)[j];
				k++;
			}

			if(k == 2)
				break;	
		}

	}
}

void readvertices(FILE *fp, Vertex *vertices, int numberOfvertices, Edge *ep, int numberOfEdges) 
{
	char buf[16];
	memset(buf, 0, 16);
	nextElement(buf, fp);
	int i;
	
	EdgePointer *EdgePointerStart = (EdgePointer *)(vertices+numberOfvertices);

	if(strcmp(buf,"vertices"))
		error();

	for(i = 0; i < numberOfvertices; i++)
	{
		vertices[i] = readVertex(fp, ep, numberOfEdges, EdgePointerStart);
	}

	nextElement(buf, fp);

}

Vertex readVertex(FILE *fp, Edge *ep, int numberOfEdges,  EdgePointer *EdgePointerStart)
{
	static EdgePointerCount = 0;
	Vertex v;
	memset(&v, 0, sizeof(v));
	unsigned int value, i;
	char buf[128];
	memset(buf, 0, 128);

	nextElement(buf, fp);

	if(strcmp(buf,"vertex"))
		error();

	v.vertexId = nextElementValue(buf, fp);
	memset(buf, 0 , 128);

	nextElement(buf, fp);

	if(strcmp(buf,"coord"))
		error();

	v.x = nextElementValue(buf, fp);
	v.y = nextElementValue(buf, fp);

	nextElement(buf, fp);


	memset(buf, 0, 128);
	nextElement(buf, fp);

	if(strcmp(buf,"edges"))
		error();	

	while(1){
		memset(buf, 0, 128);
		value = nextElementValue(buf, fp);
		if(strcmp(buf, "edgeId") == 0){
				Edge *edgeP = getEp(ep, value, numberOfEdges);	
				assignEdge(&(v.ep), &EdgePointerStart[EdgePointerCount++], edgeP);
		}
		else
			break;
		}

	getFloorAndtype(v.vertexId ,&(v.floorId) , &(v.type));

	return v;	
}


void assignEdge(EdgePointer **ep, EdgePointer *setEp, Edge *edge)
{
	if(*ep == NULL)
	{
		*ep = setEp;
		setEp->edge = edge; 
	}
	else{
		assignEdge(&((*ep)->nextEp), setEp, edge);
	}

}

void readEdges(FILE *fp, Edge *edges, int numberOfEdges)
{
	char buf[16];
	memset(buf, 0, 16);
	nextElement(buf, fp);
	int i;

	if(strcmp(buf,"edges"))
		error();


	for(i = 0; i < numberOfEdges; i++)
	{
		edges[i] = readEdge(fp);
	}

	nextElement(buf, fp);

}

Edge readEdge(FILE *fp)
{
	Edge ed;
	unsigned int value, i;
	char buf[128];
	nextElement(buf, fp);

	for(i = 0; i < 4; i++)
	{
		memset(buf, 0, 128);
		value = nextElementValue(buf, fp);

		if(strcmp(buf, "edgeId") == 0)
			ed.edgeId = value;
		if(strcmp(buf, "weight") == 0)
			ed.weight = value;
		if(strcmp(buf, "vertexId1") == 0)
			ed.vertex1 = (Vertex *)(long)value;
		if(strcmp(buf, "vertexId2") == 0)
			ed.vertex2 = (Vertex *)(long)value;
	}

	reachChar('>', fp);

	return ed;
}

Edge *getEp(Edge *ep, unsigned int id, int numberOfEdges)
{
	int i;
	for(i = 0; i < numberOfEdges; i++){
		if(ep[i].edgeId == id)
			return &ep[i];
	}
	return NULL;
}

int nextElementValue(char *name, FILE *fp)
{
	unsigned int value;
	nextElement(name, fp);
	fscanf(fp, "%u", &value);
	reachChar('>', fp);
	return value;
}

void nextElement(char *name, FILE *fp)
{
	reachChar('<', fp);
	readToChar(name, '>', fp);
}

int readToChar(char *name, char t, FILE *fp)
{	
	int i = 0;
	char c;
	while((c = getc(fp)) != EOF)
	{
		if(i > 128 - 1)
			return 0;

		if(c == t)
			return 1;

		if(c != '/')
			name[i++] = c;
	}
	return 0;
}

int reachChar(char t, FILE *fp)
{
	char c;
	while((c = getc(fp)) != EOF)
	{
		if(c == t)
			return 1;
	}
	return 0;
}

void readDefaultAtributes(int *edges, int *vertices, int *floors, FILE *fp)
{
	int i;
	int x;
	char buf[128];
	for(i = 0; i < 3; i++){
		memset(buf, 0, 128);
		x = readAtribute(buf, fp);

		if(strcmp(buf, "edges") == 0)
			*edges = x;
		else if(strcmp(buf, "vertices") == 0)
			*vertices = x;
		else if(strcmp(buf, "floors") == 0)
			*floors = x;
	}
}

int readAtribute(char *name, FILE *fp)
{
	int i = 0, value;
	char c;
	while((c = getc(fp)) != '"'){
		if(i == 128 - 1)
		{
			error();
			break;
		}

		if(c != ' ' && c != '=' && c != '/')
			name[i++] = c;
	}

	fscanf(fp, "%d", &value);
	getc(fp);

	return value;

}

void error()
{
	printf("Error reading XML file. \n");
	exit(1);
}