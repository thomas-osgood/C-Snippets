/*
 * Binary search tree program with various functions.
 *
 * To Compile:
 * 	gcc -o binarySearchTree binarySearchTree.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

/*
 * Define MACROs
 */
#define ARRAYSIZE 30

/*
 * Setup Tree Node Structure
 */
typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} treenode;

typedef int (*comparer)(int,int);
typedef void (*callback)(treenode*);

/*
 * Function Prototypes
 */
int compare(int left, int right);
int findLargest(treenode *root);
int findSmallest(treenode *root);
treenode *create_node(int data);
treenode *delete_node(treenode *root, int data, comparer compare);
treenode *insert_node(treenode *root, comparer compare, int data);
treenode *search (treenode *root, const int data, comparer compare);
void display(treenode *nd);
void display_tree(treenode *nd);
void dispose(treenode *root);
void traverse(treenode *root, callback cb);

/*
 * Main Function
 */
int main(void) {
	treenode *root = NULL;
	comparer int_comp = compare;
	callback f = display;

	int a[ARRAYSIZE];
	int i=0;

	printf("--- C BST ---\n\n");
	printf("Insert: \n");
	
	srand(time(0));
	for(i=0;i<ARRAYSIZE;i++) {
		a[i] = rand() % 60000;
		root = insert_node(root, int_comp, a[i]);
	}

	display_tree(root);
	
	treenode *s = search(root,10,int_comp);
	if ( s != NULL ) {
		printf("Found It: %d ", s->data);
		if ( s->left != NULL ) {
			printf("(L: %d)", s->left->data);
		}

		if ( s->right != NULL ) {
			printf("(R: %d)", s->right->data);
		}
		printf("\n");
	} else {
		printf("Node %d Not Found", 10);
	}
	printf("\n");

	printf("Largest Node Value Is: %d\n", findLargest(root));
	printf("Smallest Node Value Is: %d\n", findSmallest(root));

	dispose(root);

	return 0;
}

/*
 * Subfunctions
 */

/*
 * Function Name: findLargest
 * Description:
 * 	Find the largest element in a tree.
 * Input(s):
 * 	root - pointer to treenode.
 * Return(s):
 * 	largest - largest int in tree.
 */
int findLargest(treenode *root) {
	int largest;

	if ( root == NULL ) 
		return INT_MIN;

	int leftVal = findLargest(root->left);
	int rightVal = findLargest(root->right);

	if ( root->data > leftVal && root->data > rightVal )
		largest = root->data;
	else {
		if ( leftVal >= rightVal )
			largest = leftVal;
		if ( leftVal < rightVal )
			largest = rightVal;
	}

	return largest;
}


/*
 * Function Name: findSmallest
 * Description:
 * 	Function to find the smallest element in 
 * 	a tree.
 * Input(s):
 * 	root - treenode pointer.
 * Return(s):
 * 	smallest - smallest element in the tree.
 */
int findSmallest(treenode *root) {
	int smallest;

	if ( root == NULL ) 
		return INT_MAX;

	int leftVal = findSmallest(root->left);
	int rightVal = findSmallest(root->right);

	if ( root->data < leftVal && root->data < rightVal )
		smallest = root->data;
	else {
		if ( leftVal <= rightVal )
			smallest = leftVal;
		if ( leftVal > rightVal )
			smallest = rightVal;
	}

	return smallest;
}

/*
 * Function Name: create_node
 * Description:
 * 	Function to create a new node.
 * Input(s):
 * 	data - integer data for new node.
 * Return(s):
 * 	new_node - treenode pointer to new node.
 */
