#include<stdio.h>
#include<stdlib.h>

struct LinkedList {
	int value;
	struct LinkedList *next;
};

typedef struct LinkedList LinkedList;
LinkedList *reverse(LinkedList *head);

int main() {
	/* read the input and create the list */
	int n, i;
	scanf_s("%d", &n);
	LinkedList *head = (LinkedList *)malloc(sizeof(LinkedList));
	LinkedList *cur, *p;
	cur = head;

	i = n;
	while (i--) {
		cur->next = (LinkedList *)malloc(sizeof(LinkedList));
		cur = cur->next;
		scanf_s("%d", &(cur->value));
		cur->next = NULL;
	}

	/* delete the placeholder at head */
	cur = head;
	head = head->next;
	free(cur);

	/* reverse the list */
	head = reverse(head);

	/* print the result */
	for (cur = head; cur != NULL; cur = cur->next) {
		printf("%d ", cur->value);
	}
	printf("\n");

	/* free the list nodes */
	for (cur = head; cur != NULL; free(p)) {
		p = cur;
		cur = cur->next;
	}
	head = NULL;

	getchar();
	getchar();

	return 0;
}





LinkedList *reverse(LinkedList *head) {
	LinkedList *L, *cur ,*temp;
	L = (LinkedList *)malloc(sizeof(LinkedList));
	cur = head;
	L->next = NULL;

	while (cur) {
		temp = (LinkedList *)malloc(sizeof(LinkedList));
		temp->value = cur->value;
		temp->next = L->next;
		L->next = temp;
		cur = cur->next;
	}

	L = L->next;
	return L;
}