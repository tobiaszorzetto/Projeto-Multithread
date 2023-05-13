#pragma once
#include "queue.h"
#include "publisher.h"
typedef struct{
    Queue* queue;
    void* diff_elem;
    int diff;
}Queue_change;

Queue_change* new_queue_change( Queue* q, int diff, void* diff_elems);

void enqueue_publisher_wrapper( Queue* q,Publisher* pub,void* obj);

void* dequeue_publisher_wrapper( Queue* q,Publisher* pub);