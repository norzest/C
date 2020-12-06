#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <string.h>	
#include <windows.h>	
#include <mysql.h>	

#define DB_ADDRESS "127.0.0.1"	
#define DB_ID "root"	
#define DB_PASS "DBAdmin2010"	
#define DB_NAME "test_db"	


void screen_menu(); // 메뉴 출력	
void INSERT_SQL(MYSQL**); // SQL 삽입	
void DELETE_SQL(MYSQL**); // SQL 삭제	
void UPDATE_SQL(MYSQL**); // SQL 수정	


////////////////////////////////////////////////////////////////////////////////////// MAIN	
int main() {	
	MYSQL_ROW row;	
	MYSQL_RES* res;	
	MYSQL mysql;	
	MYSQL* connect = NULL,* insert_c = NULL;	
	int stat;	

	char menu_select[50] = { (char)NULL };	

	mysql_init(&mysql);	
	connect = mysql_real_connect(&mysql, DB_ADDRESS, DB_ID, DB_PASS, DB_NAME, 3306, 0, 0);	
	mysql_set_character_set(connect, "euckr"); //한글 깨짐 방지	

	if (connect == NULL) {	
		fprintf(stderr, "mysql connection error : %s\n", mysql_error(&mysql));	
		return 1;	
	}	
	while (1) {	
		system("cls"); // 화면 초기화	

		stat = mysql_query(connect, "select * from friends"); // stat에 mysql_query의 값을 반환받아 오류 검사	
		if (stat != 0) {	
			fprintf(stderr, "mysql query error : %s", mysql_error(&mysql));	
			return 1;	
		}	

		res = mysql_store_result(connect); // 쿼리 결과 전체 읽기	

		printf("      이름|            전화번호|   나이|\n");	
		while ((row = mysql_fetch_row(res)) != NULL) { // 결과 값을 하나씩 출력	
			printf("%10s|%20s|%7s|\n", row[0], row[1], row[2]);	
		}	
		mysql_free_result(res);	

		screen_menu();	
		scanf("%s", menu_select);	
		getchar();	

		if (strcmp(menu_select, "insert") == 0) INSERT_SQL(&connect);	
		else if (strcmp(menu_select, "delete") == 0) DELETE_SQL(&connect);	
		else if (strcmp(menu_select, "update") == 0) UPDATE_SQL(&connect);	
		else if (strcmp(menu_select, "exit") == 0) return 1;	

		fflush(stdin);	
	}	


	mysql_close(&mysql);	


	return 0;	
}	
//////////////////////////////////////////////////////////////////////////////////////	

void screen_menu() {	
	printf("------------------------------------------\n");	
	printf("삽입 : insert\n");	
	printf("삭제 : delete\n");	
	printf("수정 : update\n");	
	printf("종료 : exit\n");	
	printf("------------------------------------------\n");	
	printf("실행할 명령 : ");	
}	

void INSERT_SQL(MYSQL** connect) {	
	char insert_query[150] = "insert into `test_db`.`friends` (`name`, `phone`, `age`) values('";	
	char insert_name[10];	
	char insert_adnum[16];	
	char insert_age[5];	

	printf("입력할 이름: ");	
	scanf("%s", insert_name);	
	getchar();	
	printf("입력할 전화번호: ");	
	scanf("%s", insert_adnum);	
	getchar();	
	printf("입력할 나이: ");	
	scanf("%s", insert_age);	
	getchar();	

	strcat(insert_query, insert_name);	
	strcat(insert_query, "', '");	
	strcat(insert_query, insert_adnum);	
	strcat(insert_query, "', ");	
	strcat(insert_query, insert_age);	
	strcat(insert_query, ")");	

	mysql_query(*connect, insert_query);	
}	

void DELETE_SQL(MYSQL** connect) {	
	char delete_query[150] = "delete from `test_db`.`friends` where ";	
	char delete_name[10] = { (char)NULL };	
	char delete_adnum[16] = { (char)NULL };	
	char delete_age[5] = { (char)NULL };	
	int count = 0;	

	printf("삭제할 리스트의 이름: ");	
	scanf("%[^\n]s", delete_name);	
	getchar();	
	printf("삭제할 리스트의 전화번호: ");	
	scanf("%[^\n]s", delete_adnum);	
	getchar();	
	printf("삭제할 리스트의 나이: ");	
	scanf("%[^\n]s", delete_age);	
	getchar();	

	if (strcmp(delete_name, "") != 0) { // 이름을 입력했을 경우 추가	
		strcat(delete_query, "name = '");	
		strcat(delete_query, delete_name);	
		strcat(delete_query, "'");	
		count++;	
	}	

	if (strcmp(delete_adnum, "") != 0) { // 전화번호를 입력했을 경우 추가	
		if (count != 0) { // 전에 다른 조건을 입력했을 경우	
			strcat(delete_query, " and phone = '");	
			strcat(delete_query, delete_adnum);	
			strcat(delete_query, "'");	
		}	
		else { // 전화번호만 입력했을 경우	
			strcat(delete_query, "phone = '");	
			strcat(delete_query, delete_adnum);	
			strcat(delete_query, "'");	
			count++;	
		}	
	}	

	if (strcmp(delete_age, "") != 0) { // 나이를 입력했을 경우 추가	
		if (count != 0) { // 전에 다른 조건을 입력했을 경우	
			strcat(delete_query, " and age = '");	
			strcat(delete_query, delete_age);	
			strcat(delete_query, "'");	
		}	
		else { // 나이만 입력했을 경우	
			strcat(delete_query, "age = '");	
			strcat(delete_query, delete_age);	
			strcat(delete_query, "'");	
		}	
	}	

	mysql_query(*connect, "SET SQL_SAFE_UPDATES=0");	
	mysql_query(*connect, delete_query);	
}	

