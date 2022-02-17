#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "HashMapAVL.c"


//Main function to check the performance of the hashMap AVL data structure
int main(int argc, char **argv) {
    // create the table for the hashMap
    hashMap_t *hashMap = create();
    tree_t* tree1 = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tree2 = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tree3 = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tree4 = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tree5 = (tree_t*)malloc(sizeof(tree_t));

    // insert 1
    clock_t start1 = clock();
    insert(hashMap, "20-25", tree1);
	clock_t end1 = clock();
	double total1 = (double) (end1-start1) / CLOCKS_PER_SEC;
	printf("HashMap AVL insert 1 time %f seconds\n", total1);

    // insert 2
	clock_t start2 = clock();
    insert(hashMap, "30-35", tree2);
	clock_t end2 = clock();
	double total2 = (double) (end2-start2) / CLOCKS_PER_SEC;
	printf("HashMap AVL insert 2 time %f seconds\n", total2);

    // insert 3
	clock_t start3 = clock();
    insert(hashMap, "40-45", tree3);
	clock_t end3 = clock();
	double total3 = (double) (end3-start3) / CLOCKS_PER_SEC;
	printf("HashMap AVL insert 3 time %f seconds\n", total3);

    // insert 4
	clock_t start4 = clock();
    insert(hashMap, "50-55", tree4);
	clock_t end4 = clock();
	double total4 = (double) (end4-start4) / CLOCKS_PER_SEC;
	printf("HashMap AVL insert 4 time %f seconds\n", total4);


    // insert 5
	clock_t start5 = clock();
    insert(hashMap, "60-65", tree5);
	clock_t end5 = clock();
	double total5 = (double) (end5-start5) / CLOCKS_PER_SEC;
	printf("HashMap AVL insert 5 time %f seconds\n", total5);

    printHashMap(hashMap);
    free(hashMap);
    return 0;
}