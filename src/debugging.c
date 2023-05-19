#include "debugging.h"

void debugging_waiting_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        printf("joined waiting queue\n");
        fflush(stdout);
    }
    else{
        printf("left waiting queue\n");
        fflush(stdout);
    }
}

void debugging_individuals_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        printf("joined %d individuals queue\n",((Person*)q_c->diff_elem)->type);
        fflush(stdout);
    }
    else{
        printf("left %d individuals queue\n",((Person*)q_c->diff_elem)->type);
        fflush(stdout);
    }
}

void debugging_groups_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        for (int i = 0; i < ((Group*)q_c->diff_elem)->size; i++) {
             printf("type = %d\n", ((Group*)q_c->diff_elem)->participants[i]->type);
        }
        fflush(stdout);
    }
    else{
        printf("left groups queue\n");
        fflush(stdout);
    }
}

void debugging_setup(){
    subscribe(global_state->waiting_queue_publisher,debugging_waiting_queue);
    for(int i=0; i<global_state->num_groups; i++){
        subscribe(global_state->individuals_queue_publishers[i], debugging_individuals_queue);
    }
    subscribe(global_state->groups_queue_publisher, debugging_groups_queue);
}