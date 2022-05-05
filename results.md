## 12

from triang.gb 

(2,3) to (0,11)

(2,7) to (0,10)

(2,9) to (1,11)

(2,11) to (0,1)

(1,11) to (0,9)

(1,9) to (0,8)

(8,9) to (0,4)


neighbours 0, 1 and 4 are in reverse search tree

lower layer

(1,4) to (0,7)

(4,5) to (2,10)

(4,6) to (2,7)

(4,10) to (2,3)

(3,10) to (2,9)

(4,7) to (0,2)

(2,4) to (0,3)

(6,7) to (2,11)

(7,11) to (1,2)

(2,11) to (1,6)



69978 from v
31810 from v2

## 13
top

	Graph *first = Adj(v13, 8);
	Graph *second = Adj(first, 9);
	Graph *third = Adj(second, 13);
	Graph *fourth = Adj(third, 9);
	Graph *fifth = Adj(fourth, 9);
	Graph *six = Adj(fifth, 6);
	Graph *seven = Adj(six, 8);
	Graph *eight = Adj(seven, 10);
	Graph *nine = Adj(eight, 8);
	//done
	Graph *ten = Adj(nine, 14);

bottom

	Graph *first = Adj(v13, 4);
	Graph *second = Adj(first, 8);
	Graph *third = Adj(second, 10);
	Graph *fourth = Adj(third, 13);
	Graph *fifth = Adj(fourth, 15);
	Graph *six = Adj(fifth, 18);
	Graph *seven = Adj(six, 24);
	Graph *eight = Adj(seven, 31);

## 14
top

	Graph *first = Adj(v14, 4);
	Graph *second = Adj(first, 5);
	Graph *third = Adj(second, 12);
	Graph *fourth = Adj(third, 16);
	Graph *fifth = Adj(fourth, 16);
	Graph *six = Adj(fifth, 17);

bottom

	Graph *first = Adj(v14, 13);
	Graph *second = Adj(first, 17);
	Graph *third = Adj(second, 19);
	Graph *fourth = Adj(third, 20);
	Graph *fifth = Adj(fourth, 24);
	Graph *six = Adj(fifth, 26);
	Graph *seven = Adj(six, 30);
	Graph *eight = Adj(seven, 30);
	Graph *nine = Adj(eight, 26);
	Graph *ten = Adj(nine, 24);
	Graph *eleven = Adj(ten, 27);
	Graph *twelve = Adj(eleven, 26);

## 15

top layer


	Graph *first = Adj(v15, 22);
	Graph *second = Adj(first, 22);
	Graph *third = Adj(second, 9);
	Graph *fourth = Adj(third, 13);
	Graph *fifth = Adj(fourth, 29);
	Graph *six = Adj(fifth, 28);
	Graph *seven = Adj(six, 22);
	Graph *eight = Adj(seven, 32);
	Graph *nine = Adj(eight, 34);
	Graph *ten = Adj(nine, 35);
	Graph *eleven = Adj(ten, 40);
	Graph *twelve = Adj(eleven, 41);
	Graph *tt = Adj(twelve, 43);
	Graph *ft = Adj(tt, 46);
	Graph *fft = Adj(ft, 53);

 11,12 to 1,9

 3,11 to 1, 14

 some others


bottom layer

	Graph *first = Adj(v15, 8);
	Graph *second = Adj(first, 12);
	Graph *third = Adj(second, 18);
	Graph *fourth = Adj(third, 21);
	Graph *fifth = Adj(fourth, 29);
	Graph *six = Adj(fifth, 37);
	Graph *seven = Adj(six, 19);
	Graph *eight = Adj(seven, 26);
	Graph *nine = Adj(eight, 23);
	Graph *ten = Adj(nine, 31);
	Graph *eleven = Adj(ten, 38);
	Graph *twelve = Adj(eleven, 21);
	Graph *tt = Adj(twelve, 21);
	Graph *ft = Adj(tt, 43);
	Graph *fft = Adj(ft, 42);

## 16

top layer

(4,12) to (0,11) - 18

(6,10) to (2,9) - 22

(7,8) to (1,12) - 25

(9,10) to (2,3) - 28

(9,15) to (3,6) - 32

(3,10) to (2,13) - 28

(6,15) to (3,14) - 32

(11,13) to (4,12) - 34

