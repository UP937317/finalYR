#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gb_graph.h"  
#include "gb_save.h"

#define NUMOFVERTICES 24

Area s;
static Vertex *arr_vert[24];

int main(){

	//Constructing triangulated graph, 9-critical, reference 12.57.1 from Boutin paper
	Graph *triang = gb_new_graph(NUMOFVERTICES);
	arr_vert[0] = triang->vertices;

	for (int i=1; i<NUMOFVERTICES;i++){
		arr_vert[i] = arr_vert[0] + i;
	}

	//printf(triang->id);

	//upper part

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


	//upper part edges

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


	save_graph(triang, "triang.gb");

}