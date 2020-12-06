#define _CRT_SECURE_NO_WARNINGS 	
#include <stdio.h>	
#include <stdlib.h>	

#define MAX_VERTICES 1001	

////////////////////////////////////////////////////////// 구조체	
// 그래프	
typedef struct GraphNode {	
	int vertex;	
	struct GraphNode* link;	
} GraphNode;	

typedef struct GraphType {	
	int n; // 정점의 개수	
	GraphNode* adj_list[MAX_VERTICES];	
} GraphType;	

// BFS의 방문한 정점 저장용 큐	
typedef struct QueueNode {	
	int item;	
	struct QueueNode* link;	
} QueueNode;	

typedef struct {	
	QueueNode* front, * rear;	
} QueueType;	
//////////////////////////////////////////////////////////	

int visited[MAX_VERTICES];	

////////////////////////////////////////////////////////// 함수	
// 그래프 초기화	
void graph_init(GraphType*);	
// 정점 삽입	
void insert_vertex(GraphType*);	
// 간선 삽입	
void insert_edge(GraphType*, int, int);	
// DFS( 깊이 우선 탐색 )	
void dfs(GraphType*, int);	
// BFS( 너비 우선 탐색 )	
void bfs(GraphType*, int);	

// 큐 초기화	
void queue_init(QueueType*);	
// 큐의 공백 상태 확인	
int is_empty(QueueType*);	
// 큐 삽입	
void enqueue(QueueType*, int);	
// 큐 삭제	
int dequeue(QueueType*);	
//////////////////////////////////////////////////////////	

////////////////////////////////////////////////////////// 메인 함수	
void main() {	
	GraphType g;	
	int v, u, n; // 정점, 간선, 탐색 시작할 위치	
	int a, b; // 연결할 두 정점의 번호	
	graph_init(&g);	

	scanf("%d %d %d", &v, &u, &n);	
	getchar();	

	for(int i = 0; i < v; i++)	
		insert_vertex(&g);	

	for (int i = 0; i < u; i++) {	
		scanf("%d %d", &a, &b);	
		getchar();	
		insert_edge(&g, a - 1, b - 1);	

	}	


	dfs(&g, n - 1);	
	printf("\n");	
	for (int i = 0; i < MAX_VERTICES; i++) visited[i] = 0;	
	bfs(&g, n - 1);	
	printf("\n");	


}	
//////////////////////////////////////////////////////////	

void graph_init(GraphType* g) {	
	g->n = 0;	

	for (int i = 0; i < MAX_VERTICES; i++) 	
		g->adj_list[i] = NULL;	
}	

void insert_vertex(GraphType* g) {	
	if (((g->n) + 1) > MAX_VERTICES) {	
		printf("그래프 정점 개수 초과\n");	
		return;	
	}	
	g->n++;	
}	

// v를 u의 인접 리스트에 삽입	
void insert_edge(GraphType* g, int u, int v) {	
	GraphNode* node;	

	if (u >= g->n || v >= g->n) { 	
		printf("그래프 정점 번호 오류\n");	
		return;	
	}	

	node = (GraphNode*)malloc(sizeof(GraphNode));	

	node->vertex = v;	
	node->link = g->adj_list[u];	
	g->adj_list[u] = node;	
}	

void dfs(GraphType* g, int v) {	
	GraphNode* w;	
	visited[v] = 1;	

	printf("%d ", v + 1);	

	for (w = g->adj_list[v]; w; w = w->link)	
		if (!visited[w->vertex])	
			dfs(g, w->vertex);	
}	

void bfs(GraphType* g, int v) {	
	GraphNode* w;	
	QueueType q;	

	queue_init(&q);	
	visited[v] = 1;	
	printf("%d ", v + 1);	
	enqueue(&q, v);	
	while (!is_empty(&q)) {	
		v = dequeue(&q);	

		for (w = g->adj_list[v]; w; w = w->link) {	
			if (!visited[w->vertex]) {	
				visited[w->vertex] = 1;	
				printf("%d ", w->vertex + 1);	
				enqueue(&q, w->vertex);	
			}	
		}	
	}	

}	

void queue_init(QueueType* q) {	
	q->front = NULL;	
	q->rear = NULL;	
}	

int is_empty(QueueType* q) {	
	return (q->front == NULL);	
}	

void enqueue(QueueType* q, int item) {	
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));	

	if (temp == NULL) {	
		printf("메모리 할당 불가\n");	
		return;	
	}	

	temp->item = item;	
	temp->link = NULL;	

	if (is_empty(q)) {	
		q->front = temp;	
		q->rear = temp;	
	}	
	else {	
		q->rear->link = temp;	
		q->rear = temp;	
	}	
}	

int dequeue(QueueType* q) {	
	QueueNode* temp = q->front;	
	int item;	

	if (is_empty(q)) {	
		printf("큐가 공백 입니다.\n");	
		exit(1);	
	}	

	item = temp->item;	
	q->front = q->front->link;	

	if (q->front == NULL)	
		q->rear = NULL;	

	free(temp);	

	return item;	
}