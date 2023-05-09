#pragma once 

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    void** items;
    int arr_size;
    int front;
    int rear;
    int size;
}Queue;

Queue* new_queue();

void enqueue(void* element,Queue* q);

void* dequeue(Queue* q);