#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	
#include <conio.h>	

typedef struct list {	
	char array[50];	
	struct list* Rlink;	
	struct list* Llink;	
} List;	

void error(char*); // 에러 메시지 출력 (문장)	
void InitList(List**); // 리스트 초기화 (초기화 하려는 리스트의 주소값)	
void MenuPrint(); // 메뉴 출력	
void MovePointer(); // 재생중인 음악 이동	
void CreateList(List**, List**, FILE*); // 텍스트파일의 내용 불러들이기 ( 마지막 목록 포인터, 첫 목록 포인터, 파일 인자 )	
void AddList(List**, List**, FILE*); // 내용 추가 ( 마지막 목록 포인터, 첫 목록 포인터, 파일 인자 )	
void DelList(List**, FILE*); // 내용 삭제 ( 첫 목록 포인터, 파일 인자 )	
void SearchList(List*); // 목록 검색 ( 첫 목록 포인터 )	
void display(List*); // 목록 출력 ( 첫 목록 포인터 )	

List* PlayPointer;	

///////////////////////////////////////////////////////////////////////////// 메인 함수	
int main() {	
	FILE* stream;	
	List* list;	
	List* temp;	
	char num;	

	InitList(&list);	
	InitList(&temp);	

	stream = fopen("mp3.txt", "r+");	

	while (!feof(stream)) {	
		CreateList(&temp, &list, stream);	
	}	

	PlayPointer = list;	

	while(1) {	
		system("cls");	
		display(list);	
		MenuPrint();	

		printf("번호 입력: ");	
		scanf("%c", &num);	
		while (getchar() != '\n');	

		switch (num) {	
		case '0':	
			MovePointer();	
			break;	
		case '1':	
			AddList(&temp, &list, stream);	
			break;	
		case '2':	
			DelList(&list, stream);	
			break;	
		case '3':	
			SearchList(list);	
			break;	
		case '4':	
			puts("프로그램 종료\n");	
			exit(1);	
		default:	
			break;	
		}	
	}	

	fclose(stream);	


	return 0;	
}	

///////////////////////////////////////////////////////////////////////////// 함수	
void error(char* ch) {	
	puts(ch);	
}	

void MenuPrint() {	
	puts("--------------------------");	
	puts("|0. 재생 목록 이동       |");	
	puts("|1. 리스트 추가          |");	
	puts("|2. 리스트 삭제          |");	
	puts("|3. 리스트 검색          |");	
	puts("|4. 종료                 |");	
	puts("--------------------------");	
	fprintf(stdout, "현재 재생중인 음악: %s\n\n", PlayPointer->array);	
}	

void MovePointer() {	
	char move;	
	printf("('<' Or '>'): ");	
	scanf("%c", &move);	
	while (getchar() != '\n');	

	switch (move) {	
	case '<':	
		PlayPointer = PlayPointer->Llink;	
		break;	
	case '>':	
		PlayPointer = PlayPointer->Rlink;	
		break;	
	default:	
		break;	
	}	
}	

void InitList(List** list) {	
	*list = NULL;	
}	

void CreateList(List** temp, List** list, FILE* stream) {	
	List* new;	
	new = (List*)malloc(sizeof(List));		
	fscanf(stream, "%[^/\n]s", new->array);	
	fgetc(stream);	

	if (*list == NULL) {	
		*temp = new;	
		*list = new;	
		new->Rlink = *list;	
		new->Llink = *list;	

	}	
	else {	
		(*temp)->Rlink = new;	
		new->Llink = *temp;	
		(*list)->Llink = new;	
		new->Rlink = *list;	
		*temp = new;	
	}	
}	

void AddList(List** temp, List** list, FILE* stream) {	
	List* new;	
	new = (List*)malloc(sizeof(List));	
	printf("추가할 리스트 입력: ");	
	fscanf(stdin, "%[^\n]s", new->array);	
	while (getchar() != '\n');	
	fprintf(stream, "\n%s", new->array);	

	if (*list == NULL) {	
		*temp = new;	
		*list = new;	
		new->Rlink = *list;	
		new->Llink = *list;	

	}	
	else {	
		(*temp)->Rlink = new;	
		new->Llink = *temp;	
		(*list)->Llink = new;	
		new->Rlink = *list;	
		*temp = new;	
	}	
}	

void DelList(List** list, FILE* stream) {	
	List* temp = *list;	
	char del[50];	

	printf("삭제할 리스트 입력: ");	
	fscanf(stdin, "%[^\n]s", del);	
	while (getchar() != '\n');	
	fflush(stdin);	
	  do { // 선택한 리스트 삭제	
		if (strcmp(del, temp->array) == 0) {	

			if (temp == *list) *list = temp->Rlink;	
			if (temp == PlayPointer) PlayPointer = PlayPointer->Rlink;	
			temp->Llink->Rlink = temp->Rlink;	
			temp->Rlink->Llink = temp->Llink;	
			free(temp);	
			break;	
		}	

		temp = temp->Rlink;	
	} while (temp != *list);	

	temp = *list;	

	fclose(stream);	
	stream = fopen("mp3.txt", "w");	

	do { // 선택한 리스트 파일에서 삭제	
		fprintf(stream, "%s", temp->array);	

		temp = temp->Rlink;	

		if (temp != *list) fprintf(stream, "\n");	
	} while (temp != *list);	

	fclose(stream);	
	stream = fopen("mp3.txt", "r+");	
}	

void SearchList(List* list) {	
	List* temp = list;	
	char search[50];	
	int count = 0;	

	printf("검색할 리스트 입력: ");	
	fscanf(stdin, "%[^/\n]s", search);	

	 do {	
		count++;	

		if (strcmp(search, temp->array) == 0) {	
			fprintf(stdout, "검색한 리스트는 %d번째에 있습니다.\n", count);	
			_getch();	
			while (getchar() != '\n');	
			fflush(stdin);	
			break;	
		}	

		temp = temp->Rlink;	
	 } while (temp != list);	
}	

void display(List* list) {	
	List* temp = list;	
	int count = 0;	

	 do {	
		count++;	
		fprintf(stdout, "%d. %s\n", count, temp->array);	
		temp = temp->Rlink;	
	} while (temp != list);	
}