#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

#define ARRAY_SIZE 210000	

typedef struct stack {	
	int num;	
	struct stack* bottom;	
} STACK;	

STACK* stack = NULL;	
int count = 1;	
char result[ARRAY_SIZE] = { (char)NULL };	

char push();	
char pop();	


int main() {	
	int a = 0, z = 0;	
	int num = 0;	


	scanf("%d", &a);	

	for (int i = 0; i < a; i++) {	
		scanf("%d", &num);	

		for (; count <= num; count++) {	
			result[z] = push();	
			z++;	
		}	

		if (num >= stack->num) {	
			result[z] = pop();	
			z++;	
		}	

		num = 0;	
	}	


	if (stack != NULL) printf("NO\n");	
	else 	
		for (unsigned int i = 0; i < strlen(result); i++) 	
			if(result[i] != NULL) printf("%c\n", result[i]);	



	return 0;	
}	

char push() {	
	STACK* new;	

	new = (STACK*)malloc(sizeof(STACK));	

	new->num = count;	

	if (stack == NULL) new->bottom = NULL;	
	else new->bottom = stack;	

	stack = new;	

	return '+';	
}	

char pop() {	
	STACK* temp = stack;	

	if (stack != NULL) {	
		stack = stack->bottom;	
		free(temp);	
		return '-';	
	}	
	else return (char)NULL;	
}