#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gb_graph.h"
#include "gb_save.h"


//saves a inputted graph to a file that can be inputted to pythons networkx library for drawing
int main(){
	Area s;
	FILE *fptr;
	FILE *fptr2;

	//Constructing triangulated graph, 9-critical, reference 12.57.1 from Boutin paper
	Graph *triang = restore_graph("v.gb");

	Vertex *arr_vert[triang->n];
	arr_vert[0] = triang->vertices;

	for (int i=1; i<triang->n;i++){
		arr_vert[i] = arr_vert[0] + i;
	}

	Vertex *v; 
	Arc *a;

	fptr = fopen("./resultEdges.graph","w");
	fptr2 = fopen("./resultVertices.graph","w");

	for(v = triang->vertices; v < triang->vertices + triang->n; v++){
		fprintf(fptr2, "%s\n", v->name);
		for(a = v->arcs; a; a = a->next){
			fprintf(fptr, "%s %s\n", v->name, a->tip->name);
		}
	}

}