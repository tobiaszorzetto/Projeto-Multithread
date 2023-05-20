#pragma once
#include "person.h"
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct{
    Person**participants;
    int size;
    int i;
    int id;
    sem_t system_permission;
    pthread_barrier_t barrier;
}Group;
extern int last_id;

Group* new_group(int size);

//simple function to free the memory allocated for a given group
void delete_group(Group* g);