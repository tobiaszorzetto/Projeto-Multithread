#pragma once
#include <stdlib.h>
#include <semaphore.h>
#include <stdarg.h>
#include "queue.h"
#include "publisher.h"
#include "animation.h"

typedef struct {
    WINDOW *topMargin;
    WINDOW *botMargin;
    WINDOW *topWaves;
    WINDOW *botWaves;
    WINDOW *boatWin;
    WINDOW *individualsQueueWin;
} Windows;

typedef struct{
    int group_size;
    int num_groups;
    int* group_proportions;

    
    Publisher* waiting_queue_publisher;
    sem_t join_waiting_queue_sem;
    sem_t waiting_queue_sem;
    Queue* waiting_queue;// queue of Person

    Publisher** individuals_queue_publishers;
    sem_t* individuals_queue_sems;
    Queue** individuals_queue;// queue of Person

    Publisher* groups_queue_publisher;
    sem_t groups_queue_sem;
    Queue* groups_queue;// queue of Group

    Queue* change_queue;// queue of Change
    sem_t main_sem;

    Windows* windows; // animation windows
}State;



extern State* global_state;

void init_State(int group_size, int num_groups, ...);

void set_up_state_queue(Queue** q, sem_t* q_sem, Publisher** pub);


