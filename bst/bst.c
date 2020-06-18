/*
	Author: Sylar Z
	Binary search tree
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX 64

typedef struct node{
	struct node* left;
	struct node* right;
	int val;	
}Node;

void insert(Node** root, int _x) {
	if(!*root) {
		*root = (Node*)malloc(sizeof(Node));
		(*root)->val = _x;
	}
	else {
		if (_x > (*root)->val) {
			insert(&((*root)->right), _x);
		}
		else {
			insert(&((*root)->left), _x);
		}
	}
}

Node* minNode(Node* root) {
	Node* curr = root;
	while(curr && curr->left)
		curr = curr->left;
	return curr;
}

Node* maxNode(Node* root) {
	Node* curr = root;
	while(curr && curr->right) 
		curr = curr->right;
	return curr;
}

Node* find(Node* root, int _x) {
	if(root == NULL) return root;
	Node* target = NULL;
	if(_x > root->val) {
		if (root->right)
			target = find(root->right, _x);
		else {
			printf("Couldn't find %d.\n", _x);
			return NULL; 
		}
	}
	else if (_x < root->val) {
		if (root->left)
			target = find(root->left, _x);
		else {
			printf("Couldn't find %d.\n", _x);
		}
	}
	else
		target = root;
	return target;
}

Node* nextLarger(Node* root, int _x) {
	if(root == NULL) return root;
	Node* x_node = find(root, _x);
	if (x_node == NULL) 
		return x_node;
	if(x_node->right)
		return minNode(x_node->right);
	// Empty right subtree, so start from the root
	Node* tmp = root;
	Node* ret = NULL;
	while(tmp) {
		if (_x < tmp->val) {
			ret = tmp;
			tmp = tmp->left;
		}
		else if (_x > tmp->val) {
			tmp = tmp->right;
		}
		else
			break;
	}
	return ret;
}

// DFS
void preOrder(Node* root) {
	if(!root) return;
	printf("%d ", root->val);
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(Node* root) {
	if(!root) return;
	inOrder(root->left);
	printf("%d ", root->val);
	inOrder(root->right);
}

void postOrder(Node* root) {
	if(!root) return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->val);
}

void flatten(Node* root) {
	if(!root || root->left == NULL && root->right == NULL)
		return;
	if(root->left != NULL) {
		flatten(root->left);
		Node* tmpRight = root->right;
		root->right = root->left;
		root->left = NULL;

		// Found the position to attached original right (tmpRight)
		Node* t = root->right;
		while(t->right != NULL) {
			t = t->right;
		}
		t->right = tmpRight;
	} 
	flatten(root->right);
}

// Queue defines for BFS
Node* queue[MAX];
int front = -1, rear = -1;
void enqueue(Node* n) {
	if(rear == MAX - 1) {
		printf("Queue overflow!\n");
		return;
	}
	else {
		if(front == -1)
			front = 0;
		++rear;
		queue[rear] = n;
	}
}

Node* dequeue() {
	if(front == -1 || front > rear) {
		printf("Empty queue!\n");
		exit(-1);
	}	
	return queue[front++];
}

int isEmptyQ() {
	if(front == -1 || front > rear)
		return 1;
	else
		return 0;
}

// BFS
void bfs(Node* root) {
	Node* temp = root;
	while(temp != NULL) {
		printf("%d ", temp->val);
		enqueue(temp->left);
		enqueue(temp->right);
		temp = dequeue();
	} 
}

int main(int argc, char** argv) {
	Node* root = NULL;
	insert(&root, 50);
	insert(&root, 30);
	insert(&root, 70);
	insert(&root, 40);
	insert(&root, 60);
	insert(&root, 20);
	/*	
				   50
			   / 		\
			 30    		 70
			/  \	    / 
		  20  	40	  60
	
	*/
	// preOrder: 50, 30, 20, 40, 70, 60
	preOrder(root);
	printf("\n");
	// inOrder: 20, 30, 40, 50, 60, 70
	inOrder(root);
	printf("\n");
	// postOrder: 20, 40, 30, 60, 70, 50
	postOrder(root);
	printf("\n");
	// bfs: 50, 30, 70, 20, 40, 60
	bfs(root);
	printf("\n");
	// printf("find %d: %d\n", 40, find(root, 40));
	printf("The next largest of %d is %d.\n", 40, nextLarger(root, 40)->val);
	// flatten to a list 
	flatten(root);
	Node* curr = root;
	while(curr != NULL) {
		printf("%d ", curr->val);
		curr = curr->right;
	}
	printf("\n");
	return 0;
}

