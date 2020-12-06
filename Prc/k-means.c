#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	
#include <time.h> 	
#include <conio.h>	
#include <math.h>	

#define MAX_NUM 50 // 특성 최대치	
#define ARRAY_SIZE 100 // 텍스트파일 입출력시 문자열 크기 제한	
#define MAX_CENTEROID 10 // 최대 중심값의 수	
#define REPEAT_NUM 10 // 알고리즘 최대 반복수	

FILE* input;	
FILE* output;	
int data_crt[MAX_NUM][MAX_NUM] = { NULL }; // 데이터 특성 저장 배열	
int cluster_k = 0; // 군집의 수	
int cluster[MAX_NUM][MAX_NUM] = { NULL }; // 데이터의 군집 할당용 배열	
double centroid[MAX_CENTEROID][2]; // 중심의 x, y 좌표	
double centroid_temp[MAX_CENTEROID][2]; // 이전의 중심값 저장용 변수	


void title(); //메인화면	
void txt_input(); // txt파일 인풋	
void txt_output(); // 결과물 txt파일로 출력	
void print_cluster(); // 특성 데이터 좌표 형식으로 출력	
void clustering(); // 군집화	
void exception(); // 데이터 값의 군집 할당	
void maximization(); // 중심값의 재배치	

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 메인	
void main() {	
	int n;	

	title(); // 1이면 시작 0이면 종료	
	scanf("%d", &n);	

	switch (n)	
	{	
	case 1:	
		printf("\n");	
		txt_input(); // 메모장의 특성 읽어들이기	

		clustering(); // k-means 알고리즘	
		print_cluster(); // 좌표 출력	

		txt_output(); // 결과값 output 메모장에 저장	
		break;	
	case 0:	
		printf("고객 성향 분석 프로그램을 종료합니다.\n");	
		break;	
	default:	
		printf("잘못된 입력입니다.\n");	
		break;	
	}	


}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 함수	
void title()	
{	
	printf("=============================================================");	
	printf("\n\n\n\n");	
	printf("		<고객 성향 분석 프로그램>\n\n");	
	printf("			시작하기(1)\n");	
	printf("			종료하기(0)\n");	
	printf("\n\n\n\n");	
	printf("=============================================================\n\n\n\n>");	
}	

void txt_input() {	
	char num[ARRAY_SIZE] = { (char)NULL }; // 인풋 텍스트 임시 저장 배열	
	int count = 1; // 스위치문용 변수	
	int a = 0, b = 0; // 특성1,2 임시 저장용 변수	

	input = fopen("input.txt", "r");	


	while (!feof(input)) { // 메모장에서 특성 읽어들이기	
		fscanf(input, "%s", &num);	

		switch (count) {	
		case 1:	
			printf("특성1: %s, ", num);	
			a = atoi(num);	
			break;	
		case 2:	
			printf("특성2: %s\n", num);	
			b = atoi(num);	
			data_crt[a - 1][b - 1]++; // 특성 배열에 데이터 추가	

			count = 0;	
			break;	
		default:	
			break;	
		}	


		count++;	
	}	

	fclose(input);	

	printf("\n");	
}	

void txt_output() {	
	output = fopen("output.txt", "w");	

	for (int k = 0; k < cluster_k; k++) {	
		fprintf(output, "군집%d\n", k+1);	

		for (int i = 0; i < MAX_NUM; i++) {	
			for (int j = 0; j < MAX_NUM; j++) {	
				// 해당 군집일시 저장	
				if (cluster[i][j] == k+1) fprintf(output, "특성1:%d, 특성2:%d\n", i + 1, j + 1);	
			}	
		}	

		fprintf(output, "\n");	
	}	

	fclose(output);	
}	

void print_cluster() {	
	int count = 0; // 중심값 존재 확인용 변수	
	int count_k = 0; // 중심값 출력 누적량 확인용 변수	

	printf("-----------------------------------------------------------------------------------------------------\n");	
	for (int i = MAX_NUM - 1; i >= 0; i--) {	
		for (int j = 0; j < MAX_NUM; j++) {	
			count = 0;	

			for (int k = 0; k < MAX_CENTEROID; k++) {	
				if ((int)centroid[k][0] == j && (int)centroid[k][1] == i && count_k < cluster_k) { // 해당 좌표에 중심값이 존재할 경우	
					printf("★");	
					count = 1;	
					count_k++; // 0,0 으로 초기화 되어있는 중심값들을 걸러내기 위해 사용	
				}	
			}	

			if (data_crt[j][i] != 0 && count != 1) printf("○");	
			else if (count != 1) printf("  ");	
		}	
		printf("|\n");	
	}	
	printf("-----------------------------------------------------------------------------------------------------\n");	
}	

