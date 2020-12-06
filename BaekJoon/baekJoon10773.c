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


int main() {	
	STACK* topp = NULL;	
	STACK* temp = NULL;	
	int a = 0, insert = 0, sum = 0;	

	scanf("%d", &a);	

	for (int i = 0; i < a; i++) {	
		scanf("%d", &insert);	

		if (insert == 0) pop(&topp);	
		else push(&topp, insert);	
	}	

	temp = topp;	

	while (temp != NULL) {	
		sum += temp->num;	
		temp = temp->bottom;	
	}	

	printf("%d\n", sum);	

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

	if (*top != NULL) {	
		(*top) = temp->bottom;	
		free(temp);	
	}	
}