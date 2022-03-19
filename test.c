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

//defining structure of graph + array of graphs it can be flipped into (graphs of flip distance 1)
//used for adjecancy oracle

typedef struct {
	Graph *graph;
	struct flippableTree *neighbourGraphs[];
}flippableTree;

/* //MATRICES WITH POINTERS TEST FUNCTIONS - ADD LATER

// int** testAdjMatrix = createMatrix(NUMOFVERTICES,NUMOFVERTICES);

int** createMatrix(int m, int n){
	int* values = calloc(m*n, sizeof(int));
    int** rows = malloc(m*sizeof(int*));
    for (int i=0; i<m; ++i){
        rows[i] = values + i*n;
    }
    return rows;
}

void printTESTmatrix(const int** mat[NUMOFVERTICES][NUMOFVERTICES]){
	for(int i = 0; i< NUMOFVERTICES; i++){
		for(int j = 0; j< NUMOFVERTICES ; j++){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}*/

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

//prints contents of matrix
void printMatrix(int mat[NUMOFVERTICES][NUMOFVERTICES]){
	for(int i = 0; i< NUMOFVERTICES; i++){
		for(int j = 0; j< NUMOFVERTICES ; j++){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}


//helper functions to manipulate tuples of flippable edges

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


//add flippable edge to the array of flippable edges
void addTuple(int vertex1, int vertex2, int vertex3, int vertex4, Vertex *arr_vert[], flipQuad allFlips[], int *flippableEcount) {
	
	
	if(valueInArray(vertex1, vertex2, vertex3, vertex4, allFlips)){
		return;
	}
	

	//printf("%d\n", allFlips[*flippableEcount].ver2);
	
	//printf("%d, %d\n", vertex1, vertex2);
    allFlips[*flippableEcount].edge1.ver1 = vertex1;
    allFlips[*flippableEcount].edge1.ver2 = vertex2;
    allFlips[*flippableEcount].edge2.ver1 = vertex3;
    allFlips[*flippableEcount].edge2.ver2 = vertex4;    
    
   

    //printf("flippable edge: %d, %d\n", allFlips[*flippableEcount].ver1, allFlips[*flippableEcount].ver2);

    *flippableEcount = *flippableEcount + 1;
    //printf("%d\n", *flippableEcount);
    
}

//list all flippable edges
void listTuples(flipQuad allFlips[], int *flippableEcount) {
    for (int i = 0; i < *flippableEcount; ++i)
        printf("flippable edge: (%d,%d) to (%d,%d)\n", allFlips[i].edge1.ver1, allFlips[i].edge1.ver2,allFlips[i].edge2.ver1, allFlips[i].edge2.ver2);
    puts("==========");
}

//remove edge ver1 -> ver2 from current graph, vertices referenced by their name
void removeEdgge(int vertex1, int vertex2, Vertex *arr_vert[]){
	Arc *a;
	Arc *prev;
	for(int i = 0; i < NUMOFVERTICES; i++){
		prev = arr_vert[i]->arcs;
		for(a = arr_vert[i]->arcs; a; a = a->next){
			//printf("previous: %s\n",prev->tip->name);
			if((vertex1 == atoi(arr_vert[i]->name)) && (vertex2 == atoi(a->tip->name))){
				printf("removed arc (%s, %s), %d\n", arr_vert[i]->name, a->tip->name, i);
				prev->next = a->next;
				//free(a);
			}
			else if((vertex2 == atoi(arr_vert[i]->name)) && (vertex1 == atoi(a->tip->name))){
				//remove arc from the linked list
				printf("removed arc (%s, %s), %d\n", arr_vert[i]->name, a->tip->name, i);
				prev->next = a->next;
				//free(a);
			}
			prev = a;
		}
	}
}

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

void flipPossible(Vertex *v1, Vertex *v2,Vertex *v3, Vertex *v4, flipQuad allFlips[])/*not working*/{

	/*
	i -> j 
	i -> k done
	i -> l
	k -> l
	

	Arc *temp1;
	Arc *temp2;
	int mrdka = 0;
	
	if(neighbours(v1, v2)){
		for(temp1 = v1->arcs;temp1;temp1=temp1->next){
			//printf("%s to %s\n",v1->name ,temp1->tip->name);
			for(temp2 = temp1->tip->arcs;temp2;temp2=temp2->next){
				//printf("%s to %s\n",temp1->tip->name ,temp2->tip->name);
				if(!strcmp(temp2->tip->name,v2->name)){
					mrdka++;
				}
			}
			//printf("\n");
		}
		if(mrdka >= 2){
			printf("flippable\n");
		}
		else{
			printf("not flippable, mrdka: %d\n", mrdka);
		}
	}
	*/
	if(valueInArray(atoi(v1->name), atoi(v2->name),atoi(v3->name), atoi(v4->name),  allFlips)){
		printf("edge (%s, %s) is flippable\n", v1->name, v2->name);
		return 1;
	}
	else{
		printf("edge (%s, %s) is not flippable\n", v1->name, v2->name);
		return 0;
	}
}

void makeFlipList(Vertex *arr_vert[], flipQuad allFlips[], int *flippableEcount){
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

	for(int i = 0; i<NUMOFVERTICES ; i++){
		for(int j = 0; j<NUMOFVERTICES ; j++){
			if(i == j){continue;}
			for(int k = 0; k<NUMOFVERTICES ; k++){
				if(k == i || k == j){continue;}
				for(int l = 0; l<NUMOFVERTICES ; l++){
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
						addTuple(atoi(arr_vert[i]->name),atoi(arr_vert[k]->name), atoi(arr_vert[j]->name),atoi(arr_vert[l]->name), arr_vert, allFlips, flippableEcount);
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
	printf("flipped edge (%d, %d)", edgeToFlip.edge1.ver1, edgeToFlip.edge1.ver2);
	printf("\n");
	//flip the specified edges in the new graph
	//flippableEdge newEdge = getOtherPair(vertex1, vertex2, allFlips);
	printf("to edge: (%d, %d)\n", edgeToFlip.edge2.ver1, edgeToFlip.edge2.ver2);
	
	gb_new_edge(new_vert_arr[edgeToFlip.edge2.ver1], new_vert_arr[edgeToFlip.edge2.ver2], 1L);
	//printf("new edge added: %d, %d\n", newEdge.ver1,newEdge.ver2);
	removeEdgge(edgeToFlip.edge1.ver1, edgeToFlip.edge1.ver2, new_vert_arr);

	//return new graph with flipped edge
	return new;

}

Graph* Adj(Graph *g, int i) /* adjacency oracle */{
	printf("Adj(some graph, %d)\n", i);
	
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

	makeFlipList(&array_of_vertices, allPossibleFlips, &flippableEcount);

	//printf("enumerated edge: %d, %d\n", allPossibleFlips[i].edge2.ver1, allPossibleFlips[i].edge2.ver2);
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

Graph* localSearch(Graph *g){
	printf("localsearch(some graph)\n");
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

	makeFlipList(&arr_vert, allFlips, &flippableEcount);
	lexicographicOrder(allFlips, flippableEcount);
	Graph *adjRetrunGraph = flipOneEdge(g, allFlips[0], allFlips);
	return adjRetrunGraph;
}

//if if neighbour w of g is child og g in reverse search tree
int reverse (Graph *g, int i){
	printf("reverse(some graph, %d)\n", i);
	Graph *w = Adj(g, i);

	if(w != NULL){
		return g==localSearch(w);
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
	printf("%d\n", targetedArcs);

	/*w*/g = localSearch(g);

	//int currentNumOfArcs = numberOfArcs(intersect);
	
	for(int j = 0; j < 100;j++){
		Graph *intersect = intersection(child, Adj(g, j),0,0);
		printf("%d\n", numberOfArcs(intersect));
	}


	/*
	while(targetedArcs !=  numberOfArcs(intersect)){
		gb_recycle(intersect);
		intersect = intersection(child, Adj(g, i),0,0);
		i++;
	}
	*/
	return i;
}

int root(Graph *g){
	//printf("root(some graph)\n");
	
	if(!strcmp(g->id, "start")){
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
	//printf("%d\n", maxdeg);
	while (!root(g) || i < maxdeg){
		do{
			i++;
			printf("depth: %d\n", i);
		}while (i <= maxdeg && !reverse(g, i));
		if (i <= maxdeg){

			printf("kundovina\n");
			g = Adj(g, i);
			//printf("%s\n", g->id);
			output(g);
			count++;
			i = 0;
		}
		else{
			i = backtrack(g);
		}
	}
	return count;
}

int main(){
	Area s;
	Vertex *arr_vert[NUMOFVERTICES];

	//Constructing triangulated graph, 9-critical, reference 12.57.1 from Boutin paper
	Graph *triang = restore_graph("triang.gb");

	//set ID od the loaded graph for root() function
	char rootID[] =  "start";
	strcpy(triang->id, rootID);
	//printf("%s\n", triang->id);

	arr_vert[0] = triang->vertices;

	for (int i=1; i<NUMOFVERTICES;i++){
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

	//printf(triang->id);

	/*ADJ METRIX STUGG

	//adjecancy matrix for the graph
	int adjecancyMatrix[NUMOFVERTICES][NUMOFVERTICES];

	//populating adjecancy matrix

	//populating with dummy 0s
	initiateMatrix(adjecancyMatrix);

	//print the matrix for tdebugging
	printMatrix(adjecancyMatrix);

	//pupulating matrix with 1s where there is an edge
	updateArcsInMatrix(adjecancyMatrix, &arr_vert);
	
	//print the matrix for tdebugging
	printMatrix(adjecancyMatrix);	

	//raising the matrix to the n power
	int result[NUMOFVERTICES][NUMOFVERTICES];
	initiateMatrix(result);

	//square the matrix to the power of n and save it to result
	squareMatrix(adjecancyMatrix,result, 1);

	//print result of the operation to the nth power
	printMatrix(result);


	*/


	//TESTING LEXICOGRAPHICALL ORDER SORTING
	makeFlipList(&arr_vert, allFlips, &flippableEcount);
	//listTuples(allFlips, &flippableEcount);
	lexicographicOrder(allFlips, flippableEcount);
	//listTuples(allFlips, &flippableEcount);

	int adjecancyMatrix[NUMOFVERTICES][NUMOFVERTICES];
	initiateMatrix(adjecancyMatrix);
	updateArcsInMatrix(adjecancyMatrix, &arr_vert);
	printMatrix(adjecancyMatrix);
	printf("\n");

	removeEdgge(0,3, arr_vert);

	int testMatrix[NUMOFVERTICES][NUMOFVERTICES];
	initiateMatrix(testMatrix);
	updateArcsInMatrix(testMatrix, &arr_vert);
	printMatrix(testMatrix);

	//printf("%d\n", flippableEcount);
	/*
	printf("reverse ==========================================\n");

	Graph *cojavim = localSearch(triang);

	Vertex *test0[cojavim->n];

	test0[0] = cojavim->vertices;

	for (int i=1; i<cojavim->n;i++){
		test0[i] = test0[0] + i;
	}

	int adjecancyMatrix2[cojavim->n][cojavim->n];
	initiateMatrix(adjecancyMatrix2);
	updateArcsInMatrix(adjecancyMatrix2, &test0);
	printMatrix(adjecancyMatrix2);

	
	flipQuad test1[100];

	//initiaze to all 0s, was cousing problems, due to some values in memory
	for (int i=1; i<sizeof(test1)/sizeof(test1[0]); i++){
		test1[i].edge1.ver1 = 0;
		test1[i].edge1.ver2 = 0;
		test1[i].edge2.ver1 = 0;
		test1[i].edge2.ver2 = 0;
	}

	int test2 = 0;


	makeFlipList(&test0, test1, &test2);
	printf("%d\n", test2);
	lexicographicOrder(test1, test2);
	listTuples(test1, &test2);
	*/
	

	//Graph *kundicka = Adj(triang, 2);
	//int mrdka = backtrack(triang);
	//printf("%d\n", mrdka);
	//printf("%d\n", mrdka);

	//Graph *test = localSearch(triang);
	//save_graph(test, "new.gb");

	//int idk = reversesearch(triang, flippableEcount);
}