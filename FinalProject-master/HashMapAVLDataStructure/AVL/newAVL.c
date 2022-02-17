#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
        int data;
	int height;
        struct node* left;
        struct node* right;
}node_t;

typedef struct tree{
        node_t* root;
        int numNodes;
}tree_t;

node_t* makeNode(int data){
        node_t* newNode = (node_t*)malloc(sizeof(node_t));
        newNode->data = data;
	newNode->height = 0;
        newNode->left = NULL;
        newNode->right = NULL;
}

int heightConvert(node_t* node){
        if (node == NULL){
                return -1;
        }

        return node->height;
}

int maxHeight(int heightLeft, int heightRight){
        if (heightLeft > heightRight){
                return heightLeft;
        }

        return heightRight;
}

node_t* rotation(node_t* node, int bal, int data){
	node_t* temp1;
	node_t* temp2;
	node_t* temp3;

	if (bal > 1){
		
		if (node->left->data > data){
			temp1 = node->left->right;
			temp2 = node->left;
			temp2->right = node;
			node->left = temp1;
			
			int leftH = heightConvert(temp2->right->left);
			int rightH = heightConvert(temp2->right->right);
			temp2->right->height = maxHeight(leftH, rightH) + 1;
	
			leftH = heightConvert(temp2->left);
			rightH = heightConvert(temp2->right);
			temp2->height = maxHeight(leftH, rightH);
	
			return temp2;
		}
		
		else if (node->left->data < data){
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

	
	else if (bal < -1){
		if (node->right->data < data){
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

		else if (node->right->data > data){
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

tree_t* insert(tree_t* tree, int data){
        node_t* newNode = makeNode(data);
        if (tree->root == NULL){
                tree->root = newNode;
                return tree;
        }
        
	node_t* newRoot = insertHelp(tree->root, newNode, data);
	
	tree->root = newRoot;
	return tree;
}

void printHelp(node_t* node){
        if (node == NULL){
                return;
        }
        printHelp(node->left);
        printf("%d ", node->data);
        printHelp(node->right);
}

void print(tree_t* tree){
        if (tree == NULL){
                return;
        }
        printHelp(tree->root);
}

int main(){
        tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
        insert(tree, 7);
        insert(tree, 6);
        insert(tree, 5);
	insert(tree, 4);
	insert(tree, 3);
	printf("%d \n", tree->root->left->right->data);

	//print(tree);
        printf("\n");
}

