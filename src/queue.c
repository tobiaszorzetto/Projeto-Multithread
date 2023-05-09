#include "queue.h"

Queue* new_queue(int max_size){
    Queue* new_q = (Queue*) malloc(sizeof(Queue));
    new_q->items =(void**) malloc(sizeof(void*)*max_size);
    new_q->arr_size = max_size;
    new_q->front =0;
    new_q->rear = -1;
    new_q->size = 0;
    return new_q;
}

void enqueue(void* element, Queue* q){
    q->rear=(q->rear+1)%q->arr_size;
    q->items[q->rear] = element;
    q->size++;
    
    if(q->size>q->arr_size){
        perror("queue size overflowed");
        exit(EXIT_FAILURE);
    }

}

void* dequeue(Queue* q){
    void* temp = q->items[q->front];
    q->front=(q->front+1)%q->arr_size;
    q->size--;
    return temp;
}