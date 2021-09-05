#include "bstdb.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.
//

//sources: AVL tree insert to get balanced bst heavily inspired by https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// 
typedef struct Node Node;
struct Node{
    char * title;
    int words;
	int height;
	int UID;
    struct Node * left;
    struct Node * right;
    struct Node * parent;

};
Node * root ;
bool duplicate[200000] = {false};
bool isbalanced;
int insertions, traverses;
bool balanced(Node * root);
int gen_id();
Node * tree_insert(Node * r, char* name, int word_count, int UID);
Node * tree_search(Node * r, int doc_id);
void tree_delete (Node * root );
Node* leftmost(Node* root);

int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	printf("\nIn initialize\n");
	root = (Node*)malloc(sizeof(Node));
	root->height = 1;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	root->title = NULL;
	// root = NULL;
	isbalanced = true;
	insertions = 0;
	traverses = 0;
	return 1;
}

int
bstdb_add ( char *name, int word_count ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
	
    int UID = gen_id();
	
	
	Node *temp = (Node*)malloc(sizeof(Node));
	Node *temp2 ;
	root = tree_insert(root,name,word_count,UID);
	temp2 = root;
	// if (temp2->left != NULL){
	// 	printf("\n %s " ,temp2->left->title );
	// 	printf("\n %s " ,temp2->right->title );
	// }
	// }
	//printf("its maybe working?\n");
	
	// printf("%d \n", temp2->UID);
	
	if (temp == NULL){
		printf("something seems to have gone wrong.");
		return -1;
	}
	return UID;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
    Node *temp = NULL;
    
	temp = tree_search(root,doc_id);
	if (temp == NULL){
		return -1;
	}
	return temp->words;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	Node *temp = NULL;
    
	temp = tree_search(root,doc_id);
	if (temp == NULL){
		return NULL;
	}
	return temp->title;
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	bool checkbal = balanced(root);
	if (checkbal){
		printf("\nthe tree is balanced");
	 }
	else 
		printf("\n the tree is not balanced");
	// + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	printf("\nthere were  %d insertions\n", insertions);
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	float avgnodes = (float)traverses / (float)insertions;
	printf("\nof %d total traversals there were  %f average travrsals for search\n",traverses, avgnodes);
	Node *temp = NULL;
	temp = leftmost(root);
	printf( " the depth of the leftmost root was %d and the root is %d\n", temp->height, root->height);

	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	tree_delete(root);
}

Node* tree_search(Node* r, int doc_id){
	Node *temp = NULL;
	if (r == NULL) return temp;
	// printf("\n %d " ,r->words );
	// printf("\n %s " ,r->right->title );

	if (r->UID == doc_id){
		traverses++;
		return r;
	}
	else if (r->UID > doc_id){
		traverses++;
		temp = tree_search(r->left,doc_id);
	}
	else{
		traverses++;
		temp = tree_search(r->right,doc_id);
	}
	return temp;

}

int height(Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
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

int max(int a, int b) 
{ 
    if (a > b){
		return a;
	}  
	else return b; 
} 


Node *rightRotate( Node *y) { 
    Node *x = y->left; 
    Node *T2 = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = T2; 
  
    // Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
    // Return new root 
    return x; 
} 
/*T1, T2 and T3 are subtrees of the tree 
rooted with y (on the left side) or x (on 
the right side)           
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3
Keys in both of the above trees follow the 
following order 
 keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
So BST property is not violated anywhere.*/

Node *leftRotate( Node *x) { 
    Node *y = x->right; 
    Node *T2 = y->left; 
  
    // Perform rotation 
    y->left = x; 
    x->right = T2; 
  
    // Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    // Return new root 
    return y; 
} 
bool balanced(Node* r){
	Node *temp = (Node*)malloc(sizeof(Node));
    temp = r;
	int balance;
    if (temp == NULL){ //if NULL go back to func
        return false;
    }
    //recurses on left child
    balanced(temp->left);

    if (temp != NULL){  // if node is not NULL checks balance of children
        
		if (temp == NULL)
			balance = 0;
		else
			balance = height(temp->left) - height(temp->right);
		if ((balance > 1) || (balance < -1))
			isbalanced = false;
    }
    //recurses on right child
    balanced(temp->right);
	if (isbalanced){
		return true;
	}
	else 
		return false;
}



Node * tree_insert(Node* r, char* name, int word_count, int UID){
	
    
	Node *temp ;
	temp = (Node*)malloc(sizeof(Node));
	temp = r;
												// heavily inspired by https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
	if (temp == NULL){	
		Node *temp = (Node*)malloc(sizeof(Node));
		temp->UID = UID;
		temp->right = NULL;
		temp->left = NULL;
		temp->parent = NULL;
		temp->height = 1;
		temp->title = calloc(strlen(name) + 1, sizeof(char));
		if (temp->title)
			strcpy(temp->title , name);
		else{
			Node *del = (Node*)malloc(sizeof(Node));
			del = temp;
			free(del);
			printf("\nOh god no\n");
			temp = NULL;
		}
		temp->words = word_count;
		insertions++;
		return temp;
	}

	if (UID < temp->UID){
		temp->left = tree_insert(temp->left,name, word_count, UID);
	}
	else if(UID > temp->UID){
		temp->right = tree_insert(temp->right,name, word_count, UID);
	}
	else
		return temp;

	 // Update height of  ancestor node 
	if (height(temp->left) > height(temp->right)){
    	temp->height = 1 + height(temp->left);
	}
	else
		temp->height = 1 + height(temp->right);

	
	int balance;
	if (temp == NULL)
		balance = 0;
	else
		balance = height(temp->left) - height(temp->right);

	// If unbalanced, then there are 4 cases 
    // Left Left Case 
    if ((balance > 1) && (UID < temp->left->UID)) 
        return rightRotate(temp); 
  
    // Right Right Case 
    if ((balance < -1) && UID > (temp->right->UID)) 
        return leftRotate(temp); 
  
    // Left Right Case 
    if ((balance > 1) && (UID > temp->left->UID)) 
    { 
        temp->left =  leftRotate(temp->left); 
        return rightRotate(temp); 
    } 
  
    // Right Left Case 
    if ((balance < -1) && (UID < temp->right->UID)) 
    { 
        temp->right = rightRotate(temp->right); 
        return leftRotate(temp); 
    } 
  
    // return the (unchanged) node pointer 
    return temp; 
	
	

}

int gen_id(){
	static int count= 0;
	// static bool left = true;
	// long mid = 75000;

	// if (count == 0){
	// 	count++;
	// 	return mid;
	// }
	// else if (left){
	// 	mid = mid - count;
	// 	left = !left;
	// 	return mid;
	// }
	// else {
	// 	mid = mid + count;
	// 	count++;
	// 	left = !left;
	// 	return mid;
	// }
	count++;
	return count;


	// time_t t;
	// int UID;
	// srand((unsigned)time(&t));
	// static bool first = true;
	// if (first){
	// 	first = false;
		
	// 	UID =  75000;
	// }
	
	// else{
	// UID = rand() % 150000;
	// while (duplicate[UID]){
		
		
	// 	UID = rand() % 150000;
	// }
	// }
	
	// duplicate[UID] = true;
	// return UID;

	
	


}
Node* leftmost(Node* root){
    Node *temp = (Node*)malloc(sizeof(Node));
    temp = root;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}