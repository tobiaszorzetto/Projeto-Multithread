#include "actions.h"
#define try_group_size(i,type, num_current_group,testing,group) (\
{\
    for(int j=0; j<global_state->num_groups; j++){\
            if(num_current_group==global_state->group_size){break;}\
            if(j==type){continue;}\
            if(global_state->individuals_queue[j]->size >=i){\
                num_current_group +=i;\
                if(testing==0){\
                    send_n_to_group(i,global_state->individuals_queue[j],group);\
                }\
            }\
    }\
})

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
    int starting_point = global_state->group_size > (global_state->individuals_queue[type]->size+1) ? global_state->individuals_queue[type]->size+1 : global_state->group_size;
    int found_group = 0;
    for(int i=starting_point; i>0; i--){
        if(global_state->group_size%i!=0){ continue;}
        
        int num_current_group = i;
        try_group_size(i,type,num_current_group, 1, NULL);

        if(num_current_group==global_state->group_size){
            found_group =1;
            num_current_group = i;
            Group* g = new_group(global_state->group_size);
            join_group(p, g);
            send_n_to_group(i-1,global_state->individuals_queue[type],g);
            try_group_size(i,type,num_current_group, 0, g);
            
            enqueue(g, global_state->groups_queue);
            sem_post(&(global_state->groups_queue_sem));
            break;
        }

    }
    if(!found_group){
        enqueue(p, global_state->individuals_queue[type]);
    }
    
}