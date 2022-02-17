/*
 * HashMap and AVL header file with all the structures defined and the function signatures of the functions.
 */ 

/*
 * Represents the node in the AVL tree.
 */ 
typedef struct node{
        int data;
        int height;
        struct node* left;
        struct node* right;
}node_t;

/**
 * Represents the AVL tree.
 */ 
typedef struct tree{
        node_t* root;
        int numNodes;
}tree_t;

/*
 * Represents one key - value pair into the hashMap. Note we also have a pointer to another pair value
 * for a very specific reason: if for some reason our keys return the same index, the key - value pairs
 * will be stored on the same index with pointers to different entries (single linked list).
 */ 
typedef struct pair_t {
    char *key;
    tree_t* value; 
    struct pair_t *next;
} pair_t;

/*
 * Represents the hashMap: it is an array of pointers to  key - value pairs.
 */ 
typedef struct {
    pair_t **pairs;
} hashMap_t;

// AVL FUNCTIONS:

/*
 * Makes a node in the AVL tree.
 */ 
node_t* makeNode(int data);

/*
 * Returns the height of the AVL tree.
 */ 
int heightConvert(node_t* node);

/*
 * Finds the max height between the subtrees.
 */ 
int maxHeight(int heightLeft, int heightRight);

/*
 * Does the rotation for the AVL tree.
 */ 
node_t* rotation(node_t* node, int bal, int data);

/*
 * Search a specific value in the AVL tree.
 */
node_t* search(node_t* node, int x)
/*
 * Insert a node into the AVL tree.
 */ 
node_t* insertHelp(node_t* node, node_t* newNode, int data);

/*
 * Insert new data into the AVL tree.
 */ 
tree_t* insertion(tree_t* tree, int data);

/*
 * Print function for nodes in the AVL tree.
 */ 
void printHelp(node_t* node);

/**
 * Prints the  AVL tree.
 */ 
void print(tree_t* tree);

// HASHMAP FUNCTIONS:

/*
 * Function to allocate memory for the keys and values in the hashMap.
 */ 
pair_t *hMap_pair(char *key, tree_t* value);

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
void insert(hashMap_t *hashTable, char *key, tree_t* value);

/*
 * Get a key - value pair from the HashMap.
 */
tree_t *get(hashMap_t *hashTable, char *key);

/*
 * Removes a key - value pair to the HashMap.
 */
void removes(hashMap_t *hashTable, char *key);

/*
 * Prints the key - value pairs of the HashMap.
 */
void printHashMap(hashMap_t *hashTable);

