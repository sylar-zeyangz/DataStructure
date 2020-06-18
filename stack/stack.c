/*
	Author: Sylar Z
	Stack in C/C++
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct stack{
	int top;
	unsigned capacity;
	int* array;
}stack;

stack* createStack(int _cap) {
	stack* s = (stack*)malloc(sizeof(stack));
	s->capacity = _cap;
	s->array = (int*)malloc(sizeof(int)*_cap);
	s->top = -1;
	return s; 
}

bool isEmpty(stack* _s) {
	return _s->top == -1;
}

bool isFull(stack* _s) {
	return _s->top == _s->capacity - 1;
}

void push(stack* _s, int _x) {
	if(!isFull(_s)) {
		_s->array[++_s->top] = _x;
		printf("%d pushed to stack.\n", _x);
	}
	else
		// Full stack
		return;
}

int pop(stack* _s) {
	if(!isEmpty(_s))
		return _s->array[_s->top--];
	else
		// Empty stack
		return -1;
}

int top(stack* _s) {
	if(!isEmpty(_s))
		return _s->array[_s->top];
	else
		// Empty stack
		return -1;
}

int main(int argc, char** argv) {
	stack* sa = createStack(5);
	// printf("Stack size = %d, Stack pointer size = %d\n", sizeof(*sa), sizeof(sa));
	printf("%d\n", sa->top);
	push(sa, 10);
	push(sa, 30);
	push(sa, 50);
	printf("top=%d\n",top(sa));
	int x = pop(sa);
	printf("pop=%d, top=%d", x, top(sa));
	return 0;
}