(12,13) to (4,7) - 44

(10,13) to (0,2) - 41

(2,13) to (0,3) - 27

(2,3) to (0,9) - 20

(2,9) to (0,6) - 21

(2,6) to (0,14) -22

(2,14) to (0,15) - 27

(12,15) to (2,8) -49

(2,15) to (0,8) - 32

(8,12) to (1,2) - 44

(2,8) to (0,1) - 31

(2,12) to (1,10) -45

(13,15) to (3,5) - 58

(5,13) to (1,3) - 55

bottom layer

	Graph *first = Adj(v16, 30);
	Graph *second = Adj(first, 31);
	Graph *third = Adj(second, 30);
	Graph *fourth = Adj(third, 31);
	Graph *fifth = Adj(fourth, 33);
	Graph *six = Adj(fifth, 37);
	Graph *seven = Adj(six, 27);
	Graph *eight = Adj(seven, 14);
	Graph *nine = Adj(eight, 18);
	Graph *ten = Adj(nine, 35);
	Graph *eleven = Adj(ten, 45);
	Graph *twelve = Adj(eleven, 49);
	Graph *tt = Adj(twelve, 43);
	Graph *ft = Adj(tt, 30);
	Graph *fft = Adj(ft, 33);






## mrkdy

	//Graph *first = Adj(v16, );
	//Graph *second = Adj(first, );
	//Graph *third = Adj(second, );
	//Graph *fourth = Adj(third, );
	//Graph *fifth = Adj(fourth, );
	//Graph *six = Adj(fifth, );
	//Graph *seven = Adj(six, );
	//Graph *eight = Adj(seven, );
	//Graph *nine = Adj(eight, );
	//Graph *ten = Adj(nine, );
	//Graph *eleven = Adj(ten, );
	//Graph *twelve = Adj(eleven, );
	//Graph *tt = Adj(twelve, );
	//Graph *ft = Adj(tt, );
	//Graph *fft = Adj(ft, );






		printf("test ==========================================\n");

	//TEST SECTON SKIP


	//12 UPPER LAYER

	//Graph *v = restore_graph("root12.gb");

	//strcpy(v->id, rootID);

	//flippableListOfGraph(v);

	//12 UPPER LAYER END


	//12 LOWER LAYER

	//Graph *v2 = restore_graph("root12_l2.gb");
	//strcpy(v2->id, rootID);

	//flippableListOfGraph(v2);


	//12 LOWER LAYER END

	//13 UPER LAYER

	//Graph *v13 = restore_graph("root13.gb");
	//strcpy(v13->id, rootID);

	//flippableListOfGraph(v13);
	//13 UPPER LAYER END

	//13 LOWER LAYER

	//Graph *v13 = restore_graph("root13_l2.gb");
	//strcpy(v13->id, rootID);

	//flippableListOfGraph(v13);
	//13 LOWER LAYER END


	//14 UPER LAYER

	//Graph *v14 = restore_graph("root14.gb");
	//strcpy(v14->id, rootID);

	//flippableListOfGraph(v14);
	//14 UPPER LAYER END

	//14 LOWER LAYER

	//Graph *v14 = restore_graph("root14_l2.gb");
	//strcpy(v14->id, rootID);

	//flippableListOfGraph(v14);
	//14 LOWER LAYER END

	//15 UPPER LAYER

	//Graph *v15 = restore_graph("root15.gb");
	//strcpy(v15->id, rootID);

	//flippableListOfGraph(v15);
	//15 UPPER LAYER END

	//15 LOWER LAYER

	//Graph *v15 = restore_graph("root15_l2.gb");
	//strcpy(v15->id, rootID);

	//flippableListOfGraph(v15);
	//15 LOWER LAYER END

	//16 UPPER LAYER

	//Graph *v16 = restore_graph("root16.gb");
	//strcpy(v16->id, rootID);

	//flippableListOfGraph(v16);
	//16 UPPER LAYER END

	//16 LOWER LAYER


	//Graph *v16 = restore_graph("v_16_l2.gb");
	//strcpy(v16->id, rootID);

	//flippableListOfGraph(v16);

	//16 LOWER LAYER END


	/*
	for(int i = 0; i < 26;i++){
		int testReverse = reverse(v15, i);
		if(testReverse){
			printf("%d\n", i);
		}
		
	}
	*/