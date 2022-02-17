/**
 * HashMap header file with all the structures defined and the function signatures of the functions.
 */ 

/*
 * Represents one key - value pair into the hashMap. Note we also have a pointer to another pair value
 * for a very specific reason: if for some reason our keys return the same index, the key - value pairs
 * will be stored on the same index with pointers to different entries (single linked list).
 */ 
typedef struct pair_t {
    char *key;
    char *value;
    struct pair_t *next;
} pair_t;

/*
 * Represents the hashMap: it is an array of pointers to  key - value pairs.
 */ 
typedef struct {
    pair_t **pairs;
} hashMap_t;

/*
 * Function to allocate memory for the keys and values in the hashMap.
 */ 
pair_t *hMap_pair(char *key, char *value);

/*
 * Create the HashMap.
 */
hashMap_t *create();

/*
 * Determine the index to store the value for the key in the HashMap by using a hash function.
 */
unsigned int hashFunction(char *key);

/*
 * Insert a key - value pair to the HashMap.
 */
void insert(hashMap_t *hashTable, char *key, char *value);

/*
 * Get a key - value pair from the HashMap.
 */
char *get(hashMap_t *hashTable, char *key);

/*
 * Removes a key - value pair to the HashMap.
 */
void removes(hashMap_t *hashTable, char *key);

/*
 * Prints the key - value pairs of the HashMap.
 */
void printHashMap(hashMap_t *hashTable);

/*
 * References:
 * 
 * 1. Grokking Algorithms by Aditya Bhargava, Chapter 5: Hash Tables
 * 2. Grokking Algorithms by Aditya Bhargava, Chapter 11: Where to Go Next
 * 3. Basics of Hash Tables by Prateek Garg, HackerEarth
 */ 