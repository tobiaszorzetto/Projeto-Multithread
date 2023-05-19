#include "state.h"
#include "threads.h"
#include "publisher.h"
#include "change.h"
#include "person.h"
#include "animation.h"
#include <unistd.h>
#include "debugging.h"

void individuals_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        drawQueue();
    }
    else{
        drawQueue();
    }
}

void groups_queue(void* args){
    Queue_change* q_c = args;
    if(q_c->diff == 1){
        ;
    }
    else{
        runBoat(q_c->diff_elem);
    }
}

int main() {
    initscr();
    curs_set(0);
	init_State(4,2,0.5, 0.5);
    initializeWindows();
	init_threads_infrastructure();
    //debugging_setup();

    for(int i=0; i<global_state->num_groups; i++){
        subscribe(global_state->individuals_queue_publishers[i], individuals_queue);
    }
    subscribe(global_state->groups_queue_publisher, groups_queue);
    
    
    pthread_t t;
    pthread_create(&t, NULL, moveWaves, NULL);
    
    int pessoas[20] = {0,1,0,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1};

    for(int i = 0; i < 20; i++){
        create_person_thread(pessoas[i]);
        sleep(1);
    }

    join_all_person_threads();
    pthread_join(t, NULL);
    sleep(3);
    endwin();
	return 0;
}
