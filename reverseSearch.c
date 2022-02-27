#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gb_graph.h"  
#include "gb_save.h"

#define NUMOFVERTICES 12

Area s;
Vertex *arr_vert[12];

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
void updateArcsInMatrix(int mat1[NUMOFVERTICES][NUMOFVERTICES]){
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

//defining tuple for storing flippable edges
typedef struct {
    int ver1;
    int ver2;
} flippableEdge;

//helper functions to manipulate tuples of flippable edges
static flippableEdge allFlips[100];
static int flippableEcount = 0;

int valueinarray(int vertex1, int vertex2){
    int i;
    for(i = 0; i < sizeof(allFlips) / sizeof(allFlips[0]); i++){
        if((allFlips[i].ver1 == vertex1 && allFlips[i].ver2 == vertex2)|| (allFlips[i].ver1 == vertex2 && allFlips[i].ver2 == vertex1) ){
            return 1;
        }
    }
    return 0;
}


//add flippable edge to the array of flippable edges
void addTuple(int vertex1, int vertex2) {
	if(valueinarray(vertex1, vertex2)){
		return;
	}
    allFlips[flippableEcount].ver1 = vertex1;
    allFlips[flippableEcount++].ver2 = vertex2;
}

//list all flippable edges
void listTuples(void) {
    for (int i = 0; i < flippableEcount; ++i)
        printf("flippable edge: (%d,%d)\n", allFlips[i].ver1, allFlips[i].ver2);
    puts("==========");
}

//remove edge ver1 -> ver2 from current graph, vertices referenced by their name
void removeEdgge(char vertex1[], char vertex2[]){
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
	printf("kundovina\n");
	printf("neighbours(%s,%s)\n", v1->name, v2->name);
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

void flipPossible(Vertex *v1, Vertex *v2){

	/*
	i -> j 
	i -> k done
	i -> l
	k -> l
	*/

	Arc *temp1;
	Arc *temp2;
	int mrdka = 0;
	
	if(neighbours(v1, v2)){
		for(temp1 = v1->arcs;temp1;temp1=temp1->next){
			//printf("%s to %s\n",v1->name ,temp1->tip->name);
			for(temp2 = temp1->tip->arcs;temp2;temp2=temp2->next){
				//printf("%s to %s\n",temp1->tip->name ,temp2->tip->name);
				if(!strcmp(temp2->tip->name,v2->name)){
					printf("%s to %s\n",temp1->tip->name ,temp2->tip->name);
					mrdka++;
				}
			}
			printf("\n");
		}
		if(mrdka >= 2){
			printf("flippable\n");
		}
		else{
			printf("not flippable, mrdka: %d\n", mrdka);
		}
	}
	

}

int main(){

	//Constructing triangulated graph, 9-critical, reference 12.57.1 from Boutin paper
	Graph *triang = gb_new_graph(NUMOFVERTICES);
	arr_vert[0] = triang->vertices;

	for (int i=1; i<NUMOFVERTICES;i++){
		arr_vert[i] = arr_vert[0] + i;
	}

	//printf(triang->id);

	arr_vert[0]->name = gb_save_string("0");
	arr_vert[1]->name = gb_save_string("1");
	arr_vert[2]->name = gb_save_string("2");
	arr_vert[3]->name = gb_save_string("3");
	arr_vert[4]->name = gb_save_string("4");
	arr_vert[5]->name = gb_save_string("5");
	arr_vert[6]->name = gb_save_string("6");
	arr_vert[7]->name = gb_save_string("7");
	arr_vert[8]->name = gb_save_string("8");
	arr_vert[9]->name = gb_save_string("9");
	arr_vert[10]->name = gb_save_string("10");
	arr_vert[11]->name = gb_save_string("11");


	gb_new_edge(arr_vert[0],arr_vert[7],1L);
	gb_new_edge(arr_vert[0],arr_vert[2],1L);
	gb_new_edge(arr_vert[0],arr_vert[3],1L);
	gb_new_edge(arr_vert[3],arr_vert[7],1L);
	gb_new_edge(arr_vert[3],arr_vert[2],1L);
	gb_new_edge(arr_vert[3],arr_vert[11],1L);
	gb_new_edge(arr_vert[3],arr_vert[8],1L);
	gb_new_edge(arr_vert[3],arr_vert[5],1L);
	gb_new_edge(arr_vert[3],arr_vert[6],1L);
	gb_new_edge(arr_vert[3],arr_vert[1],1L);
	gb_new_edge(arr_vert[1],arr_vert[6],1L);
	gb_new_edge(arr_vert[1],arr_vert[5],1L);
	gb_new_edge(arr_vert[1],arr_vert[8],1L);
	gb_new_edge(arr_vert[1],arr_vert[9],1L);
	gb_new_edge(arr_vert[1],arr_vert[2],1L);
	gb_new_edge(arr_vert[1],arr_vert[10],1L);
	gb_new_edge(arr_vert[10],arr_vert[7],1L);
	gb_new_edge(arr_vert[10],arr_vert[2],1L);
	gb_new_edge(arr_vert[11],arr_vert[2],1L);
	gb_new_edge(arr_vert[11],arr_vert[4],1L);
	gb_new_edge(arr_vert[11],arr_vert[8],1L);
	gb_new_edge(arr_vert[11],arr_vert[9],1L);
	gb_new_edge(arr_vert[9],arr_vert[2],1L);
	gb_new_edge(arr_vert[9],arr_vert[4],1L);
	gb_new_edge(arr_vert[9],arr_vert[8],1L);
	gb_new_edge(arr_vert[5],arr_vert[6],1L);
	gb_new_edge(arr_vert[8],arr_vert[4],1L);
	gb_new_edge(arr_vert[2],arr_vert[7],1L);

	//adjecancy matrix for the graph
	int adjecancyMatrix[NUMOFVERTICES][NUMOFVERTICES];

	//populating adjecancy matrix
	//helper arc and vertex
	Vertex *v;
	Arc *a;

	//populating with dummy 0s
	initiateMatrix(adjecancyMatrix);

	//print the matrix for tdebugging
	//printMatrix(adjecancyMatrix);

	//pupulating matrix with 1s where there is an edge

	updateArcsInMatrix(adjecancyMatrix);
	
	//print the matrix for tdebugging
	//printMatrix(adjecancyMatrix);	

	//raising the matrix to the n power
	int result[NUMOFVERTICES][NUMOFVERTICES];
	initiateMatrix(result);

	printf("\n");

	//square the matrix to the power of n and save it to result
	squareMatrix(adjecancyMatrix,result, 1);

	//print result of the operation to the nth power
	//printMatrix(result);
	

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
						addTuple(atoi(arr_vert[i]->name),atoi(arr_vert[k]->name));

						//remove edge i -> from the grahp
						//add edge k -> l to the graph

					}					
					flippable = 0;
				}
			}
		}
	}

	//TESTING FLIPS

	squareMatrix(adjecancyMatrix,result, 3);
	//printMatrix(result);

	//save_graph(triang, "triang.gb");
	//removeEdgge("1", "2");
	//gb_new_edge(arr_vert[9],arr_vert[10]);
	
	initiateMatrix(adjecancyMatrix);
	updateArcsInMatrix(adjecancyMatrix);
	squareMatrix(adjecancyMatrix,result, 3);
	//printMatrix(result);


	flipPossible(arr_vert[3],arr_vert[7]);
	//end of test flip

	listTuples();

	//4 legal (1,2 to 9,10) = -11, +12
	//3 legal (1,2 to 9,10) = -10, +7


	//4 illegal (8,11 to 3,9) = -2, +30
	//3 illegal (8,11 to 3,9) = -7, +12


	/*define flip function*/
	/* eliminating valse positives */
	/* flip two flippable edges and check numbers of paths_2 before and after*/

}