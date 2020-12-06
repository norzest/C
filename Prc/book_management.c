#include <windows.h>	
#include <mysql.h>	
#include <string.h>	
#include <stdio.h>	
#include <conio.h>	

//#define DB_HOST "127.0.0.1"	
//#define DB_USER "root"	
//#define DB_PASS "DBAdmin2010"	
//#define DB_NAME "project1"	

typedef struct admin	
{	
	char DB_HOST[50];	
	char DB_USER[50];	
	char DB_PASS[50];	
	char DB_NAME[50];	
}admin;	

//성민	
void mysql_insert();//삽입	
void mysql_select();//조회	
void mysql_update();// 갱신	
// 영효	
void mysql_delete();//삭제	
void mysql_order();//정렬	
void sort_print(char*, int); //정렬 목록 출력	
void help();// 뀨	
int menu();// 뀨뀨?	

int  query_stat;	
MYSQL* connection = NULL, conn;//   데이타 베이스에 연결했을때, 이 연결을 다루기 위해 사용되는 구조체	
MYSQL_RES* sql_result; //(SELECT, SHOW, DESCRIBE)등의 쿼리를 질의 했을 때 그 결과를 다루기 위해 사용되는 구조체.	
MYSQL_ROW sql_row;//이것은 데이타의 하나의 row 값을 가리킨다. 만약 row 값이 없다면 null 을 가르키게 된다.	

int main()	
{	
	admin db = { "127.0.0.1","root","DBAdmin2010","project1" };	
	admin login;	
	int mode, i = 0;	

	for (int i = 0; i < 50; i++) {	
		login.DB_PASS[i] = (char)NULL;	
	}	

	mysql_init(&conn);//mysql DB에 연결하기 전에 가장 먼저 실행되며, mysql 연결 지시자를 초기화 하는 일을 한다	

	printf("아이디를 입력하세요 : ");	
	scanf("%s", login.DB_USER);	
	printf("패스워드를 입력하세요 : ");	

	while ((login.DB_PASS[i] = _getch()) != '\r') {	
		if (login.DB_PASS[i] == 8) {	
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

	login.DB_PASS[i] = (char)NULL;	

	if (strcmp(login.DB_USER, db.DB_USER) == 0 && strcmp(login.DB_PASS, db.DB_PASS) == 0) {	
		connection = mysql_real_connect(&conn, db.DB_HOST, db.DB_USER, login.DB_PASS, db.DB_NAME, 3306, (char*)NULL, 0); /* mysql 서버에 실제로	
		접근하게 된다. 접근하는데 필요한, 호스트이름(DB_HOST), 유저계정(DB_USER), 계정에 대한 패스워드(DB_PASS), 접근 하고자 하는 DB이름(DB_NAME),	
		포트번호(DB_PORT) 등이 들어간다. */	

		mysql_set_character_set(connection, "euckr");// 연결한 후 한글로 설정!!	

		if (connection == NULL)	
		{	
			fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));	
			return 1;	
		}	
		while (1)	
		{	
			system("cls");	

			mode = menu();	


			switch (mode)	
			{	
			case 0:	
				help();	
				break;	
			case 1:	
				mysql_insert();	
				break;	

			case 2:	
				mysql_delete();	
				break;	

			case 3:	
				mysql_select();	
				break;	

			case 4:	
				mysql_update();	
				break;	

			case 5:	
				mysql_order();	
				break;	

			case 6:	
				printf("프로그램을 종료합니다...\n");	
				return;	

			default:	
				printf("잘못 입력하였습니다.\n");	
				while (getchar() != '\n');	
				break;	
			}	
			system("pause");	

			fflush(stdin);	
		}	

		mysql_free_result(sql_result);	

		mysql_close(connection);	
	}	

	else if (strcmp(login.DB_USER, db.DB_USER) != 0)	
		printf("아이디가 일치 하지 않습니다.\n");	

	else if (strcmp(login.DB_PASS, db.DB_PASS) != 0)	
		printf("비밀번호가 일치 하지 않습니다.\n");	

	return 0;	
}	

int menu() {	
	int select;	

	printf("모드를 선택해주세요(0:HELP 1:삽입 2:삭제 3:조회 4:갱신 5:정렬 6:종료)\n");	
	printf("=====================================================================\n");	
	scanf("%d", &select);	
	getchar();	

	return select;	
}	

