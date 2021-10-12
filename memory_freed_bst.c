#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//defining attributes of a node structure
typedef struct _Node
{
	int data;
	struct _Node *left;
	struct _Node *right;

} Node;



// this is recursively done
Node *insertNode(Node *root, int value)
{
	Node *currentNode;
	
	if (root == NULL)
	{
		// allocating new memory for the new node
		Node *new  = (Node *)malloc(sizeof(struct _Node));

		if (new == NULL)
		{
			printf("failed\n");
			return NULL;
		}
		//assigning data
		new->data = value;
		new->left = NULL;
		new->right = NULL;
		root = new;

		//	printf("inserted \n");
		return root;
	}

	//if value is greater 
	if (root->data < value)
	{
		//	printf("right \n");

		//go to right subtree and change the right subtree after inserting 
		root->right = insertNode(root->right, value);
		return root;
	}
	else if (root->data > value)
	{
		//printf("left \n");
		 // go to left subtree and change the left subtree
		root->left = insertNode(root->left, value);
		return root; // have to return the root otherwise it will not print the whole tree

	}
	else if (root->data == value) //if found a dubplicate return null
	{
		return NULL;
	}
	return root;
}


/*
Node *insertNode(Node *root, int value){
	
	Node ** z = &root; //referencing the root so that I am able to insert the node
	while (*z!=NULL){
		//printf("root is not null");
		if (value > (*z)->data){
			//printf("going right");
			z = &(*z)->right;
		}else if (value < (*z)->data){
			z= &(*z)->left;
		}else{
			return NULL;
		}
	}

	Node * new = (Node *) malloc(sizeof(struct _Node));
	new->data= value;
	new->left= NULL;
	new->right = NULL;
    *z= new;

	return new;
}
*/
//recursive approach
/*
Node *deleteNode(Node *root, int value)
{
	//base case if there is no node that has the value 
	if (root == NULL)
	{
		//printf("base null detected");
		return NULL;
	}

	//if value is greater than root then search for its right subtree to delete the node
	if (value > root->data)
	{
		//printf("going right");
		// if we dont assign the node to root->right my function will remove all the nodes
		//change the right subtree after deleting it and return the node 
		root->right = deleteNode(root->right, value);
		return root;
	}
	else if (value < root->data)
	{
		//printf("going left");
		//change the left subtree and return it ;
		root->left = deleteNode(root->left, value);
		return root;
	}
	else //if we find the node that we want to delete
	{
		// and has left subtree as null then simply make right subtree as its root
		if (root->left == NULL)
		{

			
			Node *temp = root->right;
			free(root);
			
			root = temp;
			return root;
		}
		//and has right subtree as null then make left subtree as its root
		else if (root->right == NULL)
		{
			Node *temp = root->left;
			free(root);
		
			root = temp;
			return root;
		}
		//has both subtrees as null then make root as null
		else if (root->right == NULL && root->left == NULL){
			free(root);
			root = NULL;
			return root;
		}
	
			//if none of above then find the rightmost leaf of left subtree and take its data as root data
			//then proceed to delete that leaf

			Node *temp = root->left;

			while (temp->right != NULL)
			{

				temp = temp->right;
			}
			root->data = temp->data;
			deleteNode(root, temp->data);
			
		
		
	}
}
*/





Node *deleteNode(Node *root, int value){
	Node **z = &root;
	Node **c;
	Node **r;
	Node ** newroot = &root;

	Node *rightsub;
	Node * temp;
	Node *temp2;
	int copy =0;

	while (*z!=NULL){
		//printf("root is not null");
		if (value > (*z)->data){
			//printf("going right");
			z = &(*z)->right;
		}else if (value < (*z)->data){
			z= &(*z)->left;
		}else if (value == (*z)->data){

			if ((*z)->left ==NULL && (*z)->right != NULL){
				temp= (*z)->right;
				free((*z));
				(*z) = temp;

			}
			else if ((*z)->left !=NULL && (*z)->right == NULL){
				temp= (*z)->left;
				free((*z));
				(*z) = temp;

			}
			else if ((*z)->left ==NULL && (*z)->right == NULL){
				(*z) = NULL;
			}
			else{
				//printf("doing all \n");
				c = &(*z);
				r = &(*z)->left;
				rightsub = (*z)->right; //referencing right subtree;

				
				
				
				z= &(*z)->left; // going through left subtree

				while((*z)->right != NULL){
					z = &(*z)->right; //take the rightmost value
				}
				temp = (*z);
				copy= temp->data; // copy the data . Note that I tried to copy the whole node but somehow it gives me the value of address instead of node and it gives the wrong subtree  
				//printf("data %d", temp->data);
				
				free((*z));
				(*z) = NULL;
				
				//printf("data %d", temp->data);
				
				temp2 = (*r);
				free((*c));
				
				(*c)->data= copy;
				(*c)->left =temp2;
				
				(*c)->right = rightsub;
				//printSubtree((*c));
				//printf("%d", (*c)->data);
				return root;

			}

			
		}
	}
	return root;

}




