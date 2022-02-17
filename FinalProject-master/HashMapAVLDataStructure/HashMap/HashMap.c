/*
 * Implementation of a hashMap AVL tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Important for the macros, helps to determine the set limits of variable data types
#include <limits.h>

/*
 * Define the size of the hashMap
 * This is the maximum number of items that can be stored in the hashMap before there is a collision.
 */ 

#define MAX_SIZE 100

//Node struct with its assoicated fields.
//data - stores user IDs.
//name - name of individual.
//sex - gender of individual.
//salary - income yearly.
//height - height of node.
//left - pointer to left child.
//right - pointer to right child.
typedef struct node{
        int data; 
	char* name; 
	char* sex; 
	int salary; 
        int height; 
        struct node* left;
        struct node* right;
}node_t;

//AVL tree structure.
//root - root node.
//numNodes - number of nodes in the tree.
typedef struct tree{
        node_t* root;
        int numNodes;
}tree_t;

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

//Function creates a node.
node_t* makeNode(int data){
        node_t* newNode = (node_t*)malloc(sizeof(node_t));
        newNode->data = data;
        newNode->height = 0;
        newNode->left = NULL;
        newNode->right = NULL;
}

//Converts and determines the height of a node in a subtree.
int heightConvert(node_t* node){
        if (node == NULL){
                return -1;
        }

        return node->height;
}

//Function comapres the height of the parent nodes from the left
//and right subtree. The node with a greater height is returned.
int maxHeight(int heightLeft, int heightRight){
        if (heightLeft > heightRight){
                return heightLeft;
        }

        return heightRight;
}

//Rotation function used to rotate nodes.
node_t* rotation(node_t* node, int bal, int data){
        //Declaring temporary storage variables.
	node_t* temp1;
        node_t* temp2;

	//Balance greater than 1 represents a left heavy tree.
        if (bal > 1){
		// Left-Left Scenario where a right rotation is used to
		// balance the tree.
                if (node->left->data > data){
                        temp1 = node->left->right;
                        temp2 = node->left;
                        temp2->right = node;
                        node->left = temp1;
			
			//Updating the heights of nodes that have been changed.
                        int leftH = heightConvert(temp2->right->left);
                        int rightH = heightConvert(temp2->right->right);
                        temp2->right->height = maxHeight(leftH, rightH) + 1;
			
			//New height.
                        leftH = heightConvert(temp2->left);
                        rightH = heightConvert(temp2->right);
                        temp2->height = maxHeight(leftH, rightH);

                        return temp2;
                }
		//Left-Right Scenario where a left and right rotation is performed.
                else if (node->left->data < data){
                        //left rotation
			temp1 = node->left->right->left;
                        temp2 = node->left->right;
                        temp2->left = node->left;
                        node->left->right = temp1;

                        node->left = temp2;
			
                        int leftH = heightConvert(node->left->left->left);
                        int rightH = heightConvert(node->left->left->right);
                        node->left->left->height = maxHeight(leftH, rightH);

                        leftH = heightConvert(node->left->left);
                        rightH = heightConvert(node->left->right);
                        node->left->height = maxHeight(leftH, rightH);

			//right rotation
                        temp1 = node->left->right;
                        temp2 = node->left;
                        temp2->right = node;
                        node->left = temp1;

                        leftH = heightConvert(temp2->right->left);
                        rightH = heightConvert(temp2->right->right);
                        temp2->right->height = maxHeight(leftH, rightH) + 1;

                        leftH = heightConvert(temp2->left);
                        rightH = heightConvert(temp2->right);
                        temp2->height = maxHeight(leftH, rightH);

                        return temp2;
                }
        }
	//Balance less than -1 represents a right heavy tree. 
        else if (bal < -1){
		//Right right scenario where a left rotation is used.
                if (node->right->data < data){
			//left rotation
                        temp1 = node->right->left;
                        temp2 = node->right;
                        temp2->left = node;
                        node->right = temp1;
			
                        int leftH = heightConvert(temp2->left->left);
                        int rightH = heightConvert(temp2->left->right);
                        temp2->left->height = maxHeight(leftH, rightH);

                        leftH = heightConvert(temp2->left);
                        rightH = heightConvert(temp2->right);
                        temp2->height = maxHeight(leftH, rightH);

                        return temp2;
                }

		//Right left scenario where a right left rotation is performed.
                else if (node->right->data > data){
			//right rotation.
                        temp1 = node->right->left->right;
                        temp2 = node->right->left;
                        temp2->right = node->right;
                        node->right->left = temp1;

                        int leftH = heightConvert(node->right->right->left);
                        int rightH = heightConvert(node->right->right->right);
                        node->right->right->height = maxHeight(leftH, rightH);

                        leftH = heightConvert(node->right->left);
                        rightH = heightConvert(node->right->right);
                        temp2->height = maxHeight(leftH, rightH);
			
			//left rotation.
                        node->right = temp2;
                        temp1 = node->right->left;
                        temp2 = node->right;
                        temp2->left = node;
                        node->right = temp1;

                        leftH = heightConvert(temp2->left->left);
                        rightH = heightConvert(temp2->left->right);
                        temp2->left->height = maxHeight(leftH, rightH);

                        leftH = heightConvert(temp2->left);
                        rightH = heightConvert(temp2->right);
                        temp2->height = maxHeight(leftH, rightH);

                        return temp2;
                }
        }

        return node;
}

