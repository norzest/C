#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	

#define ARRAY_SIZE 200100	




typedef struct {	
	int num[ARRAY_SIZE];	
	int heap_size;	
} HEAPTYPE;	

HEAPTYPE heap1;	

void insertHEAP( HEAPTYPE*, int);	
void deleteHEAP(HEAPTYPE*);	

int main() {	

	int a = 0, insertnum = 0;	

	heap1.heap_size = 0;	

	scanf("%d", &a);	
	getchar();	


	for (int i = 0; i < a; i++) {	
		scanf("%d", &insertnum);	
		getchar();	

		if (insertnum == 0) {	
			if (heap1.heap_size > 0) deleteHEAP(&heap1);	
			else printf("0\n");	
		}	
		else insertHEAP(&heap1, insertnum);	

	}	

	return 0;	
}	

void insertHEAP(HEAPTYPE* heap, int insertnum) {	
	int i = 0;	
	heap->heap_size++;	
	i = heap->heap_size;	

	while ((i != 1) && (insertnum <= heap->num[i / 2])) {	
		heap->num[i] = heap->num[i / 2];	
		i /= 2;	
	}	

	heap->num[i] = insertnum;	
}	

void deleteHEAP(HEAPTYPE* heap) {	
	int parent, child;	
	int item, temp;	

	printf("%d\n", heap->num[1]);	

	item = heap->num[1];	
	temp = heap->num[(heap->heap_size)--];	
	parent = 1;	
	child = 2;	
	while (child <= heap->heap_size) {	
		if ((child < heap->heap_size) &&	
			(heap->num[child] > heap->num[child + 1]))	
			child++;	
		if (temp <= heap->num[child]) break;	
		heap->num[parent] = heap->num[child];	
		parent = child;	
		child *= 2;	
	}	

	heap->num[parent] = temp;	


}