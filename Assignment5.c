#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct TreeNode;
typedef struct TreeNode *tree;

struct TreeNode
{
	tree left;
	tree right;
};

int power(int x, int k) {
	int i, y = 1;
	for (i = 0; i < k; i++)
		y *= x;
	return y;
}

int *transfer(int num, int nodenum) {
	int i, tempnodenum;
	int *a = (int *)malloc(sizeof(int) * nodenum);
	tempnodenum = findnodenum(num);
	for (i = nodenum - 1; i >= 0; i--) {		
		if (num != 0) {
			a[i] = num % 2;
			num /= 2;
		}
		else
			a[i] = 0;
	}
	return a;
}

int findarraymax(int n, int *array) {
	int i;
	int tempmax = 0;
	for (i = 0; i < n; i++) {
		if (array[i] > tempmax) {
			tempmax = array[i];
		}
	}
	return tempmax;
}

int findnodenum(int total) {
	int nodenum = 0;
	int i;
	for (i = total; i > 0; i /= 2) {
		nodenum++;
	}
	return nodenum;
}

void buildtree(tree T, int a[], int nodenum) {
	int i;
	for (i = 0; i < nodenum; i++) {
		if (a[i] == 0) {
			if (T->left == NULL) {
				T->left = malloc(sizeof(struct TreeNode));
				T = T->left;
				T->left = NULL;
				T->right = NULL;
			}
			else {
				T = T->left;
			}
		}
		else{
			if (T->right == NULL) {
				T->right = malloc(sizeof(struct TreeNode));
				T = T->right;
				T->left = NULL;
				T->right = NULL;
			}
			else {
				T = T->right;
			}
		}
	}
}

int check(tree T1, tree T2, int a[], int nodenum) {
	int i, x = 0, y = nodenum;
	for (i = 0; i < nodenum; i++) {
		y--;
		if (a[i] == 0) {
			T1 = T1->left;
			if (T2->right != NULL) {
				x += power(2, y);
				T2 = T2->right;
			}
			else
				T2 = T2->left;
		}
		else {
			T1 = T1->right;
			if (T2->left != NULL) {
				x += power(2, y);
				T2 = T2->left;
			}
			else
				T2 = T2->right;
		}
	}
	return x;
}

int max_xor(int n, int *array);

int max_xor(int n, int *array) {
	int i, maxarray, nodenum, finalmax = 0, temp;
	tree T;
	T = malloc(sizeof(struct TreeNode));
	T->left = NULL;
	T->right = NULL;
	maxarray = findarraymax(n, array);
	nodenum = findnodenum(maxarray);
	for (i = 0; i < n; i++) {
		buildtree(T, transfer(array[i], nodenum), nodenum);
	}
	for (i = 0; i < n; i++) {
		temp = check(T, T, transfer(array[i], nodenum), nodenum);
		if (temp > finalmax)
			finalmax = temp;
	}
	return finalmax;
}

int main() {
	int n;
	scanf("%d", &n);

	int *array = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", array + i);
	}

	int answer = max_xor(n, array);

	printf("%d\n", answer);
	getchar();
	getchar();
	return 0;
}
