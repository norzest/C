#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

typedef struct que {	
	int num;	
	struct que* head;	
	struct que* tail;	
} QUE;	

void AddQue(QUE**, QUE**);	
int Search(QUE**, int);	
int Del(QUE**, QUE**, int);	

int main() {	
	QUE* front = NULL;	
	QUE* back = NULL;	
	int n = 0, m = 0, p = 0;	
	int count = 0;	

	scanf("%d %d", &n, &m);	

	for (int i = 0; i < n; i++) {	
		AddQue(&front, &back);	
	}	

	for (int i = 0; i < m; i++) {	
		scanf("%d", &p);	
		count += Del(&front, &back, p);	
	}	

	printf("%d\n", count);	

	return 0;	
}	

void AddQue(QUE** front, QUE** back) {	
	QUE* new;	

	new = (QUE*)malloc(sizeof(QUE));	

	if (*front == NULL) {	
		new->num = 1;	
		*front = new;	
		*back = new;	
		new->head = *front;	
		new->tail = *front;	
	}	
	else {	
		new->num = (*back)->num + 1;	
		(*back)->tail = new;	
		new->head = *back;	
		(*front)->head = new;	
		new->tail = *front;	
		*back = new;	
	}	
}	

int Search(QUE** front, int p) {	
	QUE* temp = *front;	
	int count = 0;	
	int countb = 0;	

	do {	

		if (p == temp->num) break;	

		count++;	
		temp = temp->tail;	
	} while (temp != *front);	

	temp = *front;	

	do {	

		if (p == temp->num) break;	

		countb++;	
		temp = temp->head;	
	} while (temp != *front);	

	if (count <= countb) return 1;	
	else return -1;	
}	

int Del(QUE** front, QUE** back, int p) {	
	QUE* temp = *front;	
	int a = 0, count = 0;	
	a = Search(front, p);	

	if (a == 1) {	
		do {	

			if (p == temp->num) {	
				*front = temp->tail;	
				temp->head->tail = temp->tail;	
				temp->tail->head = temp->head;	
				free(temp);	
				break;	
			}	

			count++;	
			temp = temp->tail;	
		} while (temp != *front);	
	}	
	else { 	
		do {	

			if (p == temp->num) {	
				*front = temp->tail;	
				temp->head->tail = temp->tail;	
				temp->tail->head = temp->head;	
				free(temp);	
				break;	
			}	

			count++;	
			temp = temp->head;	
		} while (temp != *front);	
	}	

	return count;	
}