#include "state.h"
#include "threads.h"
#include "publisher.h"
#include "change.h"
#include "person.h"

void waiting_queue(void* args){
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

void individuals_queue(void* args){
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

void groups_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        printf("joined groups queue\n");
        fflush(stdout);
    }
    else{
        printf("left gruops queue\n");
        fflush(stdout);
    }
}


int main() {
	init_State(4,3, 0.25, 0.5, 0.25);
	init_threads_infrastructure();

    subscribe(global_state->waiting_queue_publisher,waiting_queue);
    for(int i=0; i<global_state->num_groups; i++){
        subscribe(global_state->individuals_queue_publishers[i], individuals_queue);
    }
    subscribe(global_state->groups_queue_publisher, groups_queue);

    create_person_thread(1);
    create_person_thread(1);
    create_person_thread(2);
    create_person_thread(2);
    
    join_all_person_threads();

	return 0;
}
