#include <stdio.h>
#include <stdlib.h>

struct node {
        int data;
        int height;
        struct node* pred;
        struct node* left;
        struct node* right;
};

struct node* newnode(int x){
        struct node* n;
        n = malloc(sizeof(struct node));
        n->data = x;
        n->height = 0;
        n->pred = NULL;
        n->left = NULL;
        n->right = NULL;
        return n;
}

struct node* search(struct node* node, int x){
        if (node == NULL){
                return NULL;
        }
        else if (x == node->data){
                return node;
        }
        else if (x < node->data){
                return search(node->left,x);
        }
        else{
                return search(node->right,x);
        }
}

struct node* rotation(struct node* node, int bal){
        struct node* temp;
        if (bal > 1){
                if (node->right == NULL){
                        temp = node;
                        node = node->left;
                        node->right = temp;
                        return node;
                }
        }

        else if (bal < 1){

        }
}

struct node* insert(struct node* node, int x){
        if (node ==  NULL){
                struct node* node = newnode(x);
                return node;
        }

        if (x < node->data){
                node->left = insert(node->left,x);
                node->left->pred = node;
                node->height += 1;
                if (node->pred == NULL){
                        if (node->left->height != 0 && node->right == NULL){
                                int valleft = node->left->height;
                                node = rotation(node, valleft + 1);
                        }
                }
        }
        else if(x > node->data){
                node->right = insert(node->right,x);
                node->right->pred = node;
        }

        return node;
}

struct node* find_the_min(struct node* node){
        if(node == NULL){
                return NULL;
        } else if (node->left == NULL) {
                return node;
        } else {
                find_the_min(node->left);
        }

        return node;
}

struct node* delete(struct node* node, int x){
        if(node == NULL){
                return node;
        }

        if (x < node->data){
                node->left = delete(node->left,x);
        }
        else if (x > node->data){
                node->right = delete(node->right,x);
        }
        else {
                if (node->left == NULL && node->right == NULL){
                        free(node);
                        return NULL;
                }

                else if(node->left == NULL || node->right == NULL){
                        struct node* temp;

                        if(node->left == NULL){
                                temp = node->right;
                        } else {
                                temp = node->left;
                        }

                        free(node);
                        return temp;
                }
                else {
                        struct node* temp = find_the_min(node->right);
                        node->data = temp->data;
                        node->right = delete(node->right, temp->data);

                }
        }

        return node;
}

void print_inorder(struct node* node) {
        if(node == NULL){
                return;
        } else {
                print_inorder(node->left);
                printf("%d \n", node->data);
                print_inorder(node->right);
        }

}

int main(){
        struct node *avl;
        avl = newnode(3);
        insert(avl,2);
        insert(avl,1);

}