void UPDATE_SQL(MYSQL** connect) {	
	char update_query[200] = "update `test_db`.`friends` set ";	
	char update_name[10] = { (char)NULL }; // 찾을 이름	
	char update_adnum[16] = { (char)NULL }; // 찾을 전화번호	
	char update_age[5] = { (char)NULL }; // 찾을 나이	
	char change_name[10] = { (char)NULL }; // 바꿀 이름	
	char change_adnum[16] = { (char)NULL }; // 바꿀 전화번호	
	char change_age[5] = { (char)NULL }; // 바꿀 나이	
	int count = 0;	

	printf("수정할 리스트의 이름: ");	
	scanf("%[^\n]s", update_name);	
	getchar();	
	printf("수정할 리스트의 전화번호: ");	
	scanf("%[^\n]s", update_adnum);	
	getchar();	
	printf("수정할 리스트의 나이: ");	
	scanf("%[^\n]s", update_age);	
	getchar();	

	printf("수정할 이름: ");	
	scanf("%[^\n]s", change_name);	
	getchar();	
	printf("수정할 전화번호: ");	
	scanf("%[^\n]s", change_adnum);	
	getchar();	
	printf("수정할 나이: ");	
	scanf("%[^\n]s", change_age);	
	getchar();	

	if (strcmp(change_name, "") != 0) { // 이름을 입력했을 경우 추가	
		strcat(update_query, "name = '");	
		strcat(update_query, change_name);	
		strcat(update_query, "'");	
		count++;	
	}	

	if (strcmp(change_adnum, "") != 0) { // 전화번호를 입력했을 경우 추가	
		if (count != 0) { // 전에 다른 조건을 입력했을 경우	
			strcat(update_query, ", phone = '");	
			strcat(update_query, change_adnum);	
			strcat(update_query, "'");	
		}	
		else { // 전화번호만 입력했을 경우	
			strcat(update_query, "phone = '");	
			strcat(update_query, change_adnum);	
			strcat(update_query, "'");	
			count++;	
		}	
	}	

	if (strcmp(change_age, "") != 0) { // 나이를 입력했을 경우 추가	
		if (count != 0) { // 전에 다른 조건을 입력했을 경우	
			strcat(update_query, ", age = '");	
			strcat(update_query, change_age);	
			strcat(update_query, "'");	
		}	
		else { // 나이만 입력했을 경우	
			strcat(update_query, "age = '");	
			strcat(update_query, change_age);	
			strcat(update_query, "'");	
			count++;	
		}	
	}	

	if (count != 0) strcat(update_query, " where ");	
	else return; // 수정할 데이터가 없을 경우 리턴	

	count = 0;	

	if (strcmp(update_name, "") != 0) { // 이름을 입력했을 경우 추가	
		strcat(update_query, "name = '");	
		strcat(update_query, update_name);	
		strcat(update_query, "'");	
		count++;	
	}	

	if (strcmp(update_adnum, "") != 0) { // 전화번호를 입력했을 경우 추가	
		if (count != 0) { // 전에 다른 조건을 입력했을 경우	
			strcat(update_query, " and phone = '");	
			strcat(update_query, update_adnum);	
			strcat(update_query, "'");	
		}	
		else { // 전화번호만 입력했을 경우	
			strcat(update_query, "phone = '");	
			strcat(update_query, update_adnum);	
			strcat(update_query, "'");	
			count++;	
		}	
	}	

	if (strcmp(update_age, "") != 0) { // 나이를 입력했을 경우 추가	
		if (count != 0) { // 전에 다른 조건을 입력했을 경우	
			strcat(update_query, " and age = '");	
			strcat(update_query, update_age);	
			strcat(update_query, "'");	
		}	
		else { // 나이만 입력했을 경우	
			strcat(update_query, "age = '");	
			strcat(update_query, update_age);	
			strcat(update_query, "'");	
			count++;	
		}	
	}	

	mysql_query(*connect, update_query);	
}