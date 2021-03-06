#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gb_graph.h"  
#include "gb_save.h"
#include "gb_basic.h"	

#define NUMOFVERTICES 12

//defining tuple for storing flippable edges
typedef struct {
    int ver1;
    int ver2;
} flippableEdge;

//defining structure to store pairs of flippable edges, flippable edge + edge it can be flipped into 

typedef struct {
	flippableEdge edge1;
	flippableEdge edge2;
} flipQuad;

//prints all edges in a graph, for debugging 
void listEdgesOfGraph(Graph *g){
	Vertex *v;
	Arc *a;

	for(v = g->vertices; v < g->vertices + g->n; v++){
		for(a = v->arcs; a; a = a->next){
			printf("(%s,%s);", v->name, a->tip->name);
		}
	}
}

//prints the flippable list of graph, for debugging
void flippableListOfGraph(Graph *g){

	Vertex *testVertice[g->n];

	testVertice[0] = g->vertices;

	for (int i=1; i<g->n;i++){
		testVertice[i] = testVertice[0] + i;
	}

	flipQuad testAllFlips[1000];

	//initiaze to all 0s, was cousing problems, due to some values in memory
	for (int i=1; i<sizeof(testAllFlips)/sizeof(testAllFlips[0]); i++){
		testAllFlips[i].edge1.ver1 = 0;
		testAllFlips[i].edge1.ver2 = 0;
		testAllFlips[i].edge2.ver1 = 0;
		testAllFlips[i].edge2.ver2 = 0;
	}

	int testFlippableEcount = 0;

	makeFlipList(&testVertice, g->n ,testAllFlips, &testFlippableEcount);
	lexicographicOrder(testAllFlips, testFlippableEcount);
	listTuples(testAllFlips, &testFlippableEcount);
	printf("%d\n", testFlippableEcount);
}

//initiaze adjecancy matrix to all 0s
void initiateMatrix(int mat1[NUMOFVERTICES][NUMOFVERTICES]){
	for(int k = 0; k < NUMOFVERTICES; k++){
		for(int l = 0; l < NUMOFVERTICES; l++){
			mat1[k][l] = 0;
		}
	}

}

//update adjecancy matrix mat1 to the current graph
void updateArcsInMatrix(int mat1[NUMOFVERTICES][NUMOFVERTICES], Vertex *arr_vert[]){
	for(int j = 0; j<NUMOFVERTICES ; j++){
		for(Arc *a = arr_vert[j]->arcs; a; a = a->next){
			int temp = atoi(a->tip->name);
			mat1[j][temp] += 1;
		}
	}
}

//squares adjecancy matrix to the nth power
void squareMatrix(int mat1[NUMOFVERTICES][NUMOFVERTICES], int result[NUMOFVERTICES][NUMOFVERTICES], int n){
	int temp[NUMOFVERTICES][NUMOFVERTICES];
	int sum = 0;

	for ( int b = 0 ; b < NUMOFVERTICES ; b++ ) {
        for ( int d = 0 ; d < NUMOFVERTICES ; d++ ) {
            result[b][d] = mat1[b][d];
        }
    }

	for (int l = 0; l < n - 1; l++){

		for (int i = 0; i < NUMOFVERTICES; i++) {
	    	for (int j = 0; j < NUMOFVERTICES; j++) {
	        	for (int k = 0; k < NUMOFVERTICES; k++) {
	        		sum += mat1[i][k] * result[k][j];
	        	}
	        	temp[i][j] = sum;
	        	sum = 0;
	        }
	    }
	

		for ( int b = 0 ; b < NUMOFVERTICES ; b++ ) {
	        for ( int d = 0 ; d < NUMOFVERTICES ; d++ ) {
	            result[b][d] = temp[b][d];
	        }
	    }
	}
}

