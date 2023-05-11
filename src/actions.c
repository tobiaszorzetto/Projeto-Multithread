#include "actions.h"

void join_system(Person* p){
    sem_wait(&(global_state->join_waiting_queue_sem));
    enqueue(p, global_state->waiting_queue);
    sem_post(&(global_state->join_waiting_queue_sem));
    sem_post(&(global_state->waiting_queue_sem));
}

void join_group(Person* p, Group* g){
    g->participants[g->i] = p;
    g->i++;
    p->group_barrier = &(g->barrier);
}

void send_n_to_group(int n, Queue* q, Group* g){
    for(int i=0;i<n;i++){
        Person* p = dequeue(q);
        join_group(p,g);
    }
}

void try_to_find_group(Person* p){
    int type = p->type;
    int* queue_sizes = (int*) malloc(sizeof(int) * global_state->num_groups);
    int* valid_group = (int*) malloc(sizeof(int) * global_state->num_groups);
    for(int i=0; i<global_state->num_groups; i++){
        queue_sizes[i] = global_state->individuals_queue[i]->size;
        valid_group[i] = 0;
    }
    queue_sizes[type] +=1;
    
    int found_group = find_group(global_state->group_size, type,\
                        queue_sizes, global_state->group_proportions,\
                        global_state->num_groups, valid_group, type);

    if(found_group == 1){
        Group* g = new_group(global_state->group_size);
        join_group(p, g);
        send_n_to_group(valid_group[type]-1,global_state->individuals_queue[type],g);
        for(int i=0; i<global_state->num_groups; i++){
            if(i == type){continue;}
            send_n_to_group(valid_group[i], global_state->individuals_queue[i], g);
        }

        enqueue(g, global_state->groups_queue);
        sem_post(&(global_state->groups_queue_sem));
    }
    else{
        enqueue(p, global_state->individuals_queue[type]);
    }
    free(queue_sizes);
    free(valid_group);
    
}