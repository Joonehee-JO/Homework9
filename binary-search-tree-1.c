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

	printf("[----- [Cho Joon Hee] [2017038076] -----]\n");   

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
			initializeBST(&head);	//트리 초기화
			break;
		case 'q': case 'Q':
			freeBST(head);			//종료 전 메모리 반납
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);		//key값을 갖는 노드 트리에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);	//key값을 갖는 리프노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);	//반복탐색을 통하여 key값을 갖는 노드 탐색
			if(ptr != NULL)			//해당 노드가 존재한다면
				printf("\n node [%d] found at %p\n", ptr->key, ptr);	//해당노드 값과 주소 출력
			else					//존재하지 않는다면
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);	//재귀탐색으로 key값을 갖는 노드 탐색
			if(ptr != NULL)			//해당 노드가 존재한다면
				printf("\n node [%d] found at %p\n", ptr->key, ptr);	//해당노드 값과 주소 출력
			else					//존재하지 않는다면
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);	//중위순회를 통하여 트리 출력
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);	//전위순회를 통하여 트리 출력
			break;
		case 't': case 'T':
			postorderTraversal(head->left);	//후위순회를 통하여 트리 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {		//트리를 초기화하는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)	//메모리를 할당받았다면 freeBST함수 호출
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));	//헤드노드생성
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr)	//중위 순회를 통하여 트리의 노드를 출력하는 함수
{
	if(ptr) {	//ptr이 존재한다면
		inorderTraversal(ptr->left);	//먼저 ptr이 가리키는 노드의 왼쪽을 인자로 넘겨줌(왼쪽 끝까지 내려감)
		printf(" [%d] ", ptr->key);		//해당 노드의 key값 출력
		inorderTraversal(ptr->right);	//그 뒤 오른쪽 노드로 이동
	}
}

void preorderTraversal(Node* ptr)	//전위 순회를 통하여 트리의 노드를 출력하는 함수(먼저 도착한 노드의 값을 출력 후 순회)
{
	
	if(ptr){	//ptr이 존재한다면
		printf(" [%d] ", ptr->key);		//해당 노드의 key값 출력
		preorderTraversal(ptr->left);	//왼쪽 자식 노드로 이동
		preorderTraversal(ptr->right);	//왼쪽노드들을 전부 순회한 뒤 오른쪽 노드로 이동
	}
}

void postorderTraversal(Node* ptr)	//후위순회를 통하여 트리의 노드를 출력하는 함수(노드의 끝까지 내려간뒤 아래에서부터 출력)
{
	if(ptr){                            //ptr이 존재한다면
        postorderTraversal(ptr->left);  //먼저 ptr이 가리키는 노드의 왼쪽을 인자로 넘겨줌(왼쪽 끝까지 내려감)
        postorderTraversal(ptr->right); //그 뒤 오른쪽 자식 노드로 이동
        printf("[ %d ]  ", ptr->key);   //해당 노드의 key값 출력
    }
}


int insert(Node* head, int key)	//입력받은 값을 갖는 노드를 삽입하는 함수
{
	if(head == NULL){	//메모리를 할당받지 못했을 경우
		printf("the memory is not allocated\n");
		return 1;
	}

	Node* temp = (Node*)malloc(sizeof(Node));	//삽입할 노드와 필드값
	temp->key = key, temp->left = NULL, temp->right = NULL;

	if(head->left == NULL){	//아직 트리에 노드가 존재하지 않는다면
		head->left = temp;	//헤드노드의 left가 temp를 가리키도록한다
		return 1;
	}

	Node* node = head->left;	//노드가 존재할경우 비교할 노드를 가리킬 포인터 node에 헤더노드의 left를 할당
	Node* parent;				//부모노드를 가리킬 포인터

	while(node != NULL){		//node가 가리키는 노드가 존재한다면
		if(node->key == key){	//입력한 값이 이미 존재한다면
			printf("Duplicated key is exist\n");	//에러메세지출력 후 종료
			return 1;
		}
		else{					//입력한 값이 존재하지않는다면
			parent = node;		//parent가 node가 가리키는 노드를 가리키도록하고
			if(node->key > key){	//값을 비교하여 입력한 값이 작을 경우
				node = node->left;	//왼쪽으로 이동
			}		
			else{				//입력한 값이 노드의 값보다 클 경우
				node = node->right;	//오른쪽으로 이동
			}
		}
	}

	//반복문을 빠져나와 노드를 삽입하는 과정, node는 NULL값을 가짐
	if(key > parent->key)		//입력된 값이 부모노드의 key보다 클 경우
		parent->right = temp;	//부모노드의 오른쪽 자식노드에 삽입
	else
		parent->left = temp;	//부모노드의 왼쪽 자식노드에 삽입
	
	return 1;
}