//prints contents of adjecancy matrix
void printMatrix(int mat[NUMOFVERTICES][NUMOFVERTICES]){
	for(int i = 0; i< NUMOFVERTICES; i++){
		for(int j = 0; j< NUMOFVERTICES ; j++){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

//helper functions to manipulate tuples of flippable edges

//if an edge and an edge it can be flipped into is in the array of flippable edges, return true
int valueInArray(int vertex1, int vertex2, int vertex3, int vertex4, flipQuad allFlips[]){
    int i;
    for(i = 0; i < 101; i++){
        if((allFlips[i].edge1.ver1 == vertex1 && allFlips[i].edge1.ver2 == vertex2) && ((allFlips[i].edge2.ver1 == vertex3 && allFlips[i].edge2.ver2 == vertex4))){
            return 1;
        }
        else if((allFlips[i].edge1.ver1 == vertex1 && allFlips[i].edge1.ver2 == vertex2) && (allFlips[i].edge2.ver1 == vertex4 && allFlips[i].edge2.ver2 == vertex3)){
        	return 1;
        }
        else if((allFlips[i].edge1.ver1 == vertex2 && allFlips[i].edge1.ver2 == vertex1) && ((allFlips[i].edge2.ver1 == vertex3 && allFlips[i].edge2.ver2 == vertex4))){
        	return 1;
        }
        else if((allFlips[i].edge1.ver1 == vertex2 && allFlips[i].edge1.ver2 == vertex1) && (allFlips[i].edge2.ver1 == vertex4 && allFlips[i].edge2.ver2 == vertex3)){
        	return 1;
        }
    }
    return 0;
}

// returns true if and edge is in the graph referenced by array of vertices
int edgeInGraph(Vertex *arr_vert[], int size ,int vertex3, int vertex4){
	Arc *a;
	for(int i = 0; i < size; i++){
		for(a = arr_vert[i]->arcs; a; a = a->next){
			if((atoi(arr_vert[i]->name) == vertex3) && (atoi(a->tip->name) == vertex4)){
				//printf("(%d, %d)\n", atoi(arr_vert[i]->name), atoi(a->tip->name));
				return 1;
			}
			/*
			else if((atoi(arr_vert[i]->name) == vertex4) && (atoi(a->tip->name) == vertex3)){
				printf("(%d, %d)\n", atoi(arr_vert[i]->name), atoi(a->tip->name));
				return 1;
			}
			*/
		}
	}
	return 0;
}

//add flippable edge to the array of flippable edges
void addTuple(int vertex1, int vertex2, int vertex3, int vertex4, Vertex *arr_vert[], int size, flipQuad allFlips[], int *flippableEcount) {
	
	if(valueInArray(vertex1, vertex2, vertex3, vertex4, allFlips) || edgeInGraph(arr_vert, size ,vertex3, vertex4)){
		return;
	}

    allFlips[*flippableEcount].edge1.ver1 = vertex1;
    allFlips[*flippableEcount].edge1.ver2 = vertex2;
    allFlips[*flippableEcount].edge2.ver1 = vertex3;
    allFlips[*flippableEcount].edge2.ver2 = vertex4;    

    //printf("flippable edge: %d, %d\n", allFlips[*flippableEcount].ver1, allFlips[*flippableEcount].ver2);

    *flippableEcount = *flippableEcount + 1;
    //printf("%d\n", *flippableEcount);
    
}

//list all flippable edges in a graph referenced by array of flipable edges
void listTuples(flipQuad allFlips[], int *flippableEcount) {
    for (int i = 0; i < *flippableEcount; ++i)
        printf("%d ,flippable edge: (%d,%d) to (%d,%d)\n", i,allFlips[i].edge1.ver1, allFlips[i].edge1.ver2,allFlips[i].edge2.ver1, allFlips[i].edge2.ver2);
    puts("==========");
}

//remove edge ver1 -> ver2 from current graph, vertices referenced by their name
void removeEdgge(int vertex1, int vertex2, Vertex *arr_vert[], int size){
	Arc *a;
	Arc *prev;
	//used to remove first node of the arcs linked list
	int nodeOrder;

	for(int i = 0; i < size; i++){
		prev = arr_vert[i]->arcs;
		nodeOrder = 0;
		for(a = arr_vert[i]->arcs; a; a = a->next){
			//printf("previous: %s\n",prev->tip->name);
			if((vertex1 == atoi(arr_vert[i]->name)) && (vertex2 == atoi(a->tip->name))){
				//printf("removed arc (%s, %s), %d\n", arr_vert[i]->name, a->tip->name, i);
				if(nodeOrder == 0){
					arr_vert[i]->arcs = a->next;
					continue;
				}
				else {
					prev->next = a->next;
				}
				//free(a);
			}
			else if((vertex2 == atoi(arr_vert[i]->name)) && (vertex1 == atoi(a->tip->name))){
				//remove arc from the linked list
				//printf("removed arc (%s, %s), %d\n", arr_vert[i]->name, a->tip->name, i);
				if(nodeOrder == 0){
					arr_vert[i]->arcs = a->next;
					continue;
				}
				else {
					prev->next = a->next;
				}
				//free(a);
			}
			nodeOrder++;
			prev = a;
		}
	}
}

//returns true if two vertices share an edge
int neighbours(Vertex *v1, Vertex *v2){
	Arc *a;
	int count = 0;
	
	for(a = v1->arcs; a; a = a->next){
		if(!strcmp(a->tip->name,v2->name)){
			return 1;
		}
		count++;
		if(count >= NUMOFVERTICES){
			return 0;
		}
	}
	
}

void makeFlipList(Vertex *arr_vert[], int size, flipQuad allFlips[], int *flippableEcount){
	//helper arc and vertex
	Vertex *v;
	Arc *a;
	int flippable = 0;

	/*
	i -> j
	i -> k
	i -> l
	k -> l
	j -> k
	*/

	for(int i = 0; i<size ; i++){
		for(int j = 0; j<size ; j++){
			if(i == j){continue;}
			for(int k = 0; k<size ; k++){
				if(k == i || k == j){continue;}
				for(int l = 0; l<size ; l++){
					if(l == i || l == j || l == k){continue;}
					//printf("debug 1\n");
					for(a = arr_vert[i]->arcs; a; a = a->next){
						//printf("debug 2\n");
						if(a->tip == arr_vert[j]){
							flippable += 1;
						}
						if(a->tip == arr_vert[k]){
							flippable += 1;
						}
						if(a->tip == arr_vert[l]){
							flippable += 1;
						}
					}
					for(a = arr_vert[j]->arcs; a; a = a->next){
						if(a->tip == arr_vert[k]){
							flippable += 1;
						}
					}
					for(a = arr_vert[k]->arcs; a; a = a->next){
						if(a->tip == arr_vert[l]){
							flippable += 1;
						}
					}
					if(flippable == 5){
						//edge i -> k is flippable to k -> l
						addTuple(atoi(arr_vert[i]->name),atoi(arr_vert[k]->name), atoi(arr_vert[j]->name),atoi(arr_vert[l]->name), arr_vert, size , allFlips, flippableEcount);
						//remove edge i -> from the grahp
						//add edge k -> l to the graph

					}					
					flippable = 0;
				}
			}
		}
	}
}

//from vertices of one edge, get the edge it can be flipped into 
flippableEdge getOtherPair(int vertex1, int vertex2, flipQuad allFlips[]){
    int i;
    for(i = 0; i < 101; i++){
        if((allFlips[i].edge1.ver1 == vertex1 && allFlips[i].edge1.ver2 == vertex2) || (allFlips[i].edge1.ver1 == vertex2 && allFlips[i].edge1.ver2 == vertex1)){
            return allFlips[i].edge2;
        }
    }

    flippableEdge empty;
    return empty;
}

// getsgraph as input and returns another graph with flipped edge
Graph* flipOneEdge(Graph *old, flipQuad edgeToFlip, flipQuad allFlips[]){
	
	//printf("flipone: %d, %d\n", vertex1, vertex2);

	int n = old->n;
	Graph *new = gb_new_graph(n);

	//populate new array of vertex pointers of a new graph
	Vertex *new_vert_arr[n];
	new_vert_arr[0] = new->vertices;

	for (int i=1; i<n;i++){
		new_vert_arr[i] = new_vert_arr[0] + i;
	}

	//repopulate the new graph with the same edges

	Vertex *v;
	Arc *a;

	switch_to_graph(new);
	//naming of vertices

	for (int i=0; i<n;i++){
		v = old->vertices + i;
		if(v < old->vertices + old->n){
			new_vert_arr[i]->name = gb_save_string(v->name);
		}
	}

	//adding edges

	for(v = old->vertices; v < old->vertices + old->n; v++){
		for(a = v->arcs; a; a = a->next){
			gb_new_arc(new_vert_arr[atoi(v->name)],new_vert_arr[atoi(a->tip->name)]);
		}
	}
	//printf("flipped edge (%d, %d)", edgeToFlip.edge1.ver1, edgeToFlip.edge1.ver2);
	printf("\n");
	//flip the specified edges in the new graph
	//printf("to edge: (%d, %d)\n", edgeToFlip.edge2.ver1, edgeToFlip.edge2.ver2);
	gb_new_edge(new_vert_arr[edgeToFlip.edge2.ver1], new_vert_arr[edgeToFlip.edge2.ver2], 1L);
	//printf("new edge added: %d, %d\n", newEdge.ver1,newEdge.ver2);
	removeEdgge(edgeToFlip.edge1.ver1, edgeToFlip.edge1.ver2, new_vert_arr, n);

	//return new graph with flipped edge
	return new;

}

Graph* Adj(Graph *g, int i) /* adjacency oracle */{
	//printf("Adj(some graph, %d)\n", i);
	
	int n = g->n;
	Vertex *array_of_vertices[n];

	array_of_vertices[0] = g->vertices;

	for (int i=1; i<n;i++){
		array_of_vertices[i] = array_of_vertices[0] + i;
	}

	flipQuad allPossibleFlips[100];
	int flippableEcount = 0;

	//initiaze to all 0s, was cousing problems, due to some values in memory
	for (int j=1; j<sizeof(allPossibleFlips)/sizeof(allPossibleFlips[0]); j++){
		allPossibleFlips[j].edge1.ver1 = 0;
		allPossibleFlips[j].edge1.ver2 = 0;
		allPossibleFlips[j].edge2.ver1 = 0;
		allPossibleFlips[j].edge2.ver2 = 0;
	}

	makeFlipList(&array_of_vertices, g->n,allPossibleFlips, &flippableEcount);
	lexicographicOrder(allPossibleFlips, flippableEcount);

	Graph *adjRetrunGraph = flipOneEdge(g, allPossibleFlips[i], allPossibleFlips);
	return adjRetrunGraph;
}

//subfunction comparer for qsort sorting function(to compare two flippable edges)
int comparer(const void *v1, const void *v2){
	const flipQuad *flippableEdge1 = (flipQuad *)v1;
	const flipQuad *flippableEdge2 = (flipQuad *)v2;

	
	if((flippableEdge1->edge1.ver1 == flippableEdge2->edge1.ver1) && (flippableEdge1->edge1.ver2 < flippableEdge2->edge1.ver2)){
		return -1;
	}
	else if((flippableEdge1->edge1.ver1 < flippableEdge2->edge1.ver1) && (flippableEdge1->edge1.ver2 > flippableEdge2->edge1.ver2)){
		return -1;
	}
	else if((flippableEdge1->edge1.ver1 < flippableEdge2->edge1.ver1) && (flippableEdge1->edge1.ver2 < flippableEdge2->edge1.ver2)){
		return -1;
	}
	else if((flippableEdge1->edge1.ver1 == flippableEdge2->edge1.ver1) && (flippableEdge1->edge1.ver2 > flippableEdge2->edge1.ver2)){
		return +1;
	}
	else if((flippableEdge1->edge1.ver1 > flippableEdge2->edge2.ver1) && (flippableEdge1->edge1.ver2 < flippableEdge2->edge1.ver2)){
		return +1;
	}
	else if((flippableEdge1->edge1.ver1 > flippableEdge2->edge2.ver1) && (flippableEdge1->edge1.ver2 > flippableEdge2->edge1.ver2)){
		return +1;
	}
	else{
		return 0;	
	}
}

//order array of flippable edges lexicographically
void lexicographicOrder(flipQuad allFlips[], int flippableEcount){
	qsort(allFlips,flippableEcount, sizeof(flipQuad), comparer);
}

//if edge is suitable for flip(edge1 is lexicographically smaller then edge2)
int suitableForFlip(flippableEdge edge1, flippableEdge edge2){
	if(edge1.ver1 > edge2.ver1){
		return 1;
	}
	else if((edge1.ver1 == edge2.ver1) && (edge1.ver2 > edge2.ver2)){
		return 1;
	}
	else{
		return 0;
	}
}

//take the first smallest edge that can be flipped to bigger
int firstSmallestToBiggest(flipQuad allFlips[], int flippableEcount){
	for(int i = 0; i< flippableEcount; i++){
		if(suitableForFlip(allFlips[i].edge1, allFlips[i].edge2)){
			return i;
		}
	}
}

Graph* localSearch(Graph *g){
	//printf("localsearch(some graph)\n");
	int n = g->n;
	Vertex *arr_vert[n];

	arr_vert[0] = g->vertices;

	for (int i=1; i<n;i++){
		arr_vert[i] = arr_vert[0] + i;
	}

	flipQuad allFlips[100];
	int flippableEcount = 0;

	//initiaze to all 0s, was cousing problems, due to some old values in memory
	for (int i=1; i<sizeof(allFlips)/sizeof(allFlips[0]); i++){
		allFlips[i].edge1.ver1 = 0;
		allFlips[i].edge1.ver2 = 0;
		allFlips[i].edge2.ver1 = 0;
		allFlips[i].edge2.ver2 = 0;
	}

	makeFlipList(&arr_vert, g->n,allFlips, &flippableEcount);
	lexicographicOrder(allFlips, flippableEcount);
	Graph *adjRetrunGraph = flipOneEdge(g, allFlips[firstSmallestToBiggest(allFlips,flippableEcount)], allFlips);
	return adjRetrunGraph;
}

//if if neighbour w of g is child of g in reverse search tree
int reverse (Graph *g, int i){
	//printf("reverse(some graph, %d)\n", i);
	Graph *w = Adj(g, i);
	//flippableListOfGraph(w);
	int targetedArcs = numberOfArcs(g);
	Graph *ls = localSearch(w);
	//flippableListOfGraph(ls);
	Graph *intersect = intersection(g, ls,0,0);

	//w != NULL)
	if(targetedArcs==numberOfArcs(intersect)){
		return 1;
	}
	else{
		return 0;
	}
}

//return number of arcs in the graph g, used in backtreack()
int numberOfArcs(Graph *g){
	//printf("numberOfArcs()\n");
	Vertex *v;
	Arc *a;
	int count = 0;

	for(v = g->vertices; v < g->vertices + g->n; v++){
		for(a = v->arcs; a; a = a->next){
			count++;
		}
	}
	return count;
}

//look for a parent of g in reverse search tree (w = localsearch(g)), return its i g = (adj(w,i))
/*
graph g

grahp w = localseach(g)
(graph g with flipped lexicographically smallest edge)

Iam looking fo i such that

g = Adj(w,i)
*/
int backtrack(Graph *g){
	printf("backtrack(some graph)\n");
	int i = 0;
	Graph *child = g;
	int targetedArcs = numberOfArcs(child);
	Graph *intersect = intersection(child, Adj(g, i),0,0);

	/*w*/g = localSearch(g);
	
	while(targetedArcs !=  numberOfArcs(intersect)){
		gb_recycle(intersect);
		i++;
		intersect = intersection(child, Adj(g, i),0,0);
	}
	return i;
}

int root(Graph *g){
	//printf("root(some graph)\n");
	
	if(!strcmp(g->id, "root")){
		return 1;
	}
	else{
		return 0;
	}
	
}

void output(Graph *g){
	printf("output: graph: %s, dept not known\n", g->id);
}

// reverse search

int reversesearch(Graph *g, int maxdeg){
	int i=0, count=1;
	output(g);
	
	while (!root(g) || i < maxdeg){
		do{
			i++;
		}while (i <= maxdeg && !reverse(g, i));
		if (i <= maxdeg){

			g = Adj(g, i);
			output(g);
			count++;
			printf("%d\n", count);
			i = 0;
		}
		else
			i = backtrack(g);
			g = localSearch(g);
	}
	return count;
}

int main(){
	Area s;

	//Constructing triangulated graph, 9-critical, reference 12.57.1 from Boutin paper
	Graph *triang = restore_graph("v_13_l2.gb");
	Vertex *arr_vert[triang->n];

	//set ID od the loaded graph for root() function
	
	//printf("%s\n", triang->id);

	arr_vert[0] = triang->vertices;

	for (int i=1; i<triang->n;i++){
		arr_vert[i] = arr_vert[0] + i;
	}

	flipQuad allFlips[1000];

	//initiaze to all 0s, was cousing problems, due to some values in memory
	for (int i=1; i<sizeof(allFlips)/sizeof(allFlips[0]); i++){
		allFlips[i].edge1.ver1 = 0;
		allFlips[i].edge1.ver2 = 0;
		allFlips[i].edge2.ver1 = 0;
		allFlips[i].edge2.ver2 = 0;
	}

	int flippableEcount = 0;

	printf("reverse ==========================================\n");

	flippableListOfGraph(triang);
	
	char rootID[] =  "root";
	strcpy(triang->id, rootID);

	int reverse = reversesearch(triang, 37);

}