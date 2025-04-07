#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int count;
    pthread_mutex_t mutex;
} Queue;

// Function prototypes
Queue* createQueue(int size);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
void freeQueue(Queue *q);
void printQueue(Queue *q);

#endif 