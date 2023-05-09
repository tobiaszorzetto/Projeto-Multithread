#pragma once
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define GROUP_SIZE 4

#define TRUE 1
#define FALSE 0

#define SERF 1
#define HACKER 0 

#define WAITING 0
#define LOOKING 1
#define FOUND_GROUP 2
#define NOT_FOUND_GROUP 3
#define BOARDING 4
#define ROWING 5


extern pthread_barrier_t barrier;
extern sem_t state_mutex;
extern sem_t queues[2];


void sem_post_n(sem_t* sem, int n);

void init_structs();

void destroy_structs();


