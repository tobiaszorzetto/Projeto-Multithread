#include "state.h"
#include "threads.h"
#include "publisher.h"
#include "change.h"
#include "person.h"
#include "animation.h"
#include <unistd.h>

void waiting_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        //printf("joined waiting queue\n");
        //fflush(stdout);
    }
    else{
        //printf("left waiting queue\n");
        //fflush(stdout);
    }
}

void individuals_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        //printf("joined %d individuals queue\n",((Person*)q_c->diff_elem)->type);
        drawQueue();
        //fflush(stdout);
    }
    else{
        //printf("left %d individuals queue\n",((Person*)q_c->diff_elem)->type);
        drawQueue();
        //fflush(stdout);
    }
}

void groups_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        // for (int i = 0; i < ((Group*)q_c->diff_elem)->size; i++) {
        //     printf("type = %d\n", ((Group*)q_c->diff_elem)->participants[i]->type);
        // }
        //fflush(stdout);
        runBoat((Group*)q_c->diff_elem);
    }
    else{
        //runBoat();
        //printf("left groups queue\n");
        //fflush(stdout);
    }
}

int main() {
    initscr();
    curs_set(0);
	init_State(4,3, 0.25, 0.5, 0.25);
    initializeWindows();
	init_threads_infrastructure();

    subscribe(global_state->waiting_queue_publisher,waiting_queue);
    for(int i=0; i<global_state->num_groups; i++){
        subscribe(global_state->individuals_queue_publishers[i], individuals_queue);
    }
    subscribe(global_state->groups_queue_publisher, groups_queue);

    pthread_t* t = (pthread_t*)malloc(sizeof(pthread_t));
    pthread_create(t, NULL, moveWaves, NULL);
    
    int pessoas[20] = {0,1,2,2,1,2,1,0,1,2,2,1,0,2,1,2,1,0,2,1};

    for(int i = 0; i < 20; i++){
        create_person_thread(pessoas[i]);
        sleep(1);
    }

    join_all_person_threads();
    pthread_join(*t, NULL);
    // sleep(3);
    endwin();
	return 0;
}
