#pragma once
#include <stdlib.h>

#define MAX_NUM_SUBSCRIBERS 20

typedef struct {
    int free_index;
    void(*subscribers [MAX_NUM_SUBSCRIBERS])(void*);
}Publisher;

Publisher* new_publisher();

void subscribe(Publisher* pub, void(*function)(void*));

void publish(Publisher* pub, void* arg);