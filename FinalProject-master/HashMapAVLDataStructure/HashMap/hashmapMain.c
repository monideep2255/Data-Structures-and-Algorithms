#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hashmap.c"

int main(int argc, char **argv) {
    // create the table for the hashMap
    hashMap_t *hashMap = create();

    insert(hashMap, "20-25", "AVL 1");
    insert(hashMap, "30-35", "AVL 2");
    insert(hashMap, "40-45", "AVL 3");
    insert(hashMap, "50-55", "AVL 4");
    insert(hashMap, "60-65", "AVL 5");

    printHashMap(hashMap);
    free(hashMap);
    return 0;
}
