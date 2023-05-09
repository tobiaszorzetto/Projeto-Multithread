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