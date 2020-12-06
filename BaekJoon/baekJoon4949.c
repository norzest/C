#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

typedef struct stack {	
	char stk;	
	struct stack* link;	
} STACK;	

void push(char, STACK**);	
int pop(char, STACK**);	

int main() {	
	char array[110] = { (char)NULL };	
	STACK* stk;	
	int a = 0;	

	stk = NULL;	


	while (1) {	
		scanf("%[^/\n]s", array);	
		getchar();	
		fflush(stdin);	

		if (array[0] == '.' && array[1] == (char)NULL) break;	

		for (unsigned int i = 0; i < strlen(array); i++) {	
			switch (array[i]) {	
			case '(':	
			case '[':	
				push(array[i], &stk);	
				break;	
			case ')':	
			case ']':	
				if (stk == NULL) a = 1;	
				else if (a == 0) a = pop(array[i], &stk);	
				break;	
			default:	
				break;	
			}	
		}	

		if (stk == NULL && a == 0) printf("yes");	
		else printf("no");	
		printf("\n");	

		a = 0;	
		free(stk);	
		stk = NULL;	
		for (int k = 0; k < 110; k++) array[k] = (char)NULL;	
	}	


	return 0;	
}	



void push(char array, STACK** stackP) {	
	STACK* new;	
	new = (STACK*)malloc(sizeof(STACK));	

	new->stk = array;	

	if (*stackP == NULL) new->link = NULL;	
	else new->link = *stackP;	

	*stackP = new;	
}	



int pop(char array, STACK** stackP) {	
	STACK* TEMP = *stackP;	

	if (TEMP->stk == '(' && array == ')') {	
		*stackP = (*stackP)->link;	
		free(TEMP);	
		return 0;	
	}	
	else if (TEMP->stk == '[' && array == ']') {	
		*stackP = (*stackP)->link;	
		free(TEMP);	
		return 0;	
	}	
	else return 1;	
}