treenode *create_node(int data) {
	treenode *new_node = (treenode*) malloc (sizeof(treenode));
	if ( new_node == NULL ) {
		printf("Out Of Memory. Cannot Create New Node!\n");
		exit(1);
	}

	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

/*
 * Function Name: insert_node
 * Description:
 * 	Function to insert a node into a tree.
 * Input(s):
 * 	root - treenode pointer.
 * 	compare - comparer.
 * 	data - int data for new node.
 * Return(s):
 * 	root - treenode pointer
 */
treenode *insert_node(treenode *root, comparer compare, int data) {
	if ( root == NULL) {
		root = create_node(data);
	} else {
		int is_left = 0;
		int r = 0;
		treenode *cursor = root;
		treenode *prev = NULL;

		while (cursor != NULL) {
			r = compare(data, cursor->data);
			prev = cursor;

			if (r < 0) {
				is_left = 1;
				cursor = cursor->left;
			} else {
				is_left = 0;
				cursor = cursor->right;
			}
		}

		if ( is_left ) 
			prev->left = create_node(data);
		else
			prev->right = create_node(data);
	}
	return root;
}

/*
 * Function Name: delete_node
 * Description:
 * 	Function to delete a treenode.
 * Input(s):
 * 	root - treenode pointer.
 * 	data - data of the treenode to delete.
 * 	compare - comparer to search for the correct node.
 * Return(s):
 * 	cursor - treenode pointer.
 */
treenode *delete_node(treenode *root, int data, comparer compare) {
	if (root == NULL)
		return NULL;

	treenode *cursor;
	int r = compare(data, root->data);

	if ( r < 0 ) {
		root->left = delete_node(root->left,data,compare);
	} else if ( r > 0 ) {
		root->right = delete_node(root->right,data,compare);
	} else {
		if ( root->left == NULL ) {
			cursor = root->left;
			free(root);
			root = cursor;
		} else {
			cursor = root->right;
			treenode *parent = NULL;

			while ( cursor->left != NULL ) {
				parent = cursor;
				cursor = cursor->left;
			}
			root->data = cursor->data;
			if ( parent != NULL ) {
				parent->left = delete_node(parent->left, parent->left->data, compare);
			} else {
				root->right = delete_node(root->right, root->right->data, compare);
			}
		}
	}		
	return root;
	
}

/*
 * Function Name: search
 * Description:
 * 	Function to search a binary tree given
 * 	a root node, data to search for, and 
 * 	comparer.
 * Input(s):
 * 	root - treenode pointer
 * 	data - constant int to search for.
 * 	compare - comparer (used to search)
 * Return(s):
 * 	cursor - treenode pointer where the data is.
 */
treenode *search (treenode *root, const int data, comparer compare) {
	if ( root == NULL) {
		return NULL;
	}

	int r;
	treenode *cursor = root;

	while ( cursor != NULL ) {
		r = compare(data, cursor->data);
		if (r < 0) {
			cursor = cursor->left;
		} else if ( r > 0 ) {
			cursor = cursor->right;
		} else {
			return cursor;
		}
	}

	return cursor;
}

/*
 * Function Name: traverse
 * Description:
 * 	Function to traverse a binary tree given 
 * 	a root node and callback function.
 * Input(s):
 * 	root - treenode pointer.
 * 	cb - callback function.
 * Return(s):
 * 	None
 */
void traverse(treenode *root, callback cb) {
	treenode *cursor, *pre;

	if(root == NULL) {
		return;
	}

	cursor = root;

	while ( cursor != NULL ) {
		if ( cursor->left != NULL ) {
			cb(cursor);
			cursor = cursor->right;
		} else {
			pre = cursor->left;

			while (pre->right != NULL && pre->right != cursor) {
				pre = pre->right;
			}

			if ( pre->right != NULL ) {
				pre->right = cursor;
				cursor = cursor->left;
			} else {
				pre->right = NULL;
				cb(cursor);
				cursor = cursor->right;
			}
		}
	}
}

/*
 * Function Name: dispose
 * Description:
 * 	function to delete a tree with a given
 * 	root node.
 * Input(s):
 * 	root - treenode pointer
 * Return(s):
 * 	None
 */
void dispose(treenode *root) {
	if ( root != NULL ) {
		dispose(root->left);
		dispose(root->right);
		free(root);
	}
}

/*
 * Function Name: compare
 * Description:
 * 	Compare two integers and return either
 * 	-1,0, or 1 depending on the comparision
 * 	results.
 * Input(s):
 * 	left - int one
 * 	right - int two
 * Return(s):
 * 	-1,0,1 - result of compare
 */
int compare(int left, int right) {
	if ( left > right ) {
		return 1;
	}

	if ( left < right ) {
		return -1;
	}

	return 0;
}

/*
 * Function Name: display
 * Description:
 * 	Display a node's data
 * Input(s):
 * 	nd - treenode pointer.
 * Return(s):
 * 	None
 */
void display(treenode *nd) {
	if ( nd != NULL) {
		printf("%d\n", nd->data);
	}
}

/*
 * Function Name: display_tree
 * Description:
 * 	Function to display all the nodes in a tree,
 * 	and their left and right nodes.
 * Input(s):
 * 	nd - treenode pointer to base node.
 * Return(s):
 * 	None
 */
void display_tree(treenode *nd) {
	if (nd == NULL) {
		return;
	}

	printf("%d ", nd->data);
	if (nd->left != NULL)
		printf("(L: %d) ", nd->left->data);
	if (nd->right != NULL)
		printf("(R: %d) ", nd->right->data);
	printf("\n");

	display_tree(nd->left);
	display_tree(nd->right);
}