int deleteLeafNode(Node* head, int key)	//key값을 갖는 리프노드를 삭제하는 함수
{
	if (head == NULL) {	//헤더노드가 메모리를 할당받지 못했을 경우
		printf("the momory is not allocated\n");
		return 1;
	}

	if (head->left == NULL) {	//트리에 노드가 존재하지 않을 경우
		printf("the tree is empty\n");
		return 1;
	}

	Node* node = head->left;	//진행할 노드를 가리킬 포인터
	Node* parent = head;		//부모노드를 가리킬 포인터

	while(node != NULL){		//노드가 존재할경우 반복
		if(node->key == key){	//입력한 key값을 갖는 노드를 찾았을 경우
			if(node->left == NULL && node->right == NULL) {	//해당 노드가 자식노드를 갖지않는 리프노드일 경우
				if(parent == head){	//해당 노드가 첫노드인 루트노드일 경우
					head->left = NULL;	//헤더노드의 left를 NULL로 초기화(루트노드를 삭제하기위함)
					free(node);
					return 1;
				}		
				if(parent->left == node)	//해당노드가 부모노드의 왼쪽에 있을 경우
					parent->left = NULL;	//NULL로 초기화
				else if(parent->right == node)	//해당노드가 부모노드의 오른쪽에 있을 경우
					parent->right = NULL;	//해당노드를 가리키는 포인터 NULL로 초기화

				free(node);		//마지막으로 해당 노드 삭제
			}
			else 	//해당 노드가 리프노드가 아닐경우
				printf("That node is not a leaf node\n");

			return 1;
		}

		parent = node;		//parent가 node를 가리키도록함, node는 자식노드를 가리키도록함

		if(node->key < key)	//입력key값이 현재 노드의 key보다 클 경우
			node = node->right;	//오른쪽 자식노드로 이동
		else				//입력key값이 현재 노드의 key보다 작을 경우
			node = node->left;	//왼쪽 자식노드로 이동
	}

	printf("the node with that key does not exist in the tree\n");	//key값을 갖는 노드를 찾지 못했을 경우

	return 1;
}

Node* searchRecursive(Node* ptr, int key)	//재귀방식으로 해당노드의 위치를 찾는 함수
{
	if(ptr == NULL  || (ptr->key == key))	//ptr이 NULL이거나 ptr이 가리키는 노드의 값이 key와 같을 경우
		return ptr;							//ptr반환

	if(ptr->key < key)						//ptr의 key가 입력한값보다 작을 경우
		ptr = searchRecursive(ptr->right, key);	//오른쪽 자식노드로 이동하여 탐색
	else if(ptr->key > key)					//ptr의 key가 입력한값보다 클 경우
		ptr = searchRecursive(ptr->left, key);	//왼쪽 자식노드로 이동하여 탐색
}

Node* searchIterative(Node* head, int key)	//반복탐색으로 해당노드의 위치를 찾는 함수
{
	Node* ptr = head->left;		//현재 노드를 가리킬 포인터

	while(ptr != NULL){
		if(ptr->key == key)		//해당 노드의 key가 입력값과 같다면
			return ptr;			//ptr반환
		else if(ptr->key < key) //ptr의 key값이 입력값보다 작다면
			ptr = ptr->right;	//오른쪽 자식 노드로 이동
		else if(ptr->key > key)	//ptr의 key값이 입력값보다 크다면
			ptr = ptr->left;	//왼쪽 자식 노드로 이동
	}

	return NULL;	//해당값을 갖는 노드를 찾지 못하였을 경우 NULL값 리턴
}


int freeBST(Node* head)		//이진트리를 구성하기위해 사용한 메모리를 반납하는 함수
{
	if(head->left == head)	//자식노드들이 없다면
	{
		free(head);			//헤드노드 메모리 반납 후 함수종료
		return 1;
	}

	freeNode(head->left);	//freeNode함수 호출하여 트리의 노드들 메모리 해제
	free(head);				//마지막으로 헤드노드 메모리 해제

	return 1;
}

void freeNode(Node* ptr){	//트리의 노드들을 재귀적으로 접근하여 해제하는 함수
	if(ptr){		//ptr이 NULL이 아니라면
		freeNode(ptr->left);	//ptr이 가리키는 노드의 왼쪽 자식 노드로 이동
		freeNode(ptr->right);	//ptr이 가리키는 노드의 오른쪽 자식노드로 이동
		free(ptr);				//마지막으로 ptr이 가리키는 노드 메모리 반납
	}
}