void clustering() {	
	int count = 0; // 알고리즘 반복 수 설정용	
	int compare = 0; // 이전의 중심값의 위치와 현재 중심값의 위치를 통해 알고리즘 반복유무 확인용 변수	

	printf("설정할 군집의 수를 입력하세요(최대 10):");	
	scanf("%d", &cluster_k);	


	if (cluster_k > 0) {	
		srand(time(NULL));	

		for (int i = 0; i < cluster_k; i++) {	
			centroid[i][0] = (rand() % MAX_NUM - 1.0) + 1.0; // 중심 y값 랜덤 설정 1 ~ MAX_NUM	
			centroid[i][1] = (rand() % MAX_NUM - 1.0) + 1.0; // 중심 x값 랜덤 설정 1 ~ MAX_NUM	

			printf("%.0lf %.0lf\n", centroid[i][0], centroid[i][1]);	
		}	
	}	

	printf("\n");	

	while (count < REPEAT_NUM) {	
		compare = cluster_k;	

		exception();	
		for (int i = 0; i < cluster_k; i++) {	
			centroid_temp[i][0] = centroid[i][0]; // 중심값 재설정 전 변화를 비교하기 위해 이전 중심값을 저장	
			centroid_temp[i][1] = centroid[i][1];	
		}	


		maximization();	

		for (int i = 0; i < cluster_k; i++) // 이전과 현재 중심값비교	
			if (centroid_temp[i][0] == centroid[i][0] && centroid_temp[i][1] == centroid[i][1]) compare--;	


		if (compare == 0) count = REPEAT_NUM;	
		count++;	
		printf("\n\n");	
	}	

}	

void exception() {	
	double x_distance[MAX_CENTEROID] = { 0 }, y_distance[MAX_CENTEROID] = { 0 }; // 해당 점에서부터 각 중심값 까지의 거리 저장용	
	double distance[MAX_CENTEROID]; // 점과 점 사이의 거리	
	double min = 9999; // 최소 거리 찾기용 변수	
	int count = 0; // 최소거리를 가지는 중심값의 번호	

	for (int i = 0; i < MAX_NUM; i++) {	
		for (int j = 0; j < MAX_NUM; j++) {	

			if (data_crt[i][j] != NULL) { // 해당 좌표에 특성이 존재한다면	
				for (int k = 0; k < cluster_k; k++) { // 그 특성과 중심값들과의 거리 계산	

					x_distance[k] = (i+1.0) - centroid[k][0];	
					if (x_distance[k] < 0) x_distance[k] = x_distance[k] * -1;	

					y_distance[k] = (j+1.0) - centroid[k][1];	
					if (y_distance[k] < 0) y_distance[k] = y_distance[k] * -1;	

					distance[k] = sqrt(((double)x_distance[k] * (double)x_distance[k]) + ((double)y_distance[k] * (double)y_distance[k])); // 거리 계산	

					if (distance[k] < min) { // 그중 최소거리를 가진 중심값 찾기	
						min = distance[k];	
						count = k+1;	
					}	

				}	

				cluster[i][j] = count;	

				min = 9999;	
			}	
		}	
	}	

	for (int i = 0; i < MAX_NUM; i++) {	
		for (int j = 0; j < MAX_NUM; j++) {	
			if (cluster[i][j]!= 0) printf("%d, %d : 군집%d\n", i+1, j+1, cluster[i][j]);	

		}	
	}	

}	

void maximization() {	
	double cluster_avg[MAX_CENTEROID][2] = { 0 };	
	int cluster_count[MAX_CENTEROID] = { NULL };	

	for (int i = 0; i < MAX_NUM; i++) {	
		for (int j = 0; j < MAX_NUM; j++) {	
			if (data_crt[i][j] != NULL) { // 해당 좌표에 특성이 존재한다면	
				for (int k = 0; k < cluster_k; k++) {	
					if (cluster[i][j] == k+1) {	
						cluster_avg[k][0] = cluster_avg[k][0] + i;	
						cluster_avg[k][1] = cluster_avg[k][1] + j;	

						cluster_count[k]++;	
					}	
				}	
			}	
		}	
	}	

	for (int k = 0; k < cluster_k; k++) {	

		if (cluster_avg[k][0] != 0 && cluster_avg[k][1] != 0) {	
			centroid[k][0] = cluster_avg[k][0] / cluster_count[k];	
			centroid[k][1] = cluster_avg[k][1] / cluster_count[k];	
		}	

	}	
	for (int k = 0; k < cluster_k; k++)	
		printf("군집%d: %lf, %lf\n", k+1, centroid[k][0] + 1, centroid[k][1] + 1);	
}