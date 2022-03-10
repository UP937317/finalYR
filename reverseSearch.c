#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gb_graph.h"  
#include "gb_save.h"

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

// reverse search and its functions

typedef int perm[100];
void Adj (perm v, int i) /* adjacency oracle */{}
int root (perm v){return 1;}/*if vertex is root of reverse search treee*/
int backtrack (perm v){return 1;}/*from node v to its parent f(v) in reverse search tree*/
int reverse (perm v, int i){return 1;}/*if neighbour ov v is child of w=f(v) in reverse search tree*/
int output (perm v)/*Ooutput result + dept(implement!)*/{return 1;}

int reversesearch (perm v, int maxdeg){
	int i=0, count=1;
	output (v);
	while (!root (v) || i < maxdeg){
		do{
			i++;
		}while (i <= maxdeg && !reverse (v, i));
		if (i <= maxdeg){
			Adj (v, i);
			output (v);
			count++;
			i = 0;
		}
		else{
			i = backtrack (v);
		}
	}
	return count;
}

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
			mat1[j][temp] = 1;
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
			printf("%.3d ", mat[i][j]);
		}
		printf("\n");
	}
}


//helper functions to manipulate tuples of flippable edges

int valueInArray(int vertex1, int vertex2, flipQuad allFlips[]){
    int i;
    for(i = 0; i < 101; i++){
        if((allFlips[i].edge1.ver1 == vertex1 && allFlips[i].edge1.ver2 == vertex2) || (allFlips[i].edge1.ver1 == vertex2 && allFlips[i].edge1.ver2 == vertex1)){
            return 1;
        }
    }
    return 0;
}


