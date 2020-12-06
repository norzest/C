#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	

typedef struct tree {	
	char alphabet;	
	struct tree* left, * right;	
} TREE;	

TREE* ROOT = NULL;	
TREE* POINT = NULL;	
TREE* TEMPPOINT[30] = { NULL };	
int count = 0;	


void preorder(TREE*); // 전위 순회	
void inorder(TREE*); // 중위 순회	
void postorder(TREE*); // 후위 순회	
void insertNode(char, char, char); // 트리 생성	
int searchNode(TREE*, char); // 영문자가 있는지 탐색	

int main() {	
	int n = 0;	
	char root, left, right;	

	scanf("%d", &n);	
	getchar();	

	for (int i = 0; i < n; i++) {	
		scanf("%c %c %c", &root, &left, &right);	
		getchar();	

		insertNode(root, left, right);	
	}	


	preorder(ROOT); printf("\n");	
	inorder(ROOT); printf("\n");	
	postorder(ROOT); printf("\n");	

	return 0;	
}	

void preorder(TREE* temp) {	
	if (temp != NULL) {	
		if(temp->alphabet != '.') printf("%c", temp->alphabet);	
		preorder(temp->left);	
		preorder(temp->right);	
	}	
}	

void inorder(TREE* temp) {	
	if (temp != NULL) {	
		inorder(temp->left);	
		if (temp->alphabet != '.') printf("%c", temp->alphabet);	
		inorder(temp->right);	
	}	
}	

void postorder(TREE* temp) {	
	if (temp != NULL) {	
		postorder(temp->left);	
		postorder(temp->right);	
		if (temp->alphabet != '.') printf("%c", temp->alphabet);	
	}	
}	

void insertNode(char root, char left, char right) {	
	TREE* new, * newR, * newL, * temp, * temp2 = NULL;	
	new = (TREE*)malloc(sizeof(TREE));	
	newR = (TREE*)malloc(sizeof(TREE));	
	newL = (TREE*)malloc(sizeof(TREE));	
	int num = searchNode(ROOT, root);	

	if (ROOT == NULL) {	
		ROOT = new;	
		new->left = NULL;	
		new->right = NULL;	
	}	

	if (num == 0) { // 발견 안됐을 경우	

		new->alphabet = root;	
		new->left = newL;	
		new->right = newR;	
		newL->alphabet = left;	
		newL->left = NULL;	
		newL->right = NULL;	
		newR->alphabet = right;	
		newR->left = NULL;	
		newR->right = NULL;	
		TEMPPOINT[count] = new;	
		count++;	

	}	
	else if (num == 1) { // 발견 됐을 경우	
		temp = POINT;	
		///////////////////////////////////////// 왼쪽 값 발견됐을경우	
		for (int i = 0; i < count; i++) {	
			if (TEMPPOINT[i]->alphabet == left && left != '.') {	
				temp2 = TEMPPOINT[i];	
				break;	
			}	
		}	
		if (temp2 != NULL) {	
			temp->left = temp2;	
			temp->right = newR;	
			newR->alphabet = right;	
			newR->left = NULL;	
			newR->right = NULL;	
		}	
		///////////////////////////////////////// 오른쪽 값 발견됐을경우	
		for (int i = 0; i < count; i++) {	
			if (TEMPPOINT[i]->alphabet == right && right != '.') {	
				temp2 = TEMPPOINT[i];	
				break;	
			}	
		}	
		if (temp2 != NULL && temp2->right == NULL) {	
			temp->right = temp2;	
			temp->left = newL;	
			newL->alphabet = left;	
			newL->left = NULL;	
			newL->right = NULL;	
		}	
		///////////////////////////////////////// 둘다 발견 안됐을 경우	
		if (temp2 == NULL) { 	
			temp->left = newL;	
			temp->right = newR;	
			newL->alphabet = left;	
			newL->left = NULL;	
			newL->right = NULL;	
			newR->alphabet = right;	
			newR->left = NULL;	
			newR->right = NULL;	
		}	
	}	
}	

int searchNode(TREE* temp, char search) { // 0 = 발견 안됨 1 = 발견 됨	
	int count = 0;	
	if (temp != NULL) {	
		// 해당 포인터에서 발견 안됐을 경우 자손 노드 탐색	
		if (temp->alphabet != search) {	
			count += searchNode(temp->left, search);	
			count += searchNode(temp->right, search);	
			// 자손 노드에서 발견 됐을 경우 1 반환	
			if (count == 0) return 0;	
			else return 1;	
		}	
		else {	
			POINT = temp;	
			return 1;	
		}	
	}	
	else return 0;	
}