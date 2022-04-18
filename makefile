CC = gcc

compile:
	@$(CC) -w -o makeGraph12 makeGraph12.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph12_layer2 makeGraph12_layer2.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph13 makeGraph13.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph13_layer2 makeGraph13_layer2.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph14 makeGraph14.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph14_layer2 makeGraph14_layer2.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph15 makeGraph15.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph15_layer2 makeGraph15_layer2.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph16 makeGraph16.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o makeGraph16_layer2 makeGraph16_layer2.c gb_graph.c gb_save.c gb_io.c
	@$(CC) -w -o reverseSearch reverseSearch.c gb_graph.c gb_save.c gb_io.c gb_basic.c
	@$(CC) -w -o saveGraph saveGraph.c gb_graph.c gb_save.c gb_io.c