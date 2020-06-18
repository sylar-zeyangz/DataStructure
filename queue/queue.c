/*
	Arthor: Sylar Z
	Queue
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct queue{
	unsigned capacity;
	int front, rear, size;
	int* array;
}queue;

queue* createQueue(int _cap){
	queue* q = (queue*)malloc(sizeof(queue));
	q->capacity = _cap;
	q->array = (int*)malloc(sizeof(int)*_cap);
	q->front = q->size = 0;
	q->rear = q->capacity - 1;
	return q;
}

bool isFull(queue* _q) {
	return _q->size == _q->capacity;
}

bool isEmpty(queue* _q) {
	return _q->size == 0;
}

void enQueue(queue* _q, int _x) {
	if( !isFull(_q) ) {
		_q->rear = (_q->rear + 1) % _q->capacity;
		_q->array[_q->rear] = _x;
		++_q->size;
	}	
	else {
		printf("Queue is full, %d enQueue failed!\n", _x);
		return;
	}	
}

int deQueue(queue* _q) {
	if( !isEmpty(_q) ) {
		int ret = _q->array[_q->front];
		_q->front = (_q->front + 1) % _q->capacity;
		--_q->size;
		return ret;
	}
	else {
		printf("Queue is empty!\n");
		return -1;
	}
}

int front(queue* _q) {
	if(!isEmpty(_q))
		return _q->array[_q->front];
	else
		return -1;
}

int rear(queue* _q) {
	if(!isEmpty(_q))
		return _q->array[_q->rear];
	else
		return -1;
}

int main(int argc, char** argv) {
	queue* q = createQueue(3);
	enQueue(q, 10);
	enQueue(q, 20);
	enQueue(q, 30);
	deQueue(q);
	deQueue(q);
	deQueue(q);
	enQueue(q, 100);
	enQueue(q, 200);
	enQueue(q, 300);
	deQueue(q);
	deQueue(q);
	deQueue(q);
	enQueue(q, 400);
	printf("front = %d, rear = %d\n", front(q), rear(q));
	return 0;
}



