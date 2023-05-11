#pragma once
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct{
    int type;
    sem_t system_permission;
    sem_t r_system_permission;
    pthread_barrier_t* group_barrier;
}Person;

Person* new_person();

void delete_person(Person* p);

