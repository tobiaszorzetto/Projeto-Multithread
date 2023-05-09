#include "state.h"

State* global_state;

void init_State(int group_size, int num_groups, ...){
    global_state = (State *) malloc(sizeof(State));

    //constants
    global_state->group_size = group_size;
    global_state->num_groups = num_groups;
    global_state->group_proportions = (int*) malloc(sizeof(int)*num_groups);
    
    va_list ptr;
    va_start(ptr, num_groups);
    for(int i=0; i<num_groups; i++){
        global_state->group_proportions[i] = (int)(group_size*va_arg(ptr, double));
    }
    va_end(ptr);

    //setting up queues

    sem_init(&(global_state->join_waiting_queue_sem),0,1);
    sem_init(&(global_state->waiting_queue_sem),0,0);
    global_state->waiting_queue = new_queue(10);

    global_state->individuals_queue = (Queue**)malloc(sizeof(Queue*)*num_groups);
    global_state->individuals_queue_sems = (sem_t*)malloc(sizeof(sem_t)*num_groups);
    for(int i=0; i<num_groups;i++){
        global_state->individuals_queue[i] = new_queue(10);
        sem_init(&(global_state->individuals_queue_sems[i]),0,0);
    }

    sem_init(&(global_state->groups_queue_sem),0,0);
    global_state->groups_queue = new_queue(10);

    sem_init(&(global_state->main_sem),0,0);
}

