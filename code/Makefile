matrice.o : matrice.c matrice.h
	gcc -c -o matrice.o matrice.c

sac_a_dos.o : matrice.o sac_a_dos.c sac_a_dos.h
	gcc -c -o sac_a_dos.o sac_a_dos.c

entree_sortie.o : matrice.o sac_a_dos.o entree_sortie.c entree_sortie.h
	gcc -c -o entree_sortie.o entree_sortie.c

choix.o : matrice.o sac_a_dos.o choix.c choix.h
	gcc -c -o choix.o choix.c

comparaison.o : matrice.o entree_sortie.o comparaison.c comparaison.h
	gcc -c -o comparaison.o comparaison.c



test_sac_a_dos.o : matrice.o sac_a_dos.o test_sac_a_dos.c
	gcc -c -o test_sac_a_dos.o test_sac_a_dos.c

test_sac_a_dos : matrice.o sac_a_dos.o test_sac_a_dos.o
	gcc -Wall -o test_sac_a_dos test_sac_a_dos.o sac_a_dos.o matrice.o -lm


test_choix.o : matrice.o sac_a_dos.o entree_sortie.o choix.o test_choix.c
	gcc -c -o test_choix.o test_choix.c

test_choix : matrice.o sac_a_dos.o entree_sortie.o choix.o test_choix.o
	gcc -Wall -o test_choix test_choix.o choix.o entree_sortie.o sac_a_dos.o matrice.o -lm


test_entree_sortie.o : matrice.o sac_a_dos.o entree_sortie.o choix.o test_entree_sortie.c
	gcc -c -o test_entree_sortie.o test_entree_sortie.c

test_entree_sortie : matrice.o sac_a_dos.o entree_sortie.o choix.o test_entree_sortie.o 
	gcc -Wall -o test_entree_sortie test_entree_sortie.o choix.o entree_sortie.o sac_a_dos.o matrice.o -lm


test_comparaison.o : matrice.o sac_a_dos.o entree_sortie.o choix.o comparaison.o test_comparaison.c
	gcc -c -o test_comparaison.o test_comparaison.c

test_comparaison : matrice.o sac_a_dos.o entree_sortie.o choix.o comparaison.o test_comparaison.o
	gcc -Wall -o test_comparaison test_comparaison.o comparaison.o choix.o entree_sortie.o sac_a_dos.o matrice.o -lm


brouillon.o : matrice.o sac_a_dos.o entree_sortie.o choix.o comparaison.o brouillon.c
	gcc -c -o brouillon.o brouillon.c

brouillon : matrice.o sac_a_dos.o entree_sortie.o choix.o comparaison.o brouillon.o
	gcc -Wall -o brouillon brouillon.o matrice.o sac_a_dos.o entree_sortie.o choix.o comparaison.o -lm


clean : 
	rm *.o test_choix test_sac_a_dos