//add flippable edge to the array of flippable edges
void addTuple(int vertex1, int vertex2, int vertex3, int vertex4, Vertex *arr_vert[], flipQuad allFlips[], int *flippableEcount) {
	
	
	if(valueInArray(vertex1, vertex2, allFlips)){
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
        printf("flippable edge: (%d,%d)\n", allFlips[i].edge1.ver1, allFlips[i].edge1.ver2);
    puts("==========");
}

//remove edge ver1 -> ver2 from current graph, vertices referenced by their name
void removeEdgge(char vertex1[], char vertex2[], Vertex *arr_vert[]){
	Arc *a;
	Arc *prev;
	for(int i = 0; i < NUMOFVERTICES; i++){
		prev = arr_vert[i]->arcs;
		for(a = arr_vert[i]->arcs; a; a = a->next){
			//printf("current: %s\n",a->tip->name);
			//printf("previous: %s\n",prev->tip->name);
			if(!strcmp(vertex1,arr_vert[i]->name) && !strcmp(vertex2,a->tip->name)){
				printf("removed edge (%s, %s)\n", arr_vert[i]->name, a->tip->name);
				prev->next = a->next;
				//free(a);
			}
			else if(!strcmp(vertex2,arr_vert[i]->name) && !strcmp(vertex1,a->tip->name)){
				//remove arc from the linked list
				printf("removed edge (%s, %s)\n", arr_vert[i]->name, a->tip->name);
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

void flipPossible(Vertex *v1, Vertex *v2, flipQuad allFlips[])/*not working*/{

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
	if(valueInArray(atoi(v1->name), atoi(v2->name), allFlips)){
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
	*/


	for(int i = 0; i<NUMOFVERTICES ; i++){
		for(int j = 0; j<NUMOFVERTICES ; j++){
			if(i == j){continue;}
			for(int k = 0; k<NUMOFVERTICES ; k++){
				if(k == i || k == j){continue;}
				for(int l = 0; l<NUMOFVERTICES ; l++){
					if(l == i || l == j || l == k){continue;}
					for(a = arr_vert[i]->arcs; a; a = a->next){
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
					/*for(a = arr_vert[j]->arcs; a; a = a->next){
						if(a->tip == arr_vert[k]){
							flippable += 1;
						}
					}*/
					for(a = arr_vert[k]->arcs; a; a = a->next){
						if(a->tip == arr_vert[l]){
							flippable += 1;
						}
					}
					if(flippable == 4){
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


flippableEdge getOtherPair(char vertex1[], char vertex2[], flipQuad allFlips[]){
    int i;
    for(i = 0; i < 101; i++){
        if((allFlips[i].edge1.ver1 == atoi(vertex1) && allFlips[i].edge1.ver2 == atoi(vertex2)) || (allFlips[i].edge1.ver1 == atoi(vertex2) && allFlips[i].edge1.ver2 == atoi(vertex1))){
            return allFlips[i].edge2;
        }
    }

    flippableEdge empty;
    return empty;
}


// getsgraph as input and returns another graph with flipped edge
Graph* flipOneEdge(Graph *old, char vertex1[], char vertex2[], flipQuad allFlips[]){

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

	//edges

	for(v = old->vertices; v < old->vertices + old->n; v++){
		for(a = v->arcs; a; a = a->next){
			gb_new_arc(new_vert_arr[atoi(v->name)],new_vert_arr[atoi(a->tip->name)]);
		}
	}

	//flip the specified edges in the new graph

	flippableEdge newEdge = getOtherPair(vertex1, vertex2, allFlips);
	gb_new_edge(new_vert_arr[newEdge.ver1], new_vert_arr[newEdge.ver2], 1L);
	printf("new edge added: %d, %d\n", newEdge.ver1,newEdge.ver2);
	removeEdgge(vertex1, vertex2, new_vert_arr);

	//return new graph with flipped edge
	return new;

}

int main(){
	Area s;
	Vertex *arr_vert[NUMOFVERTICES];

	//Constructing triangulated graph, 9-critical, reference 12.57.1 from Boutin paper
	Graph *triang = restore_graph("triang.gb");
	arr_vert[0] = triang->vertices;

	for (int i=1; i<NUMOFVERTICES;i++){
		arr_vert[i] = arr_vert[0] + i;
	}

	flipQuad allFlips[100];

	//initiaze to all 0s, was cousing problems, due to some values in memory
	for (int i=1; i<sizeof(allFlips)/sizeof(allFlips[0]); i++){
		allFlips[i].edge1.ver1 = 0;
		allFlips[i].edge1.ver2 = 0;
		allFlips[i].edge2.ver1 = 0;
		allFlips[i].edge2.ver2 = 0;
	}

	int flippableEcount = 0;

	//adjecancy matrix for the graph
	int adjecancyMatrix[NUMOFVERTICES][NUMOFVERTICES];

	//populating adjecancy matrix

	//populating with dummy 0s
	initiateMatrix(adjecancyMatrix);

	//print the matrix for tdebugging
	//printMatrix(adjecancyMatrix);

	//pupulating matrix with 1s where there is an edge

	updateArcsInMatrix(adjecancyMatrix, &arr_vert);
	
	//print the matrix for tdebugging
	//printMatrix(adjecancyMatrix);	

	//raising the matrix to the n power
	int result[NUMOFVERTICES][NUMOFVERTICES];
	initiateMatrix(result);

	//printf("\n");

	//square the matrix to the power of n and save it to result
	squareMatrix(adjecancyMatrix,result, 1);

	//print result of the operation to the nth power
	//printMatrix(result);

	makeFlipList(&arr_vert, allFlips, &flippableEcount);



	//TESTING FLIPS

	//print matric before flip
	squareMatrix(adjecancyMatrix,result, 3);
	//printMatrix(result);

	//flip edge
	//removeEdgge("1", "2");
	//gb_new_edge(arr_vert[9],arr_vert[10]);
	

	//print matrix after flip
	initiateMatrix(adjecancyMatrix);
	updateArcsInMatrix(adjecancyMatrix,&arr_vert);
	squareMatrix(adjecancyMatrix,result, 3);
	//printMatrix(result);

	//EEND OF TESTING FLIPS

	printf("%d\n", flippableEcount);
	listTuples(allFlips, &flippableEcount);
	//flipPossible(arr_vert[2],arr_vert[3], allFlips);


	Graph *test = flipOneEdge(triang, "0", "3", allFlips);
	save_graph(test, "new.gb");

	
	/*define flip function*/
	/* eliminating valse positives */
	/* flip two flippable edges and check numbers of paths_2 before and after*/
}