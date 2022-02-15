#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gb_graph.h"  


Area s;
int numOfVertices = 12;
Vertex *arr_vert[12];

/* reverse search and its functions*/

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

int main(){

	/*Constructing triangulated graph, 9-critical, reference 12.57.1 from Boutin paper*/

	Graph *triang = gb_new_graph(12L);
	arr_vert[0] = triang->vertices;

	for (int i=1; i<13;i++){
		arr_vert[i] = arr_vert[0] + i;
	}

	printf(triang->id);
	printf("\n");

	for (int i=0; i<13;i++){
		arr_vert[i]->name = gb_save_string("v %d",i);
		/*printf(arr_vert[i]->name);
		printf("\n");*/
	}

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

	/*Loop through all arcs*/

	Vertex *v;
	Arc *a;
	/*for(int j = 0; j<13 ; j++){
		for(a = arr_vert[j]->arcs; a; a = a->next){
			printf(arr_vert[j]->name);
			printf("\n");
			printf(a);
			printf("\n");
		}
	}*/


	int flippable = 0;

	for(int i = 0; i<13 ; i++){
		for(int j = 0; j<13 ; j++){
			if(i == j){continue;}
			for(int k = 0; k<13 ; k++){
				if(k == i || k == j){continue;}
				for(int l = 0; l<13 ; l++){
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
						/*printf("quadriteral: %s, %s, %s, %s is flipable", arr_vert[i]->name,arr_vert[j]->name,arr_vert[k]->name,arr_vert[l]->name);
						*/
						printf("quadriteral: %d, %d, %d, %d is theoretically flipable",i,j,k,l);
						printf("\n");
					}
					flippable = 0;
				}
			}
		}
	}

	/* Flips in triangularion*/
	/*Output all flipable edges (all possible flips)*/

}