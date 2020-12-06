#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <string.h>	
#include <conio.h>	

#define ADMIN_ID "root"	
#define ADMIN_PW "admin2019"	
#define MAX 16	
#define TRUE 1            // TRUE는 1로 지정 	
#define FALSE 0            // FALSE는 0으로 지정 	
#define INF 10000         // 무한대(INF)는 10000으로 설정 	
#define LOCATION 10         // 지역 이름 최대 길이 	

typedef struct fast {      // Dijkstra 구조체 	
	int short_distance[MAX];      // 최단 거리 	
	int prelocation[MAX];      // 최단경로중 도착한 정점의 직전위치 	
}FAST;	

typedef struct list {	
	char id[30];	
	char pwd[30];	
	char name[30];	
	char jumin[30];	
	char city[30];	
	char number[30];	
	struct list* Rlink;	
	struct list* Llink;	
} List;	


void error(char*); // 에러 메시지 출력 (문장)	
void InitList(List**); // 리스트 초기화 (초기화 하려는 리스트의 주소값)	
void MenuPrint(); // 메뉴 출력	
void MenuPrint2(); // 회원용 메뉴 출력	
void CreateList(List**, List**, FILE*); // 텍스트파일의 내용 불러들이기 ( 마지막 목록 포인터, 첫 목록 포인터, 파일 인자 )	
void AddList(List**, List**, FILE*); // 내용 추가 ( 마지막 목록 포인터, 첫 목록 포인터, 파일 인자 )	
void DelList(List**, FILE*, char*); // 내용 삭제 ( 첫 목록 포인터, 파일 인자 )	
List* SearchList(List*, char*); // 목록 검색 ( 첫 목록 포인터 )	
void display(List*); // 목록 출력 ( 첫 목록 포인터 )	

int login(); // 로그인	
int login_check(char*, char*); // 회원 리스트 확인해서 맞으면 1 or 2 or 0 반환	
void modi(); // 회원 정보 수정	


// 그래프	
void dijkstra(FAST*, int);         // Dijkstra 테이블 생성 	
void find_way(FAST*, int, int);            // 최단경로 역추적 	

List* list;	
List* temp;	
FILE* stream;	
char tempID[30];	

char city[MAX][LOCATION] = { "서울","춘천","속초","시흥","수원",         //0~4번 도시 이름 	
				  "원주","강릉","천안","상주","보령",         //5~9번 도시 이름 	
				  "대전","전주","대구","광주","마산","부산"//10~16번 도시 이름 	
};	

