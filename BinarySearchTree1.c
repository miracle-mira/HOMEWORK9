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

/*노드 구조체*/
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h); //트리 초기화

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	          //inorder(왼쪽>부모>오른쪽) 방식으로 트리 순회
void preorderTraversal(Node* ptr);            //preorder(부모>왼쪽>오른쪽) 방식으로 트리 순회
void postorderTraversal(Node* ptr);	          //postorder(왼쪽>오른쪽>부모) 방식으로 트리 순회
int insert(Node* head, int key);              //노드 삽입
int deleteLeafNode(Node* head, int key);      //주어진 key 값을 가진 단말노드 삭제
Node* searchRecursive(Node* ptr, int key);    //순환함수 사용해서 노드 위치 찾기
Node* searchIterative(Node* head, int key);   //반복문 사용해서 노드 위치 찾기
void freeNode(Node* ptr);                     //동적 할당 해제
int freeBST(Node* head);                      //동적 할당 해제
 

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL; //트리 순회시 사용되는 변수로 찾으려는 노드가 있는지 없는지 확인하는 변수

	printf("\n\n[----- [Park Mira] [2020069006] -----]\n\n");

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

/*트리 초기화 함수: 헤드노드 변수의 주소를 넘겨줬기 때문에 이중포인터를 매개변수로 함.*/
int initializeBST(Node** h) {

	/*헤드노드가 생성되어있을 경우*/
	if(*h != NULL)
		freeBST(*h); //노드에 할당된 동적 메모리를 해제하는 함수 호출


	/*헤드노드가 생성되어있지 않을 경우*/
	*h = (Node*)malloc(sizeof(Node)); //헤드노드로 사용할 노드를 동적 메모리 할당하여 헤드노드 변수 값으로 대입
	(*h)->left = NULL;	              //헤드의 left는 root의 주소를 담음.
	(*h)->right = *h;                 //헤드의 right는 헤드노드의 주소를 담음.
	(*h)->key = -9999;                //헤드의 key 값은 임의로 설정함.

	return 1;
}


/*inorder(왼쪽>부모>오른쪽) 방식으로 트리 순회*/
void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);    //왼쪽이 NULL일 때까지 순회
		printf(" [%d] ", ptr->key);     //출력
		inorderTraversal(ptr->right);   //오른쪽이 NULL일 때까지 순회
	}

}


/*preorder(부모>왼쪽>오른쪽) 방식으로 트리 순회*/
void preorderTraversal(Node* ptr)
{
    if(ptr) {
		printf(" [%d] ", ptr->key);     //출력
		inorderTraversal(ptr->left);    //왼쪽이 NULL일 때까지 순회
		inorderTraversal(ptr->right);   //오른쪽이 NULL일 때까지 순회
	}
}


/*postorder(왼쪽>오른쪽>부모) 방식으로 트리 순회*/
void postorderTraversal(Node* ptr)
{
	inorderTraversal(ptr->left);    //왼쪽이 NULL일 때까지 순회
	inorderTraversal(ptr->right);   //오른쪽이 NULL일 때까지 순회
	printf(" [%d] ", ptr->key);     //출력
}


/*노드 삽입: 노드의 키 값은 중복되지 않음을 가정함.*/
int insert(Node* head, int key)
{
    Node* new = (Node *)malloc(sizeof(Node)); //새로운 노드 생성
    new -> key = key;                         //새로운 node에 key 값 설정
    Node* p = head->left;                     //노드를 추적할 변수를 선언한 후, 루트로 설정함.
    Node* prev = NULL;                        //기존 단말노드로 그 노드의 오른쪽 또는 왼쪽이 새로운 노드가 들어갈 위치
   
    /*root 노드 생성*/
    if(p == NULL){
        head->left = new;

        new->left = NULL;
        new->right = NULL;

        return 0;
    }

    /*노드 삽입 위치 정하기*/
    while(p != NULL){

        prev = p;

        if(key > p->key){
            p = p->right;
        }

        else{
            p = p->left;
        }
    }


    /*새로운 노드 삽입*/
    if(key < prev->key){
        prev->left = new;     //새로운 노드를 단말 노드로 추가
    }

    else{
        prev->right = new;
    }

    /*새로운 노드가 단말 노드이므로 오른쪽,왼쪽을 NULL값으로 설정*/
    new->left = NULL;
    new->right = NULL;
}