void mysql_insert()//삽입	
{	
	char buff[300];	
	char t[30], a[30], c[30], number[30], p[30], t_id[10];	
	int n;	

	printf("삽입 모드를 설정해주세요(1:book 2:user):");	
	scanf("%d", &n);	
	getchar();	

	switch (n)	
	{	
	case 1:	
		printf("책 제목 입력해주세요:");	
		scanf("%[^\n]s", t);	
		getchar();	

		printf("작가의 이름을 입력해주세요:");	
		scanf("%[^\n]s", a);	
		getchar();	

		printf("출판사의 이름을 입력해주세요:");	
		scanf("%[^\n]s", c);	
		getchar();	

		sprintf(buff, "insert into `project1`.`book` (title,author,company) values ('%s','%s','%s');", t, a, c);	
		mysql_query(connection, buff);	
		break;	

	case 2:	
		printf("책의 id를 입력해주세요:");	
		scanf("%s", t_id);	
		getchar();	

		printf("책 제목 입력해주세요:");	
		scanf("%[^\n]s", t);	
		getchar();	
		sprintf(buff, "update project1.book set state='NO' where title='%s';", t);	
		mysql_query(connection, buff);	


		printf("대여자의 이름을 입력해주세요:");	
		scanf("%[^\n]s", number);	
		getchar();	

		printf("대여자의 연락처를 입력해주세요:");	
		scanf("%[^\n]s", p);	
		getchar();	

		sprintf(buff, "insert into `project1`.`tel` (id,t_title,name,number) values ('%s','%s','%s','%s');", t_id, t, number, p);//흠....id값만 뽑아오는 방법??	
		mysql_query(connection, buff);	
		break;	
	default:	
		break;	
	}	

}	


void mysql_select()//조회	
{	
	char buff[300];	
	int n;	

	printf("정보 출력 모드를 설정해주세요(1:도서 목록 2:대여한 사용자 목록):");	
	scanf("%d", &n);	
	getchar();	

	switch (n)	
	{	
	case 1:	
		sprintf(buff, "select * from project1.book;");	
		mysql_query(connection, buff);	


		printf("-----------------------------------------------------------------------------------------------------------------------\n");	
		printf("|        ID|                     제목|                     장르|                     작가|           출판사| 대여 여부|\n");	
		printf("-----------------------------------------------------------------------------------------------------------------------\n");	

		sql_result = mysql_store_result(connection);// row 값을 요청하는 쿼리라면 이 함수를 통해 쿼리의 결과값을 되돌려 받을수 있다.	
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) //mysql_store_result()를 통해서 쿼리의 결과값을 되돌려 받았다면, mysql_fetch_row()를 이용해서 row 단위로 결과 값을 가져올수 있다. 	
		{	
			printf("|%10s|%25s|%25s|%25s|%17s|%10s|\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5]);	
		}	
		printf("-----------------------------------------------------------------------------------------------------------------------\n");	
		break;	

	case 2:	
		sprintf(buff, "select t_title,name,number from project1.book b, project1.tel t where b.id=t.id;");	
		mysql_query(connection, buff);	

		sql_result = mysql_store_result(connection);// row 값을 요청하는 쿼리라면 이 함수를 통해 쿼리의 결과값을 되돌려 받을수 있다.	
		printf("-------------------------------------------------------------------------------\n");	
		printf("|                     제목|                   대여자|                 전화번호|\n");	
		printf("-------------------------------------------------------------------------------\n");	
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {	
			printf("|%25s|%25s|%25s|\n", sql_row[0], sql_row[1], sql_row[2]);	
		}	
		printf("-------------------------------------------------------------------------------\n");	
		break;	

	default:	
		printf("잘못 입력했습니다. 다시 입력해주세요...\n");	
		while (getchar() != '\n');	
		break;	
	}	
}	


void mysql_update()// 갱신?? 	
{	
	int n;	
	char buff[500], str[30];	


	printf("수정할 모드를 선택해주세요(1:도서 대여 2:도서 반납): ");	
	scanf("%d", &n);	
	getchar();	

	switch (n)	
	{	
	case 1:	
		printf("대여할 도서 이름을 입력해주세요:");	
		scanf("%[^\n]s", str);//str= 책제목	
		getchar();	

		sprintf(buff, "update project1.book set state='NO' where title= '%s' and state='YES';", str);	
		mysql_query(connection, buff);	
		break;	

	case 2:	
		printf("반납된 도서 이름을 입력해주세요:");	
		scanf("%[^\n]s", str);//str= 책제목	
		getchar();	

		sprintf(buff, "update project1.book set state='YES' where title= '%s' and state='NO';", str);	
		mysql_query(connection, buff);	
		break;	

	default:	
		printf("잘못 입력했습니다.\n");	
		while (getchar() != '\n');	
		return;	
	}	

}	

