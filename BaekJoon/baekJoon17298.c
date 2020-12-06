#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	

#define ARRAY_SIZE 1000100	

int array[ARRAY_SIZE] = { 0, };	
int array2[ARRAY_SIZE] = { 0, };	
int size = 0, size2 = 0, msize = 0;	

void push(int);	
void pop(int);	
void compare(int);	

int main() {	
	int n = 0, num = 0;	

	scanf("%d", &n);	
	getchar();	

	for (int i = 0; i < n; i++) {	
		scanf("%d", &num);	
		getchar();	
		compare(num);	
	}	

	if (array2[1] != 0) printf("%d", array2[1]);	
	else printf("-1");	

	for (int i = 2; i <= msize + 1; i++) {	
		if (array2[i] != 0) printf(" %d", array2[i]);	
		else printf(" -1");	

	}	

	if (array2[1] == 0) n--;	

	for (int i = 1; i < n - msize; i++) printf(" -1");	

	if (array2[1] == 0) 	
		printf(" -1");	


	printf("\n");	

	return 0;	
}	

void push(int num) {	
	array[size] = num;	
	size++;	
	size2++;	
}	

void pop(int num) {	
	int temp = size2;	
	while (array2[temp] != 0) temp--;	
	array2[temp] = num;	
	array[size] = 0;	
	size--;	
}	

void compare(int num) {	
	if (array[0] == 0) push(num);	
	else {	

		while (array[size-1] < num && size >= 1) {	
			msize++;	
			pop(num);	
		}	
		push(num);	
	}	
}