#include<stdio.h>
#include<stdlib.h>
#include<math.h> 
#pragma warning(disable:4996)
		
void reversal(int a[], int h, int k) {
	int i, j, temp;
	for (i = h, j = k; j - i >= 0; i++, j--) {
		if (i != j) {
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
}

int findleftmax(int a[], int right) {
	int i, j;
	j = -1;
	for (i = right - 1; i >= 0; i--) {
		if (a[i] < a[i + 1]) {
			j = i;
			return j;
		}
	}
	return j;
}

int findrightmax(int a[], int right, int j) {
	int i, tempmax = a[j + 1], max = tempmax;
	int num = j + 1;
	for (i = j; i < right; i++) {
		if (a[j] < a[i + 1]) {
			tempmax = a[i + 1];
			if (tempmax < max) {
				max = tempmax;
				num = i + 1;
			}
		}
	}
	return num;
}

int main() {
	int n, i, j, k, temp;
	int a[10];
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		a[i] = i + 1;
	}

	while (findleftmax(a, n - 1) != -1) {
		for (i = 0; i < n; i++) {
			printf("%d ", a[i]);
		}
		printf("\n");
		j = findleftmax(a, n - 1);
		k = findrightmax(a, n - 1, j);
		temp = a[j];
		a[j] = a[k];
		a[k] = temp;
		reversal(a, j + 1, n - 1);
	}
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}

	getchar();
	getchar();
	return 0;
}