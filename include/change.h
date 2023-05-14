#pragma once
#include "queue.h"
#include "publisher.h"
typedef struct{
    Queue* queue;
    void* diff_elem;
    int diff;
}Queue_change;

Queue_change* new_queue_change( Queue* q, int diff, void* diff_elems);

// Wrapper functions that executes enqueue and dequeue and notify a publisher 
// with, respectively, diff equal to +1 and -1 and diff_elem equal to the 
//affected element
void enqueue_publisher_wrapper( Queue* q,Publisher* pub,void* obj);

void* dequeue_publisher_wrapper( Queue* q,Publisher* pub);