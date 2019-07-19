#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define MAXSIZE 10000

typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */

typedef struct {
	int key;
	int value;
}counter;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex num;        /* 邻接点下标 */ 
	PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};

typedef struct Vnode {
	PtrToAdjVNode FirstEdge;     /* 边表头指针 */
} AdjList[MAXSIZE];    /* AdjList是邻接表类型 */

typedef struct GNode *PtrToGNode;
struct GNode {
	int V;      /* 顶点数 */
	int E;      /* 边数   */
	AdjList G;   /* 邻接表 */
};
typedef PtrToGNode LGraph;    /* 以邻接表方式存储的图类型 */

int cmp(const void *a, const void *b)
{
	return (*(counter *)b).value - (*(counter *)a).value;
}

void InitGraph(LGraph graph) {
	graph->V = 0;
	graph->E = 0;
	for (int i = 0; i < MAXSIZE; i++) {		
		graph->G[i].FirstEdge = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
		graph->G[i].FirstEdge->Next = NULL;
	}
}

void Insert(PtrToAdjVNode L, int n) {
	PtrToAdjVNode temp;
	temp = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	temp->num = n;
	temp->Next = L->Next;
	L->Next = temp;
}

void Delete(PtrToAdjVNode L, int n) {
	PtrToAdjVNode temp, P;
	P = L;
	while (P->Next != NULL) {
		if (P->Next->num == n) {
			temp = P->Next;
			P->Next = temp->Next;
			free(temp);
			break;
		}
		P = P->Next;
	}
}

int factorial(int n) {
	if (n <= 1)
		return 1;
	else
		return (n * factorial(n - 1));
}

int check(PtrToAdjVNode L, int n) {
	PtrToAdjVNode P;
	P = L->Next;
	while (P != NULL) {
		if (P->num == n) {
			return 1;
		}
		P = P->Next;
	}
	return 0;
}

int main(void)
{
	counter count[MAXSIZE];
	int n, a, b, ret, triangle1, triangle2, factorial1, factorial2, i;
	triangle1 = 0;
	triangle2 = 0;
	for (i = 0; i < MAXSIZE; i++) {
		count[i].key = i;
		count[i].value = 0;
	}
	scanf("%d", &n);
	LGraph graph;
	graph = (PtrToGNode)malloc(sizeof(struct GNode));
	InitGraph(graph);
	while (1)
	{
		ret = scanf("%d", &a);
		scanf("%d", &b);
		if (ret != 1) break;
		if (check(graph->G[a].FirstEdge, b) == 0) {
			Insert(graph->G[a].FirstEdge, b);
			Insert(graph->G[b].FirstEdge, a);
			count[a].value++;
			count[b].value++;
		}
	}
	for (i = 1; i <= n; i++) {
		if (count[i].value < 2) {
			triangle2 += 0;
		}
		else if (count[i].value >= 2) {
			triangle2 += count[i].value * (count[i].value-1) /2;
		}
	}
	qsort(count, n, sizeof(counter), cmp);
	for (i = 0; i < n; i++) {
		PtrToAdjVNode L1;
		L1 = graph->G[count[i].key].FirstEdge->Next;
		while (L1 != NULL) {
			Delete(graph->G[L1->num].FirstEdge, count[i].key);
			PtrToAdjVNode L2;
			L2 = graph->G[L1->num].FirstEdge->Next;
			while (L2 != NULL) {
				if (check(graph->G[L2->num].FirstEdge, count[i].key) == 1) {
					triangle1++;
				}
				L2 = L2->Next;
			}
			L1 = L1->Next;
		}
	}

	triangle2 -= 3*triangle1;
	printf("gID:1 freq:%d\n", triangle1);
	printf("gID:2 freq:%d", triangle2);
	getchar();
	getchar();
	return 0;
}