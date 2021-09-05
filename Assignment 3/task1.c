#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node Node;
struct Node{
    char  data;
    int freq;
    struct Node *left;
    struct Node *right;
    struct Node *parent;

};

void tree_insert ( Node* root, char data );
Node* tree_search ( Node* root, char data );
void tree_print_sorted ( Node* root );
void tree_delete (Node* root );

Node* leftmost(Node* root);
Node* right_sib(Node* node);

int main(){
    Node *root = (Node*)malloc(sizeof(Node));
    Node *temp = (Node*)malloc(sizeof(Node));
    Node *temp2 = (Node*)malloc(sizeof(Node));
    root->right = NULL;
    root->left = NULL;
    root->data = 'L'; // one of  midpoints when sorted 
    char string[29] = {'F',  'O', 'C', 'C' ,'I', 'N', 'A', 'U', 'C', 'I' ,'N', 'I', 'H', 'I', 'L', 'I', 'P' ,'I', 'L', 'I', 'F', 'I' ,'C', 'A', 'T', 'T', 'I', 'O', 'N'  };

    for (int i = 0; i<29; i++){
        printf("\ninput: %d ", i);
        tree_insert(root, string[i]);
       
    }
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i<2; i++){      // doing random character checks
        char check = rand() %91;
        while (check <= 65){
            check = rand() % 91;
        }
        temp2 =tree_search(root, check);
        if (temp2 == NULL ){
         printf("\n%c is not in the bst.\n", check);
        }
        else
          printf("\n %c is in the bst\n", temp2->data);
    }
    printf("Sorted:");
    tree_print_sorted(root);
    tree_delete(root);
    return 0;
}

void tree_insert ( Node* root, char data ){
    int level = 0;
    Node *next = (Node*)malloc(sizeof(Node));
    Node *temp = (Node*)malloc(sizeof(Node));
    Node *prev = (Node*)malloc(sizeof(Node));
    prev = NULL;
    temp = root;
    bool cond = true;
    while (cond){
        if (data <= temp->data ){
            //if (data == temp->data){
               // cond = false;
                //break;
            //}
            if (temp->left == NULL){
                //printf("left ");
                temp->left = (Node*)malloc(sizeof(Node));
                temp->left->data = data;
                temp->left->right = NULL;
                temp->left->left = NULL;
                temp->left->parent = temp;
                break;
            }
            else{
                temp = temp->left;
                level++;
            }
        }
        else if (data > temp->data) {
            if (temp->right == NULL){
                //printf("right ");
                temp->right = (Node*)malloc(sizeof(Node));
                temp->right->data = data;
                temp->right->right = NULL;
                temp->right->left = NULL;
                temp->right->parent = temp;
                break;
            }
            else{
                temp = temp->right;
                level++;
            }
        }
    }

    
    
    printf("%d\n", level);


}

Node* tree_search ( Node* root, char data ){
    Node *next = (Node*)malloc(sizeof(Node));
    Node *temp = (Node*)malloc(sizeof(Node));
    Node *prev = (Node*)malloc(sizeof(Node));
    prev = NULL;
    temp = root;
    while ((true)){
        if (data < temp->data ){
            //printf("left");
            
            if( temp->left == NULL){
                return NULL;
            }
            else   
                temp = temp->left;
        }
        else if (data > temp->data) {
            //printf("right");
            if (temp->right == NULL){
                return NULL;
            }
            else 
                temp = temp->right;
        }
        else 
            return temp;
    }

}

void tree_print_sorted ( Node* root ){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp = root;
    if (temp == NULL){ //if NULL go back to func
        return;
    }
    //recurses on left child
    tree_print_sorted(temp->left);

    if (temp != NULL){  // if node is not NULL prints its data
        printf(" %c ", temp->data);
    }
    //recurses on right child
    tree_print_sorted(temp->right);
}

void tree_delete (Node* root ){
    Node *del = (Node*)malloc(sizeof(Node));
    del = root;
    if (del == NULL){
        return;  //if NULL go back to func
    }

    tree_delete(del->left); // delete recurse left goes to leftmost and deletes it
    tree_delete(del->right);   // delete recurse right deletes  any right subtrees

    //deletes current node which now only has null children
    free(del);
}


Node* leftmost(Node* root){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp = root;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

Node* right_sib(Node* node){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp = node;
    temp = temp->parent;
    
    temp = temp->right;
    return temp;
    
}

