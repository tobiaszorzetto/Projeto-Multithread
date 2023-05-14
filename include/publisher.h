#pragma once
#include <stdlib.h>

#define MAX_NUM_SUBSCRIBERS 20

typedef struct {
    int free_index;
    void(*subscribers [MAX_NUM_SUBSCRIBERS])(void*);
}Publisher;

Publisher* new_publisher();

// Adds a given function to the list of subscribers of the publisher
void subscribe(Publisher* pub, void(*function)(void*));

// Executes, in subscription order, the functions that subscribed to 
// the give publisher, passing as arguments the pointer arg
void publish(Publisher* pub, void* arg);