//Insertion helper function.
//node -- takes in a node.
//newNode -- new malloced node.
//data -- desired data.
node_t* insertHelp(node_t* node, node_t* newNode, int data){
        if ((node->data) > data){
                if ((node->left) == NULL){
                        node->left = newNode;
                } else{
                        insertHelp(node->left, newNode, data);
                }
        }

        else if ((node->data) < data){
                if ((node->right) == NULL){
                        node->right = newNode;
                }
                else {
                        insertHelp(node->right, newNode, data);
                }
        }
        
        int leftH = heightConvert(node->left);
        int rightH = heightConvert(node->right);
        node->height = maxHeight(leftH, rightH) + 1;

        int balance = heightConvert(node->left) - heightConvert(node->right);
        node_t* newRoot = rotation(node,balance,data);

        return newRoot;
}

//Insertion function.
//tree -- AVL tree.
//data -- desired data.
tree_t* insertion(tree_t* tree, int data){
        node_t* newNode = makeNode(data);
        if (tree->root == NULL){
                tree->root = newNode;
                return tree;
        }

        node_t* newRoot = insertHelp(tree->root, newNode, data);

        tree->root = newRoot;
        return tree;
}

//Print helper function.
//node -- root node.
void printHelp(node_t* node){
        if (node == NULL){
                return;
        }
        printHelp(node->left);
        printf("%d ", node->data);
        printHelp(node->right);
}

//Print function.
//tree - takes in a AVL tree structure.
void print(tree_t* tree){
        if (tree == NULL){
                return;
        }
        printHelp(tree->root);
}

// This function is to allocate memory to the key - value pairs entered into the hashMap
pair_t *hMap_pair(char *key, tree_t* value) {
    pair_t *entered = malloc(sizeof(pair_t));
    entered->key = malloc(strlen(key) + 1);
    entered->value = (tree_t*)malloc(sizeof(tree_t));

    // copy the key
    strcpy(entered->key, key);

    // we initiliaze the next entry to be NULL
    entered->next = NULL;

    return entered;
}

// We create the hashMap where all the key - value pairs will be stored
hashMap_t *create() {
    // assign memory to the hashTable that will be created to store the key - value pairs
    hashMap_t *hashTable = malloc(sizeof(hashMap_t));

    // next we shall allocate memory to all the key - value pairs that have been entered
    hashTable->pairs = malloc(sizeof(pair_t*) * MAX_SIZE);

    // To start, we shall set all the positions on the table to be NULL
    for(int i = 0; i < MAX_SIZE; i++) {
        hashTable->pairs[i] = NULL;
    }

    return hashTable;
}

/*
 * We will be using unsigned int instead of just int because the values that we will be storing eventually from the dataset
 * will always be positive numbers
 */

/**
 * The hash function is a make or break for the hashMap. If it is implemented correctly, the key - value pairs will be 
 * distributed evenly over the indexes of the hash table and give a runtime performance of O(1). 
 * 
 * Otherwise, all the key - value pairs can be placed in one index and lead to a poor performance of O(n) which completely undermines
 * using the hashMap in the first place
 */ 
