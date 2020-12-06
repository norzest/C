#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

typedef struct stack {	
	char ch;	
	struct stack* bottom;	
} STACK;	

void push(STACK**, char);	
int pop(STACK**);	


int main() {	
	STACK* topp = NULL;	
	STACK* temp = NULL;	
	int a = 0, compare = 0;	
	char array[100] = { (char)NULL };	

	scanf("%d", &a);	
	getchar();	

	for (int i = 0; i < a; i++) {	
		scanf("%[^/\n]s", array);	
		getchar();	
		for (unsigned int j = 0; j < strlen(array); j++) {	
			if (array[j] == '(') push(&topp, array[j]);	

			if (array[j] == ')' && compare == 0) compare = pop(&topp);	
		}	

		if (compare == 0 && topp == NULL) printf("YES\n");	
		else printf("NO\n");	

		compare = 0;	

		for (unsigned int j = 0; j < strlen(array); j++) {	
			array[j] = (char)NULL;	
		}	

		while (temp != NULL) {	
			temp = topp;	
			topp = temp->bottom;	
			free(temp);	
		}	

		topp = NULL;	
	}	

	return 0;	
}	

void push(STACK** top, char insert) {	
	STACK* new;	

	new = (STACK*)malloc(sizeof(STACK));	

	new->ch = insert;	

	if (*top == NULL) new->bottom = NULL;	
	else new->bottom = *top;	

	*top = new;	
}	

int pop(STACK** top) {	
	STACK* temp = *top;	

	if (*top != NULL) {	
		(*top) = temp->bottom;	
		free(temp);	
		return 0;	
	}	
	else return 1;	
}