//this function frees the whole tree
void freeTree(Node * root){
	if (root==NULL){
		return;
	}
	freeTree(root->left);
	freeTree(root->right);
	free(root);

}

Node * deleteSubtree(Node* root, int value){
	if (root == NULL){
		return root;
	}

	//if value is greater 
	if (value > root->data){

		//go to right subtree and change right subtree after deletion
		root->right = deleteSubtree(root->right,value);
		return root;

	}
	else if (value < root->data){
		//go to left subtree and change left subtree after deletion
		root->left = deleteSubtree(root->left,value);
		return root; // must return root otherwise the tree would not be complete
	}
	else{

		//freeing root then assigning null to it since freed memory is deallocated which would be dangerous if we tried to access it again
		freeTree(root);
		root = NULL;
		
		return root;
	}

}


//this is recursive way of implementing depth which is a lot more than iterative way
/* 
int depth(Node * root, Node *N){
	int sum = 0;

	//base case node is not found
	if (root == NULL)
	{
		return -1;
	}

	//printf("%d %d", root->data, N->data);

	//printf("%d",N->data);
	//if found the node the return 0
	if (N->data == root->data)
	{
		//printf("found");
		
		return 0;
	}

	

	// if nodes data is greater then go to its right subtree 
	if (N->data > root->data)
	{
		
		//printf("going right");
		
		//if the node is not found the keep return -1
		if (depth(root->right,N) == -1){
			return -1;
		}
		//else add 1 to the sum to keep the depth
		else{
			sum = sum + 1 + depth(root->right, N);
		}
		
	}
	else if (N->data < root->data)
	{

		//printf("going left");
		if (depth(root->left,N) == -1){
			
			return -1;
		}else{
			sum = sum  +  1 +depth(root->left , N);
		}
		
	}
	else
	{
		return sum;
	}

	return sum;
}
*/

//iterative way of defining depth
int depth(Node * root ,Node *N){
	if (root->data == N->data){
		return 0;
	}
	int sum = 0;

	Node ** z = &root; //referencing the root so that I am able to insert the node
	while (*z!=NULL){
		//printf("root is not null");
		if (N->data > (*z)->data){
			//printf("going right");
			z = &(*z)->right;
			sum = sum +1;
		}else if (N->data < (*z)->data){
			z= &(*z)->left;
			sum = sum+1;
		}else if (N->data == (*z)->data){
			if (N == (*z)){
				return sum;
			}
		}
	}
	return -1;	
}


// in this case using recursion is more appropriate
void printSubtree(Node *N)
{
	//if no node is found then return
	if (N == NULL)
	{
		return;
	}
	printSubtree(N->left);
	printf("%d \n", N->data);
	printSubtree(N->right);
}


int countLeaves(Node *N)
{
	int sum = 0;


	//base case no node is found the return 0
	if (N == NULL)
	{
		return 0;
	}
	//if leaf is found return 1
	if (N->left == NULL && N->right == NULL)
	{
		return 1;
	}
	// if left subtree is null but rightsubtree still has nodes then count right subtrees leaves
	else if (N->left == NULL && N->right != NULL)
	{
		//add the count of leaves on right subtree to the sum
		sum = sum + countLeaves(N->right);
	}
	else if (N->left != NULL && N->right == NULL)
	{
		//add the count on left subtree to the sum
		sum = sum + countLeaves(N->left);
	}
	else
	{
		//add the count of both subtrees to the sum
		sum = sum + countLeaves(N->left) + countLeaves(N->right);
	}
	//it is very important to return the sum
	return sum;
}


