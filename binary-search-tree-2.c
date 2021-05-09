/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {	//node 구조체 생성 
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h); /* 이진탐색트리 초기화 */

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

//void printStack();	//Q. 이 함수를 정의해야 하나?

int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("[----- [jinyounglee] [2020039063] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
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
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;

		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		// case 'p': case 'P':
		// 	printStack();
		// 	break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


/* Binary Search Tree Initialize */
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}


/* Inorder Traversal -> recursive */
void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}


/* node insert in Binary Tree*/
int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));	//삽입할 노드 동적할당 
	//삽입할 노드 초기화
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	//tree가 존재하지 않을 때
	if (head->left == NULL) { 
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


/* 노드 삭제 함수 -> 3가지 방식 */
int deleteNode(Node* head, int key)
{
	Node* parent=head;  //삭제할 노드의 부모노드 
	Node* deleted=head->left;	//삭제할 노드 


	Node* ptr=NULL;
	Node* ptr_parent=NULL;
	Node* small=NULL;
	Node* small_parent=NULL;


	//Q. 삭제할 노드를 어떻게 찾을 건가?
	while(deleted!=NULL)
	{
		//해당 key를 가진 노드를 찾을 때 
		if(key==deleted->key)
		{
			/* leaf node delete*/
			if(deleted->left==NULL&&deleted->right==NULL)
			{
				/* head->left가 leaf node일 때*/
				if(head->left==deleted)
				{
					parent->left=NULL;
					free(deleted);
					return 0;
				}
				/* 그 이외의 노드가 leaf node일 때*/
				if(key<parent->key)	
					parent->left==NULL;
				else if(key>parent->key)
					parent->right==NULL;
				free(deleted);
				return 0;
			}
	
	 		
			//여기 더 생각하기!! case가 너무 많음 
			/* non-leaf node which has two childs delete 
			-> 오른쪽 서브트리에서 가장 작은 값으로 대체되도록 한다. */
			else if(deleted->left!=NULL&&deleted->right!=NULL)
			{
				//ptr 관련 포인터는 작은원소를 찾으러 다님
				ptr_parent=deleted;
				ptr=deleted->right;  //right subtree

				//small 관련 포인터는 작은 원소를 가리킴. 
				small_parent=ptr_parent;
				small=ptr; //right subtree


				while(ptr!=NULL)
				{
					if((ptr->key)<(small->key))
					{
						small_parent=ptr_parent;
						small=ptr;
					}
					ptr_parent=ptr;
					ptr=ptr->left;		//left subtree로 이동(이유: 가장 작은 원소를 찾아야 하므로)
				}
				//small 노드형포인터가 가장 작은 값을 가진 노드 가리킴

				//head->left가 제거대상일 때
				if(head->left==deleted)
				{
					small->right=deleted->right;
					small_parent->left=NULL;
					head->left=small;
					free(deleted);
					return 0;
				}

				//그 이외의 node가 제거대상일 때
				
				if(key<parent->key)
				{
					small->right=deleted->right;
					parent->left=small;
				}
				else if(key>parent->key)
				{
					small->right=deleted->right;
					parent->right=small;
				}
				small_parent->left=NULL;
				free(deleted);
				return 0;
			}

		
			/* non-leaf node which has one child delete */
			else
			{
				/* head->left가 one child를 갖는 노드일 때*/
				if(head->left==deleted)
				{
					if(deleted->left!=NULL)
						parent->left=deleted->left;
					else if(deleted->right!=NULL)
						parent->left=deleted->right;
					free(deleted);
					return 0;
				}

				//deleted의 subtree는 left or right 중 어디에 위치하는지 알아야 함
				if(key<parent->key)
				{
					if(deleted->left!=NULL)
						parent->left=deleted->left;
				
					else if(deleted->right!=NULL)
						parent->left=deleted->right;
				}	
				else if(key>parent->key)
				{
					if(deleted->left!=NULL)
						parent->right=deleted->left;
				
					else if(deleted->right!=NULL)
						parent->right=deleted->right;
				}
				free(deleted);
				return 0;
			}
		}
		//해당 key를 가진 노드를 찾지 못할 때
		parent=deleted;
		if(key<deleted->key)
			deleted=deleted->left;  //left subtree로 이동
		else if(key>deleted->key)
			deleted=deleted->right;	//right subtree로 이동
	}

	//deleted==NULL일때(=주어진 key값과 동일한 데이터를 갖는 노드가 존재하지 않는 경우)
	printf("No node for key [%d]\n",key);
	return -1;
}


/* postorder traversal에서 파생된 함수 -> recursive방식 이용 */
void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);	//ptr에 할당된 메모리 해제 
	}
}


