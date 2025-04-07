#include "queue.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_QUEUES 10
#define QUEUE_SIZE 100
#define LARGE_QUEUE_MULTIPLIER 5
#define MAX_RANDOM_DELAY 91  // 100ms - 10ms + 1
#define MIN_RANDOM_DELAY 10
#define RUN_TIME 300  // 5 minutes in seconds

Queue *queues[NUM_QUEUES];
int elements_removed[NUM_QUEUES] = {0};
int running = 1;

void* producer_thread(void* arg) {
    while (running) {
        int value = rand() % 1000 + 1;  // Random value between 1 and 1000
        int queue_index = rand() % NUM_QUEUES;
        
        if (!isFull(queues[queue_index])) {
            enqueue(queues[queue_index], value);
        }
        
        usleep((rand() % MAX_RANDOM_DELAY + MIN_RANDOM_DELAY) * 1000);
    }
    return NULL;
}

void* consumer_thread(void* arg) {
    int queue_index = *((int*)arg);
    while (running) {
        if (!isEmpty(queues[queue_index])) {
            int value = dequeue(queues[queue_index]);
            if (value != -1) {
                elements_removed[queue_index]++;
            }
        }
        usleep(10000);  // 10ms delay
    }
    return NULL;
}

void print_status() {
	int i;
	
    printf("\nQueue Status:\n");
    for (i = 0; i < NUM_QUEUES; i++) {
        printf("Queue %d: Size=%d, Elements removed=%d\n", 
               i, queues[i]->count, elements_removed[i]);
    }
}

void user_interface() {
    int choice, queue_num, value;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Enqueue element\n");
        printf("2. Check queue status\n");
        printf("3. Dequeue element\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter queue number (0-9): ");
                scanf("%d", &queue_num);
                if (queue_num < 0 || queue_num >= NUM_QUEUES) {
                    printf("Invalid queue number!\n");
                    break;
                }
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(queues[queue_num], value);
                break;
                
            case 2:
                printf("Enter queue number (0-9): ");
                scanf("%d", &queue_num);
                if (queue_num < 0 || queue_num >= NUM_QUEUES) {
                    printf("Invalid queue number!\n");
                    break;
                }
                printQueue(queues[queue_num]);
                break;
                
            case 3:
                printf("Enter queue number (0-9): ");
                scanf("%d", &queue_num);
                if (queue_num < 0 || queue_num >= NUM_QUEUES) {
                    printf("Invalid queue number!\n");
                    break;
                }
                value = dequeue(queues[queue_num]);
                if (value != -1) {
                    printf("Dequeued value: %d\n", value);
                    elements_removed[queue_num]++;
                } else {
                    printf("Queue is empty!\n");
                }
                break;
                
            case 4:
                running = 0;
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
	int i;
    srand(time(NULL));
    
    // Create queues
    for (i = 0; i < NUM_QUEUES - 1; i++) {
        queues[i] = createQueue(QUEUE_SIZE);
    }
    queues[NUM_QUEUES - 1] = createQueue(QUEUE_SIZE * LARGE_QUEUE_MULTIPLIER);
    
    // Create producer thread
    pthread_t producer;
    pthread_create(&producer, NULL, producer_thread, NULL);
    
    // Create consumer threads
    pthread_t consumers[NUM_QUEUES];
    int consumer_args[NUM_QUEUES];
    for (i = 0; i < NUM_QUEUES; i++) {
        consumer_args[i] = i;
        pthread_create(&consumers[i], NULL, consumer_thread, &consumer_args[i]);
    }
    
    // Start user interface
    user_interface();
    
    // Wait for threads to finish
    pthread_join(producer, NULL);
    for (i = 0; i < NUM_QUEUES; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    // Print final status
    print_status();
    
    // Free queues
    for (i = 0; i < NUM_QUEUES; i++) {
        freeQueue(queues[i]);
    }
    
    return 0;
} 
