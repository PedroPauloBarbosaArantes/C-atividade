#include "queue.h"

Queue* createQueue(int size) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(size * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->size = size;
    q->count = 0;
    pthread_mutex_init(&q->mutex, NULL);
    return q;
}

int isFull(Queue *q) {
    return (q->count == q->size);
}

int isEmpty(Queue *q) {
    return (q->count == 0);
}

void enqueue(Queue *q, int value) {
    pthread_mutex_lock(&q->mutex);
    if (!isFull(q)) {
        q->rear = (q->rear + 1) % q->size;
        q->data[q->rear] = value;
        q->count++;
    }
    pthread_mutex_unlock(&q->mutex);
}

int dequeue(Queue *q) {
    pthread_mutex_lock(&q->mutex);
    int value = -1;
    if (!isEmpty(q)) {
        value = q->data[q->front];
        q->front = (q->front + 1) % q->size;
        q->count--;
    }
    pthread_mutex_unlock(&q->mutex);
    return value;
}

void freeQueue(Queue *q) {
    pthread_mutex_destroy(&q->mutex);
    free(q->data);
    free(q);
}

void printQueue(Queue *q) {
    pthread_mutex_lock(&q->mutex);
    printf("Queue (size: %d, count: %d): ", q->size, q->count);
    if (!isEmpty(q)) {
        int i = q->front;
        do {
            printf("%d ", q->data[i]);
            i = (i + 1) % q->size;
        } while (i != (q->rear + 1) % q->size);
    }
    printf("\n");
    pthread_mutex_unlock(&q->mutex);
} 