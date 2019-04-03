#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode stack;
typedef PtrToNode position;

struct Node
{
	int element;
	int location;
	position next;
};

int IsEmpty(stack S);
void MakeEmpty(stack S);
stack CreteStack(void);
void pop(stack S);
int Top_element(stack S);
int Top_location(stack S);
void push(int x, int y, stack S);

int IsEmpty(stack S) {
	return S->next == NULL;
}

void push(int x,int y, stack S) {
	position temp;
	temp = malloc(sizeof(struct Node));
	temp->element = x;
	temp->location = y;
	temp->next = S->next;
	S->next = temp;
}

void pop(stack S) {
	position first;
	first = S->next;
	S->next = S->next->next;
	free(first);
}

int Top_element(stack S) {
	if (!IsEmpty(S))
		return S->next->element;
	return 0;
}

int Top_location(stack S) {
	if (!IsEmpty(S))
		return S->next->location;
	return 0;
}

void MakeEmpty(stack S) {
	while (!IsEmpty(S))
		pop(S);
}

stack CreteStack(void) {
	stack s;
	s = malloc(sizeof(struct Node));
	s->next = NULL;
	MakeEmpty(s);
	return s;
}

int MaxSquareSum(int a[], int n)
{
	stack S;
	S = CreteStack();
	push(a[0], 0, S);
	int i, length, width = 1, temptwidth;   /*定义临时宽度*/
	int maxsquare = 1 * a[0];  /*定义最大面积*/
	for (i = 1; i < n; i++) {
		if (a[i] >= a[i - 1] && i!=n-1) {
			push(a[i], i, S);
		}
		else
		{
			if (i == n-1) {
				if (a[i] >= a[i - 1]) {
					push(a[i], i, S);
					while (!IsEmpty(S)) {
						length = Top_element(S);
						width = i - Top_location(S) + 1;
						if (length*width >= maxsquare)
							maxsquare = length * width;
						pop(S);
					}
				}
				else {
					while (!IsEmpty(S) && a[i] < Top_element(S)) {
						length = Top_element(S);
						width = i - Top_location(S);
						if (length*width >= maxsquare)
							maxsquare = length * width;
						temptwidth = Top_location(S);
						pop(S);
					}
					push(a[i], temptwidth, S);
					while (!IsEmpty(S)) {
						length = Top_element(S);
						width = i - Top_location(S) + 1;
						if (length*width >= maxsquare)
							maxsquare = length * width;
						pop(S);
					}
				}
			}
			else {
				while (!IsEmpty(S) && a[i] < Top_element(S)) {
					length = Top_element(S);
					width = i - Top_location(S);
					if (length*width >= maxsquare)
						maxsquare = length * width;
					temptwidth = Top_location(S);
					pop(S);
				}
				push(a[i], temptwidth, S);
			}
		}
	}
	return maxsquare;
}


int main(void)
{
	int n, i;
	int maxsum;
	scanf_s("%d", &n);
	int a[1000];
	for (i = 0; i < n; i++) {
		scanf_s("%d", &a[i]);
	}
	maxsum = MaxSquareSum(a, n);

	printf("%d", maxsum);
	getchar();
	getchar();

	return 0;
}