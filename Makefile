all: Flood-It

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c `sdl2-config --cflags`

API_Grille.o: API_Grille.c API_Grille.h
	gcc -c API_Grille.c `sdl2-config --cflags`

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c `sdl2-config --cflags`

Exercice_1.o: Exercice_1.c Exercice_1.h Liste_case.h
	gcc -c Exercice_1.c `sdl2-config --cflags`

Exercice_2.o: Exercice_2.c Exercice_2.h Liste_case.h
	gcc -c Exercice_2.c `sdl2-config --cflags`

Exercice_3.o: Exercice_3.c Exercice_3.h Liste_case.h
	gcc -c Exercice_3.c `sdl2-config --cflags`

Exercice_4.o: Exercice_4.c Exercice_4.h Liste_case.h
	gcc -c Exercice_4.c `sdl2-config --cflags`

Exercice_5.o: Exercice_5.c Exercice_5.h Liste_case.h
	gcc -c Exercice_5.c `sdl2-config --cflags`

Exercice_6.o: Exercice_6.c Exercice_6.h Liste_case.h
	gcc -c Exercice_6.c `sdl2-config --cflags`


Flood-It.o: Flood-It.c
	gcc -c Flood-It.c `sdl2-config --cflags`

Flood-It: Flood-It.o Liste_case.o  API_Grille.o API_Gene_instance.o Exercice_1.o Exercice_2.o Exercice_3.o Exercice_4.o Exercice_5.o Exercice_6.o 
	gcc -o Flood-It Flood-It.o Liste_case.o API_Grille.o API_Gene_instance.o Exercice_1.o Exercice_2.o Exercice_3.o Exercice_4.o Exercice_5.o Exercice_6.o  `sdl2-config --libs` 

clean:
	rm -f *.o Flood-It
