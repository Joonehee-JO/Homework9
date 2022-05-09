/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
void freeNode(Node* ptr);
/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {	
		inorderTraversal(ptr->left);	
		printf(" [%d] ", ptr->key);		
		inorderTraversal(ptr->right);	
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr){	
		printf(" [%d] ", ptr->key);		
		preorderTraversal(ptr->left);	
		preorderTraversal(ptr->right);	
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr){                           
        postorderTraversal(ptr->left);  
        postorderTraversal(ptr->right); 
        printf("[ %d ]  ", ptr->key);   
    }
}

int insert(Node* head, int key)	
{
	if(head == NULL){	
		printf("the memory is not allocated\n");
		return 1;
	}

	Node* temp = (Node*)malloc(sizeof(Node));	
	temp->key = key, temp->left = NULL, temp->right = NULL;

	if(head->left == NULL){	
		head->left = temp;
		return 1;
	}

	Node* node = head->left;	
	Node* parent;				

	while(node != NULL){		
		if(node->key == key){	
			printf("Duplicated key is exist\n");	
			return 1;
		}
		else{					
			parent = node;		
			if(node->key > key){	
				node = node->left;	
			}		
			else{				
				node = node->right;	
			}
		}
	}

	if(key > parent->key)		
		parent->right = temp;	
	else
		parent->left = temp;	
	
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {	
		printf("the momory is not allocated\n");
		return 1;
	}

	if (head->left == NULL) {	
		printf("the tree is empty\n");
		return 1;
	}

	Node* node = head->left;	
	Node* parent = head;		

	while(node != NULL){	
		if(node->key == key){	
			if(node->left == NULL && node->right == NULL) {	
				if(parent == head){
					head->left = NULL;	
					free(node);
					return 1;
				}		
				if(parent->left == node)	
					parent->left = NULL;
				else if(parent->right == node)	
					parent->right = NULL;	

				free(node);		
			}
			else 	
				printf("That node is not a leaf node\n");

			return 1;
		}

		parent = node;		

		if(node->key < key)
			node = node->right;
		else				
			node = node->left;	
	}

	printf("the node with that key does not exist in the tree\n");	

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{

}

Node* searchIterative(Node* head, int key)
{

}


int freeBST(Node* head)
{
	if(head->left == head)	
	{
		free(head);			
		return 1;
	}

	freeNode(head->left);	
	free(head);				

	return 1;
}

void freeNode(Node* ptr){	
	if(ptr){		
		freeNode(ptr->left);	
		freeNode(ptr->right);	
		free(ptr);				
	}
}