/* BST에 할당된 메모리 전체 해제 */
int freeBST(Node* head)
{
	//tree가 존재하지 않을 때 -> head만 메모리 해제시키면 됨
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	//tree가 존재할 때 -> tree안의 모든 노드들을 메모리 해제시켜야 함
	Node* p = head->left;

	freeNode(p);

	//tree안의 모든 노드들이 메모리 해제된 후, head에 할당된 메모리 해제
	free(head);
	return 1;
}


/* 스택에서 원소 삭제하는 함수 */
Node* pop()
{
	/* stack이 Empty인지 검사 */
	if(top==-1)					//top=-1일때 스택이 비어있는상태로, 삭제할 원소가 존재하지 않음
		return NULL; 			//NULL리턴
	else
		return stack[top--];	//top에 위치한 원소를 반환하고, top의 위치를 -1한다
}


/* 스택에 원소 삽입하는 함수 */
void push(Node* aNode)
{
	if(top<MAX_STACK_SIZE-1)	//top>=MAX_STACK_SIZE-1이면, stack이 가득찬 상태로 원소를 삽입할 수 없음
		stack[++top]=aNode;		//top을 1증가시킨 위치에 원소를 삽입한다
}

/**
 * textbook: p 224s
 */
/* 비순환 중위순회방식 -> stack 이용*/
void iterativeInorder(Node* node)   //LVR 방식 
{
	while(1)
	{
		for(;node;node=node->left)	//node가 NULL이기 전까지, node의 left로 이동하며, 스택에 node삽입
		{
			push(node);	//스택에 삽입
		}
		node=pop();		//스택에서 삭제 
		if(!node)  		//공백스택 (pop()==NULL일 때) -> 반복문 탈출
			break;
		printf(" [%d] ",node->key);	
		node=node->right;	//right subtree로 이동
	}
}


/* front위치를 dummmy space로 지정하여 cricular queue구현하기 */
/* queue에서 원소 삭제하는 함수 */
Node* deQueue()
{
	//queue가 empty일 때(rear과 front 동일) -> 삭제할 원소 없으므로 에러 발생 
	if(rear==front)
		return NULL;	//NULL 반환
	else
		return queue[(++front)%MAX_QUEUE_SIZE];	//front를 front+1로 재설정하고, 변경된 front에 위치한 큐의 원소 반환
}


/* queue에서 원소 삽입하는 함수 */
void enQueue(Node* aNode)
{
	//rear+1과 front가 동일하지 않고(queue가 full인 상태x) -> 원소를 queue에 삽입할 수 있음
	if((rear+1)%MAX_QUEUE_SIZE!=front)	
		queue[(++rear)%MAX_QUEUE_SIZE]=aNode;	//rear를 rear+1로 재설정하고, 변경된 rear위치에 aNode 삽입
	else
		return ;
}

/**
 * textbook: p 225
 */
/* 레벨순서 순회(non-recursive) -> circular queue이용 */
void levelOrder(Node* ptr)
{
	if(!ptr)	//공백 트리 
	{
		printf("There is no node in tree\n");
		return ;		//QQ. 이렇게 return ;으로 표시하면, 이 함수를 반환하긴 하는거야? 이 함수에서 탈출하는거야?
	}	
	enQueue(ptr);	//tree의 첫번째 노드 삽입
	while(1)
	{
		ptr=deQueue();
		if(ptr)
		{	
			printf(" [%d] ",ptr->key);
			if(ptr->left)				//ptr의 왼쪽노드가 NULL이 아닐때, queue에 원소 삽입
				enQueue(ptr->left);
			if(ptr->right)				//ptr의 오른쪽노드가 NULL이 아닐때, queue에 원소 삽입
				enQueue(ptr->right);
		}
		//ptr=NULL일 때, 반복문 탈출 
		else
			break;
	}
}