unsigned int hashFunction(char *key) {
    // initialize the index position
    unsigned int indexPosition = 0;

    // will be using the length of the string which will be crucial to determine the index position
    unsigned int lengthKey = strlen(key);

    /**
     * Using the multiplication method to use the unique index position for all our keys to store the data
     * In the method, the indexPosition is multiplied by a prime number
     * 
     * Why a prime number? A prime number helps to best distribute the data among the buckets of a hashMap
     */
    for(int i = 0; i < lengthKey; i++) {
        indexPosition = indexPosition * 31 + key[i];
    }

    // next we shall make sure that the index postion will always be within the size of the hashMap
    indexPosition = indexPosition % MAX_SIZE;

    return indexPosition;
}

// Insert function of a hashMap
void insert(hashMap_t *hashTable, char *key, tree_t* value) {
    unsigned int bucket = hashFunction(key);

    // Firstly, we shall look up the bucket
    pair_t *entered = hashTable->pairs[bucket];

    // if the bucket is NULL, insertion takes place
    if (entered == NULL) {
        hashTable->pairs[bucket] = hMap_pair(key,value);
        return;
    }

    // else

    pair_t *prev;

    // In this part we shall walk through each entry until the end is reached or a matching key is found
    while(entered != NULL)
    //compare the string arguments
        if(strcmp(entered->key, key) == 0) {
            // a match was found, value to be updated
            free(entered->value);
            //assign space to the new value
            entered->value = malloc(sizeof(value));
            return;
        }

        // for the new entry, a pointer to another entry is created (single linked list)
        prev = entered;
        entered = prev->next;

        // no matching previously existing key was found, hence we add a new entry
        // implies two values at the index
        prev->next = hMap_pair(key,value);
}

// Get function of a hashMap
tree_t *get(hashMap_t *hashTable, char *key) {
    unsigned int bucket = hashFunction(key);

    // Similar to insert we shall find the bucket first
    pair_t *entered = hashTable->pairs[bucket];

    // if there is no bucket found, there was no entry
    if(entered == NULL) {
        return NULL;
    }

    // walk through each entry to find the value
    while(entered != NULL) {
        // if the value is found
        if(strcmp(entered->key, key) == 0) {
            return entered->value;
        }
        
        // if not then proceed to the next key available
        entered = entered->next;
    }

    // if the value does not exist
    return NULL;
}

// Remove function of a hashMap
void removes(hashMap_t *hashTable, char *key) {
    unsigned int bucket = hashFunction(key);

    // We again look for a valid bucket
    pair_t *entered = hashTable->pairs[bucket];

    // no bucket found means no entry
    if(entered == NULL) {
        return;
    }

    pair_t *prev;
    int index = 0;

    // The big step: we shall walk through each entry until either we reach the end or a key is matched
    while(entered != NULL) {
        // we check the keys
        if(strcmp(entered->key, key) == 0) {
            // there is an item and no next pair
            if(entered->next == NULL && index == 0) {
                hashTable->pairs[bucket] = NULL;
            }

            // there is an item with next entry
            if(entered->next != NULL && index == 0) {
                hashTable->pairs[bucket] = entered->next;
            }

            // last item
            if(entered->next == NULL && index != 0) {
                prev->next = NULL;
            }

            // middle item
            if(entered->next != NULL && index != 0) {
                prev->next = entered->next;
            }

            // we must remember to free the allocated memory
            free(entered->key);
            free(entered->value);
            free(entered);

            return;
        }

        // if we reached here, we then move to the next entry
        prev = entered;
        entered = prev->next;
        index++;
    }
}

// Print function of a hashMap
void printHashMap(hashMap_t *hashTable) {
    for(int i = 0; i < MAX_SIZE; i++) {
        pair_t *entered = hashTable->pairs[i];

        if(entered == NULL) {
            continue;
        }

        printf("Bucket[%3d] : ", i);

        for(;;) {
            printf("%s=%s ", entered->key, entered->value);
            if(entered->next == NULL) {
                break;
            }
            entered = entered->next;
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    // create the table for the hashMap
    hashMap_t *hashMap = create();
    tree_t* tree1 = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tree2 = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tree3 = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tree4 = (tree_t*)malloc(sizeof(tree_t));
    tree_t* tree5 = (tree_t*)malloc(sizeof(tree_t));
    insert(hashMap, "20-25", tree1);
    insert(hashMap, "30-35", tree2);
    insert(hashMap, "40-45", tree3);
    insert(hashMap, "50-55", tree4);
    insert(hashMap, "60-65", tree5);

    printHashMap(hashMap);
    free(hashMap);
    return 0;
}
