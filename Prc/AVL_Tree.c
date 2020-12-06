#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	

typedef struct Node {	
	int data;	
	struct Node* left,* right;	
} AVL;	

AVL* ROOT;	

// 트리 회전	
AVL* rotate_LL(AVL*);	
AVL* rotate_RR(AVL*);	
AVL* rotate_RL(AVL*);	
AVL* rotate_LR(AVL*);	
// 트리 높이 반환	
int get_height(AVL*);	
// 노드 간의 높이의 차이를 반환	
int get_height_diff(AVL*);	
// 트리의 균형 잡기	
AVL* rebalance(AVL**);	
// 트리 삽입	
AVL* avl_insert(AVL**, int);	
// 트리 탐색	
AVL* avl_search(AVL*, int);	

////////////////////////////////////////////////////////////////////////// 메인 함수	
void main() {	
	int key = 0;	

	printf("-- 삽입할 key 입력 --\n");	
	while (scanf("%d", &key) != 0) {	
		while(getchar() != '\n');	
		avl_insert(&ROOT, key);	
	}	

	while (getchar() != '\n');	

	printf("-- 탐색할 key 입력 --\n");	
	while (scanf("%d", &key) != 0) {	
		while (getchar() != '\n');	
		avl_search(ROOT, key);	
		printf("\n");	
	}	

}	
//////////////////////////////////////////////////////////////////////////	

AVL* rotate_LL(AVL* parent) {	
	AVL* child = parent->left;	
	parent->left = child->right;	
	child->right = parent;	

	return child;	
}	

AVL* rotate_RR(AVL* parent) {	
	AVL* child = parent->right;	
	parent->right = child->left;	
	child->left = parent;	

	return child;	
}	

AVL* rotate_RL(AVL* parent) {	
	AVL* child = parent->right;	
	parent->right = rotate_LL(child);	

	return rotate_RR(parent);	
}	

AVL* rotate_LR(AVL* parent) {	
	AVL* child = parent->left;	
	parent->left = rotate_RR(child);	

	return rotate_LL(parent);	
}	

int get_height(AVL* node) {	
	int height = 0;	

	// 트리가 더 깊은 쪽에서 + 1을 한 후 반환	
	// max(X,Y) ((X) > (Y) ? (X) : (Y))	
	if (node != NULL)	
		height = 1 + max(get_height(node->left), get_height(node->right));	


	return height;	
}	

int get_height_diff(AVL* node) {	
	if (node == NULL) return 0;	

	return get_height(node->left) - get_height(node->right);	
}	

AVL* rebalance(AVL** node) {	
	int height_diff = get_height_diff(*node);	

	if (height_diff > 1) { // 왼쪽의 깊이가 2개 이상 클 경우	
		// 왼쪽 노드의 자손이 왼쪽에 있으면 LL 아닐 경우 LR	
		if (get_height_diff((*node)->left) > 0)	
			* node = rotate_LL(*node);	
		else	
			* node = rotate_LR(*node);	
	}	
	else if (height_diff < -1) { // 오른쪽의 깊이가 2개 이상 클 경우	
		// 오른쪽 노드의 자손이 오른쪽에 있으면 RR 아닐 경우 RL	
		if (get_height_diff((*node)->right) < 0)	
			* node = rotate_RR(*node);	
		else	
			*node = rotate_RL(*node);	
	}	

	// 트리가 이미 균형잡혀있을 경우	
	return *node;	
}	

AVL* avl_insert(AVL** root, int key) {	
	if (*root == NULL) { // 해당 트리가 비어있을 경우	
		*root = (AVL*)malloc(sizeof(AVL));	

		if (*root == NULL) {	
			printf("메모리 할당 에러\n");	
			exit(1);	
		}	

		(*root)->data = key;	
		(*root)->left = NULL;	
		(*root)->right = NULL;	
	}	
	else if (key < (*root)->data) { // 삽입하려는 key 값이 현재 노드의 key 값보다 작을 경우	
		(*root)->left = avl_insert(&((*root)->left), key);	
		(*root) = rebalance(root);	
	}	
	else if (key > (*root)->data) { // 삽입하려는 key 값이 현재 노드의 key 값보다 클 경우	
		(*root)->right = avl_insert(&((*root)->right), key);	
		(*root) = rebalance(root);	
	}	
	else { // 같은 key 값은 삽입 불가	
		printf("중복 키 에러\n");	
		exit(1);	
	}	

	return *root;	
}	

AVL* avl_search(AVL* node, int key) {	
	if (node == NULL) return NULL;	

	printf("%d ", node->data);	

	if (key == node->data) // 전달된 key 값을 찾았을 경우	
		return node;	
	else if (key < node->data) // 전달된 key 값이 현재 노드의 key 값보다 작을 경우 왼쪽 자손을 탐색	
		return avl_search(node->left, key);	
	else // 전달된 key 값이 현재 노드의 key 값보다 클 경우 오른쪽 자손을 탐색 (같을 경우는 없음)	
		return avl_search(node->right, key);	
}