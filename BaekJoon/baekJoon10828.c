#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

typedef struct stack {	
	int num;	
	struct stack* bottom;	
} STACK;	

void push(STACK**, int);	
void pop(STACK**);	
void size(STACK**);	
void empty(STACK**);	
void top(STACK**);	

int main() {	
	STACK* topp = NULL;	
	STACK* temp = NULL;	
	int a = 0, insert = 0;	
	char array[20] = { (char)NULL };	

	scanf("%d", &a);	

	for (int i = 0; i < a; i++) {	
		scanf("%s", array);	

		if (strcmp(array, "push") == 0) {	
			scanf("%d", &insert);	
			push(&topp, insert);	
		}	
		else if (strcmp(array, "pop") == 0) pop(&topp);	
		else if (strcmp(array, "size") == 0) size(&topp);	
		else if (strcmp(array, "empty") == 0) empty(&topp);	
		else if (strcmp(array, "top") == 0) top(&topp);	

		for (unsigned int j = 0; j < strlen(array); j++) {	
			array[j] = (char)NULL;	
		}	
	}	


	return 0;	
}	

void push(STACK** top, int insert) {	
	STACK* new;	

	new = (STACK*)malloc(sizeof(STACK));	

	new->num = insert;	

	if (*top == NULL) new->bottom = NULL;	
	else new->bottom = *top;	

	*top = new;	
}	

void pop(STACK** top) {	
	STACK* temp = *top;	

	if (*top == NULL) printf("-1\n");	
	else {	
		(*top) = temp->bottom;	
		printf("%d\n", temp->num);	
		free(temp);	
	}	
}	

void size(STACK** top) {	
	STACK* temp = *top;	
	int count = 0;	

	while (temp != NULL) {	
		temp = temp->bottom;	
		count++;	
	}	

	printf("%d\n", count);	
}	

void empty(STACK** top) {	
	if (*top == NULL) printf("1\n");	
	else printf("0\n");	
}	

void top(STACK** top) {	
	if (*top == NULL) printf("-1\n");	
	else printf("%d\n", (*top)->num);	
}