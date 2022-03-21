#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"


int FindMinPath(struct AVLTree *tree, TYPE *path);
void printBreadthFirstTree(struct AVLTree *tree);
void preorder_traversal(struct AVLnode *node, TYPE *min_cost, TYPE *path, int *a, TYPE *potential_path, int *b, TYPE diff, TYPE par_val);

/* -----------------------
The main function
  param: argv = pointer to the name (and path) of a file that the program reads for adding elements to the AVL tree
*/
int main(int argc, char** argv) {

	FILE *file;
	int len, i;
	TYPE num; /* value to add to the tree from a file */
	struct timeval stop, front; /* variables for measuring execution time */
	int pathArray[50];  /* static array with values of nodes along the min-cost path of the AVL tree -- as can be seen, the tree cannot have the depth greater than 50 which is fairly sufficient for out purposes*/

	struct AVLTree *tree;
	
	tree = newAVLTree(); /*initialize and return an empty tree */
	
	file = fopen(argv[1], "r"); 	/* filename is passed in argv[1] */
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){
		addAVLTree(tree, num);		
	}
	/* Close the file  */
	fclose(file);
	
	printf("\nPrinting the tree breadth-first : \n");
	printBreadthFirstTree(tree);
	
	gettimeofday(&front, NULL);

	/* Find the minimum-cost path in the AVL tree*/
	len = FindMinPath(tree, pathArray);
	
	gettimeofday(&stop, NULL);

	/* Print out all numbers on the minimum-cost path */
	printf("\nThe minimum-cost path is: \n");
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	printf("\nYour execution time to find the mincost path is %f microseconds\n", (double) (stop.tv_usec - front.tv_usec));

        /* Free memory allocated to the tree */
	deleteAVLTree(tree); 
	
	return 0;
}
/*
traverses the tree in preorder fashion and keeps track of paths
that could be the min cost. If one is found that is lower, it is traded
*/
void traversal(struct AVLnode *node, TYPE *min_cost, TYPE *path, int *length_of_path, TYPE *potential_path, int *length_of_potential_path, TYPE diff, TYPE par_val) {
	int i;

	potential_path[*length_of_potential_path] = node->val; /* start path */ 
	(*length_of_potential_path)++; /* bookkeep the length */

	diff = diff + abs(par_val - node->val);
	/* exchange paths */
	if (diff >= *min_cost) {
		(*length_of_potential_path)--;
		return;
	}
	/* end of route has been found, check the length */
	if (node->left == NULL && node->right == NULL) {
		if (diff < *min_cost) {
			*min_cost = diff;
			for (i = 0; i < *length_of_potential_path; i++) {
				path[i] = potential_path[i];
			}
			*length_of_path = *length_of_potential_path;
			(*length_of_potential_path)--;
		}
	}
	/* the end has not been found, keep recursively traversing the tree */
	else {
		if (node->left != NULL) {
			traversal(node->left, min_cost, path, length_of_path, potential_path, length_of_potential_path, diff, node->val);
		}
		if (node->right != NULL) {
			traversal(node->right, min_cost, path, length_of_path, potential_path, length_of_potential_path, diff, node->val);
		}
		(*length_of_potential_path)--;
	}

}


/* --------------------
Finds the minimum-cost path in an AVL tree
   Input arguments: 
        tree = pointer to the tree,
        path = pointer to array that stores values of nodes along the min-cost path, 
   Output: return the min-cost path length 

   pre: assume that
       path is already allocated sufficient memory space 
       tree exists and is not NULL
*/
int FindMinPath(struct AVLTree *tree, TYPE *path)
{
	int length_of_path = 0;
	struct AVLnode* curr = tree->root;			/* allows us to traverse the tree */
	TYPE min_cost = (TYPE) 10^6 * tree->cnt;	/* sets a maximum */
	int potential_path_length = 0;				/* creates a potential path and sets the length to 0 */
	TYPE potential_path[200];

	path[length_of_path] = tree->root->val;
	length_of_path++;
	/* if the tree has more than one node (a path), then find the minimum path length */
	if (tree->cnt > 1) {
		traversal(curr, &min_cost, path, &length_of_path, potential_path, &potential_path_length, 0, curr->val);
	}
	else if (tree->cnt == 0) {
		/* case where the tree has no nodes */
		printf("\nThere are no nodes to count\n");
	}
	return length_of_path;
}

/* -----------------------
Printing the contents of an AVL tree in breadth-first fashion
  param: pointer to a tree
  pre: assume that tree was initialized well before calling this function
*/
void printBreadthFirstTree(struct AVLTree *tree)
{
	struct AVLnode **ordered_array = (struct AVLnode**) malloc((tree->cnt)*sizeof(struct AVLnode));
	struct AVLnode *curr = tree->root;
	int front = 0;
	int back = 0;
	int i = 0;

	ordered_array[back] = curr;		/* start the array to print */
	back++;
	/* do while there are still children to add to the array */
	while (front < back) {
		curr = ordered_array[front];
		front++;
		/* if there is a left child, add it */
		if (curr->left != NULL) {
			ordered_array[back] = curr->left;
			back++;
		}
		/* if theres a right child, add it */
		if (curr->right != NULL) {
			ordered_array[back] = curr->right;
			back++;
		}
	}
	/* print the whole array */
	for (;i < back; i++) {
		printf("%d ", ordered_array[i]->val);
	}
	/* free memory allocated */
	free(ordered_array);
}




