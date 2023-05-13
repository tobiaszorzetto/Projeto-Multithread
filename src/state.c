#include "state.h"

State* global_state;

void set_up_state_queue(Queue** q, sem_t* q_sem, Publisher** pub){
    sem_init(q_sem,0,0);
    (*q) = new_queue(10);
    (*pub) = new_publisher();
}

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
    set_up_state_queue(&(global_state->waiting_queue),\
                       &(global_state->waiting_queue_sem),\
                       &(global_state->waiting_queue_publisher));


    global_state->individuals_queue = (Queue**)malloc(sizeof(Queue*)*num_groups);
    global_state->individuals_queue_sems = (sem_t*)malloc(sizeof(sem_t)*num_groups);
    global_state->individuals_queue_publishers = (Publisher**) malloc(sizeof(Publisher*)*num_groups);

    for(int i=0; i<num_groups;i++){
        set_up_state_queue(&(global_state->individuals_queue[i]),\
                           &(global_state->individuals_queue_sems[i]),\
                           &(global_state->individuals_queue_publishers[i]));
    }

    set_up_state_queue(&(global_state->groups_queue),\
                       &(global_state->groups_queue_sem),\
                       &(global_state->groups_queue_publisher));

    sem_init(&(global_state->main_sem),0,0);
}

