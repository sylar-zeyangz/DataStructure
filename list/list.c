/*
	Author: Sylar Z
	Sinlgy linked list in C
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	struct Node* next;
	int val;
}Node;

static int node_num = 0;

// Push to the head
void push_head(Node** _n, int _x) {
	Node* new_n = (Node*)malloc(sizeof(Node));
	new_n->next = *_n;
	new_n->val = _x;
	*_n = new_n;
	node_num++;
}

// Push to non-head location
void push(Node* _n, int _x) {
	Node* new_n = (Node*)malloc(sizeof(Node));
	new_n->next = NULL;
	new_n->val = _x;	

	Node* curr = _n;
	while(curr->next != NULL)
		curr = curr->next;
	curr->next = new_n;

	node_num++;
}

// Use pointer to the pointer's head so that we could change the head if needed
void delNode(Node** _n, int _x) {
	Node* prev = NULL;
	for (Node* curr = *_n; curr != NULL; prev = curr, curr = curr->next) {
		if (curr->val == _x) {
			if (prev == NULL) {
				printf("Deleting the first node\n");
				*_n = curr->next;
			}
			else
				prev->next = curr->next;
			free(curr);
			--node_num;
			return;
		}
	}
	printf("Couldn't find NODE %d to delete.\n", _x);
}

#define NUM 6
#define GAP 10

int missingVal(Node* _n) {
	Node* curr = _n;
	while(curr->next) {
		if (curr->val + GAP != curr->next->val)
			return curr->val + GAP; 		
		curr = curr->next;
	}
	return -1;
}

void reverse(Node** _n) {
	Node* prev = NULL;
	Node* next = NULL;
	Node* curr = *_n;
	while(curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;

		curr = next;
	}
	*_n = prev;
}

void printList(Node* _n) {
	Node* dummy = _n;
	while(dummy) {
		printf("%d ", dummy->val);
		dummy = dummy->next;
	}
	printf("\n");
}

int main(int argc, char** argv) {
	//static int call_time = 0;
	Node* head = (Node*)malloc(sizeof(Node));
	// -10 -> 0 -> 10 -> 20 -> 30 -> 40 -> 50 -> 60	
	for (int i = 1; i <= NUM; ++i)
		push(head, 10*i);
	push_head(&head, -10);
	delNode(&head, 60);
	delNode(&head, -10);
	delNode(&head, 20);
	delNode(&head, 100);	
	printList(head);
	printf("Missing value = %d\n", missingVal(head));
	printf("total nodes = %d\n", node_num+1);
	
	reverse(&head);
	printList(head);
	return 0;
}

