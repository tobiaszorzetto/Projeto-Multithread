#pragma once
#include <stdlib.h>
#include "queue.h"
#include <semaphore.h>
#include <stdarg.h>

typedef struct{
    int group_size;
    int num_groups;
    int* group_proportions;

    sem_t join_waiting_queue_sem;
    sem_t waiting_queue_sem;
    Queue* waiting_queue;// queue of Person

    sem_t* individuals_queue_sems;
    Queue** individuals_queue;// queue of Person

    sem_t groups_queue_sem;
    Queue* groups_queue;// queue of Group

    Queue* change_queue;// queue of Change
    sem_t main_sem;
}State;



extern State* global_state;

void init_State(int group_size, int num_groups, ...);