/*주어진 key 값을 가진 단말노드 삭제*/
int deleteLeafNode(Node* head, int key)
{
	/*헤드노드가 없는 경우*/
	if (head == NULL) {
		printf("\n Nothing to delete!!\n"); //오류 메시지 출력

		return -1;
	}

	/*헤드노드만 있는 경우: 노드가 하나도 없는 경우*/
	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	
	Node* ptr = head->left;   //현재 위치 나타내는 변수 선언: root부터 시작
	Node* parentNode = head;  //현재 위치의 전 위치를 나타내는 변수 선언: 즉, 현재 위치 노드의 부모노드 위치임


	/*현재 위치를 단말노드까지 이동함*/
	while(ptr != NULL) {

		if(ptr->key == key) {
		//주어진 key 값과 일치한 것이 있는지 확인

			if(ptr->left == NULL && ptr->right == NULL) {
			//주어진 key 값을 가진 노드가 단말 노드인지 확인

				/*root 노드를 삭제할 경우: head의 왼쪽 노드를 NULL값으로 초기화*/
				if(parentNode == head)
					head->left = NULL;

				/*삭제할 노드의 부모노드의 right 또는 left 삭제: 원래 노드의 위치를 파악헤 삭제함.*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;

				else
					parentNode->right = NULL;

				free(ptr); //동적 할당 해제를 함으로써 단말노드 삭제 
			}

			//주어진 key 값을 가진 노드가 단말 노드가 아닐 경우
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		//현재 위치를 부모 노드를 저장하는 변수에 저장
		parentNode = ptr;

		//주어진 key값이 현재 노드의 key 값보다 크면 오른쪽 노드로 이동
		if(ptr->key < key)
			ptr = ptr->right;

		//주어진 key값이 현재 노드의 key 값보다 작으면 왼쪽 노드로 이동
		else
			ptr = ptr->left;


	}

	//주어진 key 값을 가진 노드가 하나도 없을 경우 오류문 출력
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}


/*순환함수 사용해서 노드 위치 찾기*/
Node* searchRecursive(Node* ptr, int key)
{
	/*root노드가 없을 경우 또는 주어진 key값을 가진 노드가 없을 경우*/
	if(ptr == NULL)
		return NULL;

	//주어진 key값이 현재 노드의 key 값보다 크면 오른쪽 노드로 이동
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	
	//주어진 key값이 현재 노드의 key 값보다 작으면 왼쪽 노드로 이동
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/*주어진 key 값을 가진 노드의 주소를 반환*/
	return ptr;
}


/*반복문 사용해서 노드 위치 찾기*/
Node* searchIterative(Node* head, int key)
{
	/*현재 위치를 저장할 변수: root 노드로 설정*/
	Node* ptr = head->left;

	/*주어진 key 값을 가진 노드 찾기*/
	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr; /*주어진 key 값을 가진 노드의 주소를 반환*/

		//주어진 key값이 현재 노드의 key 값보다 크면 오른쪽 노드로 이동
		if(ptr->key < key) 
			ptr = ptr->right;

		//주어진 key값이 현재 노드의 key 값보다 작으면 왼쪽 노드로 이동
		else
			ptr = ptr->left;
	}

	return NULL; //주어진 key 값을 가진 노드가 없음
}

/*동적 할당 해제 함수*/
void freeNode(Node* ptr)
{
	if(ptr) {
		//순환함수 이용해 동적할당 해제
		freeNode(ptr->left);   //왼쪽 끝까지 탐색
		freeNode(ptr->right);  //오른쪽 끝까지 탐색
		free(ptr);             //하나씩 해제
	}
}

int freeBST(Node* head)
{

	/*root노드가 없고, 헤드노드만 있을 경우*/
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	//root노드 위치를 새로운 변수로 생성해 저장: 헤드는 마지막에 삭제해야하므로.
	Node* p = head->left;

	//root 노드 주소를 인수로 보냄
	freeNode(p);

	//마지막으로 헤드노드도 동적 할당 해제
	free(head);

	return 1;
}