///////////////////////////////////////////////////////////////////////////// 메인 함수	
int main() {	

	char num;	
	char del[50];	
	char del2;	
	int n = 0;	
	FAST fastSet;                     // Dijkstra 테이블 선언 	
	int start, end;                     // 시작 위치, 도착 위치 (수치) 	
	int i, check;                     // 반복문 용 임시 변수 선언 	
	char starting_point[LOCATION], destination[LOCATION];   // 시작,도착 Location 변수 (문자열)	



	InitList(&list);	
	InitList(&temp);	

	stream = fopen("Member_List.txt", "r+");	

	while (!feof(stream)) {	
		CreateList(&temp, &list, stream);	
	}	

	n = login();	

	if (n == 1)// 관리자로 로그인 할 경우 (회원을 맘대로 주물러! 회원 추가는 회원가입시 자동으로 연결리스트로)	
	{	
		while (1) {	
			system("cls");	
			printf("-관리자로 로그인 하였습니다-\n");	

			MenuPrint();	

			printf("번호 입력: ");	
			scanf("%c", &num);	
			while (getchar() != '\n');	

			switch (num) {	
			case '1':	
				AddList(&temp, &list, stream);	
				break;	
			case '2':	
				printf("삭제할 회원의 ID를 입력해주세요: ");	
				fscanf(stdin, "%[^\n]s", del);	
				while (getchar() != '\n');	
				fflush(stdin);	
				DelList(&list, stream, del);	
				break;	
			case '3':	
				display(list);	
				system("pause");	
				break;	
			case '4':	
				puts("프로그램 종료\n");	
				exit(1);	
			default:	
				break;	
			}	
		}	

	}	
	else// 회원으로 로그인 할 경우 	
	{	
		while (1) {	
			system("cls");	
			printf("-회원으로 로그인 하였습니다-\n");	

			MenuPrint2();	

			printf("번호 입력: ");	
			scanf("%c", &num);	
			while (getchar() != '\n');	

			switch (num) {	
			case '1':	
				printf("정말로 탈퇴하시겠습니까?(y / n) ");	
				scanf("%c", &del2);	
				getchar();	
				if(del2 == 'y') DelList(&list, stream, tempID);	
				exit(1);	
				break;	
			case '2':	
				modi();	
				break;	
			case '3':	
				////////////////////////////////////////////////////////////////////////////// 네비게이션 실행	
				printf("도시목록:");	
				for (int i = 0; i < MAX; i++)	
				{	
					for (int j = 0; j < 1; j++) {	
						printf(" %s  ", &city[i][j]);	
					}	
				}	

				printf("\n\n");	


				while (1) {	
					printf("[S&J네비게이션] 종료를 원하시면 종료를 치세요\n");	

					/***** 출발 도시 입력 *****/	
					check = 1;                        // check(정상 입력 확인) 변수 초기화	
					while (check) {	
						printf("[1] 출발도시명 : ");	
						fflush(stdin);                   // stdin 버퍼 초기화 	
						scanf("%s", &starting_point);            // 출발도시 입력 대기 	
						if (!strcmp(starting_point, "종료")) exit(0); // 종료 입력시 프로그램 종료 	

						/***** Exception 확인 *****/	
						for (i = 0; i < MAX; i++) {	
							if (!strcmp(city[i], starting_point)) {	
								check = 0;               // 정상입력일 경우 check 0로 변경 	
								start = i;               // 출발 위치(수치) 입력 	
								break;	
							}	
						}	
						if (check != 0) {                  // Location 이름 잘못 입력하였을 경우 	
							printf("  [ERROROR] %s 은(는) 없는지역입니다.\n", starting_point);	
						}	
					}	

					/***** 도착 도시 입력 *****/	
					check = 1;                        // check(정상 입력 확인) 변수 초기화 	
					while (check) {	
						printf("[2] 도착도시명 : ");	
						fflush(stdin);                  // stdin 버퍼 초기화 	
						scanf("%s", &destination);            // 도착도시 입력 대기 	
						if (!strcmp(destination, "종료")) exit(0);   // 종료 입력시 프로그램 종료 	
						/***** Exception 확인 *****/	
						for (i = 0; i < MAX; i++) {	
							if (!strcmp(city[i], destination)) {	
								check = 0;               // 정상입력일 경우 check 0로 변경 	
								end = i;                  // 도착 위치(수치) 입력 	
								break;	
							}	
						}	
						if (check != 0) {                  // Location 이름 잘못 입력하였을 경우 	
							printf("  [ERROROR] %s 은(는) 없는지역입니다.\n", destination);	
						}	
					}	

					/***** 예외처리 *****/	
					if (start != end) {                     // 출발,도착 지역이 다른 경우 	
						dijkstra(&fastSet, start);      // Dijkstra 테이블 생성 	
						find_way(&fastSet, start, end);        // 최단경로 출력 	
						// 도착지역에 대한 최단거리 출력 	
						printf(", 최단거리 = %dkm\n\n", fastSet.short_distance[end]);	
					}	
					else {                           // 출발, 도착 지역이 같은 경우 	
						printf("  출발지와 도착지가 같은 장소는 설정할 수 없습니다.\n");	
					}	
				}	
				break;	
				///////////////////////////////////////////////////////////////////////////////////////////////////	
			case '4':	
				puts("프로그램 종료\n");	
				exit(1);	
			default:	
				break;	
			}	

		}	

	}	



	fclose(stream);	


	return 0;	
}	

