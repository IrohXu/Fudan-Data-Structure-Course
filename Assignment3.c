#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#include<limits.h> //for INT_MIN

struct Interval;
typedef struct Interval *PtrToNode;
typedef PtrToNode list;
typedef PtrToNode position;

struct Interval
{
	int left;
	int right;
	position next;
};

int IsEmpty(list I) {
	return I->next == NULL;
}

void MakeEmpty(list L) {
	position temp;
	while (!IsEmpty(L)) {
		temp = L->next;
		L->next = L->next->next;
		free(temp);
	}
}

list CreteList(void) {
	list L;
	position P;
	position temp;
	L = malloc(sizeof(struct Interval));
	L->next = NULL;
	MakeEmpty(L);
	P = L;
	temp = malloc(sizeof(struct Interval));
	temp->left = -99999;
	temp->right = -99998;
	temp->next = P->next;
	P->next = temp;
	return L;
}

void Add(int x, int y, list *L)
{
	position P;
	position temp;
	P = (*L)->next;
	if (P->next==NULL) {
		temp = malloc(sizeof(struct Interval));
		temp->left = x;
		temp->right = y;
		temp->next = P->next;
		P->next = temp;
		return L;
	}
	P = (*L)->next;
	while (P != NULL)
	{
		if (P->next == NULL) {
			if (x == P->right) {
				P->left = y;
				break;
			}
			else if (x > P->right) {
				temp = malloc(sizeof(struct Interval));
				temp->left = x;
				temp->right = y;
				temp->next = P->next;
				P->next = temp;
				break;
			}
		}
		if (x > P->right && x < P->next->right) {
			if (y < P->next->left) {		
				temp = malloc(sizeof(struct Interval));
				temp->left = x;
				temp->right = y;
				temp->next = P->next;
				P->next = temp;
				break;
			}
			else if (y > P->next->left) {
				if (y <= P->next->right) {
					P->next->left = min(x, P->next->left);
				}
				else {
					x = min(x, P->next->left);
					temp = P->next;
					P->next = P->next->next;
					free(temp);
					continue;
				}
			}
			else if (P->next->left == y) {
				P->next->right = x;
				break;
			}
		}
		else if(x == P->right && x < P->next->right){
			if (y < P->next->left || P->next == NULL) {
				P->right = y;
				break;
			}
			else if (y >= P->next->left && y <= P->next->right) {
				P->right = P->next->right;
				temp = P->next;
				P->next = P->next->next;
				free(temp);
				break;
			}
			else {
				temp = P->next;
				P->next = P->next->next;
				free(temp);
				continue;
			}
		}
		P = P->next;
	}
	return L;
}

int Delete(list *L)
{
	position P;
	position temp;
	P = (*L)->next;
	while (P != NULL) {
		if (P->next->right > P->next->left) {
			P->next->left += 1;
			return P->next->left - 1;
		}
		else if (P->next->right == P->next->left) {
			temp = P->next;
			P->next = P->next->next;
			free(temp);
			continue;
		}
	}
	return 0;
}

int main() {
	int num_instructions;
	scanf("%d", &num_instructions);
	list L;
	L = CreteList();

	char buf[50];
	while (num_instructions--) {
		scanf("%s", buf);
		if (buf[0] == '+') {
			int left, right;
			sscanf(buf, "+%d,%d", &left, &right);
			Add(left, right, &L);
		}
		else if (buf[0] == '-') {
			int next;
			next = Delete(&L);
			printf("%d\n", next);
		}
		/* printf("     %d      %d\n", L->next->next->left, L->next->next->right); */
	}
	getchar();
	getchar();
	return 0;
}