void mysql_delete() {	
	int table_num;	
	char delete_array[300] = { (char)NULL };	
	char title[40] = { (char)NULL };	

	printf("삭제할 목록이 있는 테이블을 입력해주세요(1:book 2:tel):");	
	scanf("%d", &table_num);	
	getchar();	

	if (table_num == 1) {	
		printf("삭제할 책의 제목을 입력해주세요:");	
		scanf("%s", title);	
		getchar();	

		sprintf(delete_array, "DELETE FROM `project1`.`book` WHERE title = '%s'", title);	
		mysql_query(connection, delete_array);	
	}	
	else if (table_num == 2) {	
		printf("삭제할 책의 제목을 입력해주세요:");	
		scanf("%s", title);	
		getchar();	

		sprintf(delete_array, "UPDATE project1.book set state = 'YES' WHERE title = '%s'", title);	
		mysql_query(connection, delete_array);	
		sprintf(delete_array, "DELETE FROM `project1`.`tel` WHERE t_title = '%s'", title);	
		mysql_query(connection, delete_array);	
	}	
	else {	
		printf("잘 못 입력하였습니다.\n");	
		while (getchar() != '\n');	
	}	
}	

void mysql_order() {	
	int table_num;	
	char sort_array[300] = { (char)NULL };	
	char column[20] = { (char)NULL };	
	char order_by[10] = { (char)NULL };	

	printf("정렬할 테이블을 입력해주세요(1:book 2:tel):");	
	scanf("%d", &table_num);	
	getchar();	

	if (table_num == 1) {	
		printf("기준으로 삼을 컬럼을 입력해주세요:");	
		scanf("%s", column);	
		getchar();	
		printf("정렬 기준을 입력해주세요(오름차순:ASC 내림차순:DESC):");	
		scanf("%s", order_by);	
		getchar();	

		sprintf(sort_array, "SELECT * FROM `project1`.`book` ORDER BY %s %s", column, order_by);	
		sort_print(sort_array, table_num);	
	}	
	else if (table_num == 2) {	
		printf("기준으로 삼을 컬럼을 입력해주세요:");	
		scanf("%s", column);	
		getchar();	
		printf("정렬 기준을 입력해주세요(오름차순:ASC 내림차순:DESC):");	
		scanf("%s", order_by);	
		getchar();	

		sprintf(sort_array, "SELECT * FROM `project1`.`tel` ORDER BY %s %s", column, order_by);	
		sort_print(sort_array, table_num);	
	}	
	else {	
		printf("잘 못 입력하였습니다.\n");	
		while (getchar() != '\n');	
	}	
}	

void sort_print(char* table, int count) {	
	int stat;	

	stat = mysql_query(connection, table);	
	if (stat != 0) {	
		fprintf(stderr, "mysql query error : %s\n", mysql_error(&conn));	
		return;	
	}	

	sql_result = mysql_store_result(connection);	

	if (count == 1) {	
		printf("-----------------------------------------------------------------------------------------------------------------------\n");	
		printf("|        ID|                     제목|                     장르|                     작가|           출판사| 대여 여부|\n");	
		printf("-----------------------------------------------------------------------------------------------------------------------\n");	
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) { // 결과 값을 하나씩 출력	
			printf("|%10s|%25s|%25s|%25s|%17s|%10s|\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5]);	
		}	
		printf("-----------------------------------------------------------------------------------------------------------------------\n");	
	}	
	else {	
		printf("------------------------------------------------------------------------------------------\n");	
		printf("|        ID|                     제목|                   대여자|                 전화번호|\n");	
		printf("------------------------------------------------------------------------------------------\n");	
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {	
			printf("|%10s|%25s|%25s|%25s|\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);	
		}	
		printf("------------------------------------------------------------------------------------------\n");	
	}	
	mysql_free_result(sql_result);	
}	

void help() {	
	printf("뀨?\n");	
}