///////////////////////////////////////////////////////////////////////////// 함수	
void error(char* ch) {	
	puts(ch);	
}	

void MenuPrint() { // 관리자 메뉴	
	puts("--------------------------");	
	puts("|1. 회원 추가            |");	
	puts("|2. 회원 삭제            |");	
	puts("|3. 회원 목록            |");	
	puts("|4. 종료                 |");	
	puts("--------------------------");	

}	

void MenuPrint2() { // 회원 메뉴	
	puts("--------------------------");	
	puts("|1. 회원 탈퇴            |");	
	puts("|2. 회원 정보 수정       |");	
	puts("|3. S&J네비게이션 실행   |");	
	puts("|4. 종료                 |");	
	puts("--------------------------");	

}	

void InitList(List** list) {	
	*list = NULL;	
}	

void CreateList(List** temp, List** list, FILE* stream) {	
	List* new;	
	new = (List*)malloc(sizeof(List));	
	fscanf(stream, "%s %s %s %s %s %s", new->id, new->pwd, new->name, new->jumin, new->city, new->number);	
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
	printf("아이디를 입력해주세요:");	
	scanf("%s", new->id);	
	getchar();	

	printf("비밀먼호를 입력해주세요:");	
	scanf("%s", new->pwd);	
	getchar();	

	printf("이름을 입력해주세요:");	
	scanf("%s", new->name);	
	getchar();	

	printf("주민번호를 입력해주세요:");	
	scanf("%s", new->jumin);	
	getchar();	

	printf("거주지를 입력해주세요:");	
	scanf("%s", new->city);	
	getchar();	

	printf("전화번호를 입력해주세요:");	
	scanf("%s", new->number);	
	getchar();	

	fprintf(stream, "\n%s %s %s %s %s %s", new->id, new->pwd, new->name, new->jumin, new->city, new->number);	

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

void DelList(List** list, FILE* stream, char* del) {	
	List* temp = *list;	

	if (del != NULL) {	
		do { // 선택한 리스트 삭제	
			if (strcmp(del, temp->id) == 0) {	

				if (temp == *list)* list = temp->Rlink;	
				temp->Llink->Rlink = temp->Rlink;	
				temp->Rlink->Llink = temp->Llink;	
				free(temp);	
				break;	
			}	

			temp = temp->Rlink;	
		} while (temp != *list);	
	}	
	temp = *list;	

	fclose(stream);	
	stream = fopen("Member_List.txt", "w");	

	do { // 선택한 리스트 파일에서 삭제	
		fprintf(stream, "%s %s %s %s %s %s", temp->id, temp->pwd, temp->name, temp->jumin, temp->city, temp->number);	

		temp = temp->Rlink;	

		if (temp != *list) fprintf(stream, "\n");	
	} while (temp != *list);	

	fclose(stream);	
	stream = fopen("Member_List.txt", "r+");	
}	

List* SearchList(List* list, char* id) {	
	List* temp = list;	
	do {	

		if (strcmp(id, temp->id) == 0) return temp;	

		temp = temp->Rlink;	

	} while (temp != list);	

	return NULL;	
}	

void display(List* list) {	
	List* temp = list;	

	do {	
		fprintf(stdout, "%s %s %s %s %s %s\n", temp->id, temp->pwd, temp->name, temp->jumin, temp->city, temp->number);	
		temp = temp->Rlink;	
	} while (temp != list);	
}	

int login() {	
	int n, cnt = 0, i = 0;	
	char id[30];	
	char pwd[30];	

	while (1)	
	{	
		for (int j = 0; j < 30; j++) {	
			pwd[j] = (char)NULL;	
		}	
		i = 0;	
		n = 0;	

		printf("====로그인==== \n");	
		printf("1.로그인 \n");	
		printf("2.회원가입 \n");	
		printf("===============\n");	
		printf("모드를 선택해주세요:");	
		scanf("%d", &n);	
		while (getchar() != '\n');	


		switch (n)	
		{	
		case 1:	

			printf("아이디를 입력해주세요:");	
			scanf("%s", id);	
			getchar();	
			strcpy(tempID, id);	

			printf("비밀번호를 입력해주세요:");	
			while ((pwd[i] = _getch()) != '\r') {	

				if (pwd[i] == 8) {	
					printf("\b");	
					fputs(" ", stdout);	
					printf("\b");	

					if (i > 0)	
						i--;	
				}	

				else {	
					fputs("*", stdout); i++;	
				}	
			} printf("\n");	
			pwd[i] = (char)NULL;	

			cnt = login_check(id, pwd);	


			if (cnt == 1) return 1; // 관리자일 경우 1 반환	
			else if (cnt == 2) return 2; // 일반 회원일 경우 2 반환	
			else error("ID 또는 비밀번호가 틀렸습니다\n");	

			break;	

		case 2:// 회원가입	
			AddList(&temp, &list, stream);	
			break;	

		default:	
			error("잘못된 값을 입력하였습니다\n");	
			break;	
		}	
	}	
}	

int login_check(char* id, char* password) {	
	List* temp = SearchList(list, id);	


	if (strcmp(id, ADMIN_ID) == 0 && strcmp(password, ADMIN_PW) == 0) return 1; // 관리자 일 때	

	if (temp == NULL) return 0; // 해당 아이디가 없을 때	
	if (strcmp(temp->pwd, password) != 0) return 0; // 비밀번호가 틀렸을 때	

	return 2;	

}	

void modi() {	
	List* temp = SearchList(list, tempID);	
	int a;	
	char modifi[30] = { (char)NULL };	

	puts("--------------------------");	
	puts("|1. 비밀번호             |");	
	puts("|2. 주소                 |");	
	puts("|3. 전화번호             |");	
	puts("--------------------------");	
	printf("수정하고자 하는 메뉴를 선택해주세요:");	

	scanf("%d", &a);	
	while (getchar() != '\n');	

	switch (a) {	
	case 1:	
		printf("수정하실 비밀번호를 입력해주세요:");	
		scanf("%s", modifi);	
		while (getchar() != '\n');	

		strcpy(temp->pwd,modifi);	
		DelList(&list, stream, NULL);	
		break;	
	case 2:	
		printf("수정하실 주소를 입력해주세요:");	
		scanf("%s", modifi);	
		while (getchar() != '\n');	

		strcpy(temp->city, modifi);	
		DelList(&list, stream, NULL);	
		break;	
	case 3:	
		printf("수정하실 전화번호를 입력해주세요:");	
		scanf("%s", modifi);	
		while (getchar() != '\n');	

		strcpy(temp->number, modifi);	
		DelList(&list, stream, NULL);	
		break;	
	default:	
		break;	
	}	
}	

////////////////////////////////////////////////////////////////////////////////////////////////// 그래프	

/********** 다익스트라 생성 **********/	
void dijkstra(FAST* fastSet, int start) {	
	/***** 기본 지역 정보 *****/	
	int location[MAX][MAX] = {	
	   0,70,INF,30,40,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,	
	   70,0,90,INF,INF,65,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,	
	   INF,90,0,INF,INF,INF,35,INF,INF,INF,INF,INF,INF,INF,INF,INF,	
	   30,INF,INF,0,25,INF,INF,INF,INF,95,INF,INF,INF,INF,INF,INF,	
	   40,INF,INF,25,0,75,INF,65,INF,INF,INF,INF,INF,INF,INF,INF,	
	   INF,65,INF,INF,75,0,85,INF,80,INF,INF,INF,INF,INF,INF,INF,	
	   INF,INF,35,INF,INF,85,0,INF,INF,INF,INF,INF,INF,INF,INF,280,	
	   INF,INF,INF,INF,65,INF,INF,0,INF,100,80,INF,INF,INF,INF,INF,	
	   INF,INF,INF,INF,INF,80,INF,INF,0,INF,INF,INF,95,INF,INF,INF,	
	   INF,INF,INF,95,INF,INF,INF,100,INF,0,INF,INF,INF,110,INF,INF,	
	   INF,INF,INF,INF,INF,INF,INF,80,INF,INF,0,50,105,INF,INF,INF,	
	   INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,50,0,INF,30,85,INF,	
	   INF,INF,INF,INF,INF,INF,INF,INF,95,INF,105,INF,0,INF,55,75,	
	   INF,INF,INF,INF,INF,INF,INF,INF,INF,110,INF,30,INF,0,40,INF,	
	   INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,85,55,40,0,INF,	
	   INF,INF,INF,INF,INF,INF,280,INF,INF,INF,INF,INF,75,INF,INF,0	
	};	

	int visited[MAX], next, temp;	

	/***** 변수 초기화 *****/	
	for (int i = 0; i < MAX; i++) {	
		visited[i] = 0;            // 방문한 지역 변수, 초기는 0으로 초기화	
		fastSet->prelocation[i] = start;   // 최단경로 중 방문한 정점의 직전 위치 	
	}	
	next = start;                  // (처음 시작 위치) 	

	/***** 다익스트라 테이블 생성 *****/	
	for (int i = 0; i < MAX; i++) {	
		for (int j = 0; j < MAX; j++) {	
			/***** 첫 최단경로 테이블 값을 시작위치에서의 값으로 입력 *****/	
			if (i == 0) {	
				fastSet->short_distance[j] = location[start][j];   // 시작위치에서의 값 입력 	
				visited[start] = TRUE;                  // 시작위치 방문 처리(TRUE=1)	
			}	

			else {	
				// 새로 찾은 거리가 현재 거리보다 가까운 경우 값 변경 	
				if ((fastSet->short_distance[j]) > (fastSet->short_distance[next] + location[next][j])) {	
					// 새로 찾은 거리 입력 	
					fastSet->short_distance[j] = fastSet->short_distance[next] + location[next][j];	
					// 새로 찾은 지역(가까운 노드 바로 이전 지역 위치 입력)	
					fastSet->prelocation[j] = next;	
				}	
			}	
		}	
		temp = INF;      // 비교용 변수-> INF로 초기화 	

		for (int k = 0; k < MAX; k++) {	
			/***** 방문하지 않은 지역중 가장 temp(다른 지역 값)보다 작은 경우 *****/	
			if ((temp > fastSet->short_distance[k]) && (visited[k] == FALSE)) {	
				temp = fastSet->short_distance[k];      // 작은 거리 값 입력 	
				next = k;                     // 다음 이동할 지역 입력 	
			}	
		}	
		visited[next] = TRUE;                  // 다음 이동할 지역 방문으로 처리 	
	}	
}	

/********** 최단경로 탐색**********/	
void find_way(FAST* fastSet, int start, int find) {	
	int i, set, way[MAX];	


	way[0] = start;         // 시작 지역(수치)를 맨처음 배열에 삽입 	
	for (i = 1; i < MAX; i++) {	
		way[i] = -1;         // 모든 나머지 배열 값을 -1로 초기화 	
	}	
	set = MAX - 1;            // 배열 최대개수 셋팅	
	/***** 역순으로 된 경로를 정순으로 정렬 *****/	
	while (find != start) {	
		way[set] = find;      // 배열 뒷부분부터 경로 입력 (정순으로 정렬 과정) 	
		set--;            // set -1 (뒤에서 앞으로 1칸 이동) 	
		find = fastSet->prelocation[find];   // find에 이전위치에 대한 가까운 경로 값 입력	
	}	

	/***** 정순으로 된 경로를 출력 *****/	
	for (i = 0; i < MAX; i++) {	
		if (way[i] != -1) {                  // 배열값이 -1이 아닌경우만 출력 	
			printf("%s", city[way[i]]);      // 위치값에 대한 지역 이름(문자열) 출력 	
			if (i != (MAX - 1)) {               // 마지막 경로가 아닌경우 -> 출력 	
				printf(" -> ");	
			}	
		}	
	}	
}