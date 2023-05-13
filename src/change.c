#include "change.h"

Queue_change* new_queue_change( Queue* q, int diff, void* diff_elem){
    Queue_change* q_c = (Queue_change*) malloc(sizeof(Queue_change*));
    q_c->queue = q;
    q_c->diff = diff;
    q_c->diff_elem = diff_elem;

    return q_c;
}

void enqueue_publisher_wrapper( Queue* q,Publisher* pub,void* obj){
    enqueue(obj,q);
    Queue_change* q_c = new_queue_change(q,1, obj);
    publish(pub, q_c);
}

void* dequeue_publisher_wrapper( Queue* q,Publisher* pub){
    void* obj = dequeue(q);
    Queue_change* q_c = new_queue_change(q,-1, obj);
    publish(pub, q_c);
    return obj;
}