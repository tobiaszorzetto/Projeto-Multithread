#pragma once
#include "person.h"
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct{
    Person**participants;
    int size;
    int i;
    sem_t system_permission;
    pthread_barrier_t barrier;
}Group;

Group* new_group(int size);

//simple function to free the memory allocated for a given group
void delete_group(Group* g);