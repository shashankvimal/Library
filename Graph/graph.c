#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "mem_alloc.h"
#include <memory.h>

#define SIZE_GRAPH(nVertices, pPlaceholder)					((nVertices) * sizeof(*(pPlaceholder)))
#define NOT_LAST_ELEMENT_IN_LIST(position, lastPosition)	((position) < (lastPosition) - 1)

#define INT													(1)
#define CHAR												(2)
#define STRING												(3)

#define ST_VERTEX_UNKNOWN									(0)
#define ST_VERTEX_NOT_PROCESSED								(1)
#define ST_VERTEX_PROCESSED									(2)

typedef struct neighbour T_ST_NEIGHBOUR_INFO_t;

typedef struct vertex
{
	unsigned int dataType;
	unsigned int dataLen;
	void *pData;
	T_ST_NEIGHBOUR_INFO_t *pNeighbour;
	unsigned int status;
}T_ST_VERTEX_t;

typedef struct neighbour
{
	T_ST_VERTEX_t *pSelf;
	struct neighbour *pNext;
}T_ST_NEIGHBOUR_INFO_t;

T_ST_VERTEX_t* graph_alloc(unsigned int nVertices_p)
{
	T_ST_VERTEX_t *pGraph;
	
	pGraph = (T_ST_VERTEX_t*)malloc(SIZE_GRAPH(nVertices_p, pGraph));
	
	printf("Allocation successful!\n");
	
	return pGraph;
	
}
void graph_linkNeighbours(T_ST_VERTEX_t *pVertex, 
                          unsigned int nNeighbours, 
						  T_ST_VERTEX_t* neighbourList[])
{
	unsigned int i;
	T_ST_NEIGHBOUR_INFO_t *pTemp = (T_ST_NEIGHBOUR_INFO_t*)malloc(sizeof(*pTemp));
	pTemp->pSelf = neighbourList[0];
	pTemp->pNext = NULL;
	pVertex->pNeighbour = pTemp;
	
	for(i = 1; neighbourList[i] != NULL; i++, pTemp->pNext = NULL)
	{
		pTemp->pNext = (T_ST_NEIGHBOUR_INFO_t*)malloc(sizeof(*pTemp));
		pTemp = pTemp->pNext;
		pTemp->pSelf = neighbourList[i];
	}
	
	for(pTemp = pVertex->pNeighbour; pTemp; pTemp = pTemp->pNext)
	{
		printf("My neighbours %p\n", pTemp->pSelf);
	}
	printf("\n");
}
void graph_destroy(T_ST_VERTEX_t* pGraph_p)
{
	ASSERT(pGraph_p != NULL, ERROR: Invalid Parameter!!);
}
void graph_dfs( T_ST_VERTEX_t *pVertex, 
				void (*pFprocess)(void *pArg),
				void *pArg )
{
	
	T_ST_NEIGHBOUR_INFO_t *pTemp;
	
	ASSERT(pVertex != NULL, ERROR: Invalid Parameter!!);
	
	if(pVertex->status != ST_VERTEX_PROCESSED)
	{
		pFprocess(pArg);
		pVertex->status = ST_VERTEX_PROCESSED;
	}
	
	for(pTemp = pVertex->pNeighbour; pTemp; pTemp = pTemp->pNext) 
	{
		graph_dfs(pTemp->pSelf, pFprocess, pArg);
	}
}
bool graph_bfs( T_ST_VERTEX_t *pVertex, 
				void (*pFprocess)(void *pArg),
				void *pArg )
{
	return TRUE;
}
T_ST_VERTEX_t* graph_mstUsingKruskalMethod()
{
	return NULL;
}
T_ST_VERTEX_t* graph_mstUsingPrimMethod()
{
	return NULL;
}
void graph_setVertexData( T_ST_VERTEX_t* pVertex,
						  unsigned int dataLen,
                          void *pData,  
						  unsigned int dataType )
{
	ASSERT(pVertex != NULL, ERROR: Invalid Parameter!!);
	
	memcpy(pVertex->pData, pData, dataLen);
	pVertex->dataLen = dataLen;
	pVertex->dataType = dataType;
}

void graph_setVertexStatus( T_ST_VERTEX_t* pVertex,
                            unsigned int status)
{
	ASSERT(pVertex != NULL, ERROR: Invalid Parameter!!);
	
	pVertex->status = status;
}

void graph_defaultProcess(void *pArg)
{
	T_ST_VERTEX_t* pVertex = (T_ST_VERTEX_t*)pArg;
	
	printf("Vertex data: %d\n", *(int*)(pVertex->pData));
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	/*TEST GRAPH TRAVERSAL*/
	unsigned int i;
	T_ST_VERTEX_t *pGraph = graph_alloc(5);
	
	for(i = 0; i < 5; i++)
	{
		pGraph[i].pData = (void*)malloc(sizeof(unsigned int));
		
		ASSERT(pGraph[i].pData != NULL, ERROR: Memeory allocation failed!!);
		
		graph_setVertexData(&pGraph[i], sizeof(int), (void*)&i, INT);
		
		graph_setVertexStatus(&pGraph[i], ST_VERTEX_UNKNOWN);
	}
	
	/*Neighbour list for vertex 1*/
	T_ST_VERTEX_t *neighbourList[5] = {&pGraph[1], &pGraph[2], &pGraph[3], NULL, NULL};
	graph_linkNeighbours(&pGraph[0], 3, neighbourList);
	
	/*Neighbour list for vertex 2*/
	T_ST_VERTEX_t *neighbourList1[5] = {&pGraph[0], &pGraph[3], &pGraph[4], NULL, NULL};
	graph_linkNeighbours(&pGraph[1], 3, neighbourList1);
	
	/*Neighbour list for vertex 3*/
	T_ST_VERTEX_t *neighbourList2[5] = {&pGraph[0], &pGraph[3], NULL, NULL, NULL};
	graph_linkNeighbours(&pGraph[1], 2, neighbourList2);
	
	/*Neighbour list for vertex 4*/
	T_ST_VERTEX_t *neighbourList3[5] = {&pGraph[0], &pGraph[1], &pGraph[2], &pGraph[4], NULL};
	graph_linkNeighbours(&pGraph[1], 4, neighbourList3);
	
	/*Neighbour list for vertex 5*/
	T_ST_VERTEX_t *neighbourList4[5] = {&pGraph[1], &pGraph[3], NULL, NULL, NULL};
	graph_linkNeighbours(&pGraph[1], 2, neighbourList4);
	
	printf("Depth first traversal\n");
	graph_dfs(pGraph, graph_defaultProcess, pGraph);
	printf("Adress of vertices %p, %p, %p, %p, %p\n", &pGraph[0], &pGraph[1], &pGraph[2], &pGraph[3], &pGraph[4]);
#if 0
	for(i = 0; i < 5; i++)
	{
		for(T_ST_NEIGHBOUR_INFO_t *pTemp = pGraph[i].pNeighbour; pTemp != NULL; pTemp = pTemp->pNext)
		{
			if(pTemp->pSelf != NULL)
				printf("Vertex %i, neighbour %p\n", i, pTemp->pSelf);
		}
	}
#endif
	/*TEST MST*/
	
	/*TEST SHORTEST PATH*/
	return 0;
}

