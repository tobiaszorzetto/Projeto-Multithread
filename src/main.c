#include "state.h"
#include "threads.h"
#include "publisher.h"
#include "change.h"
#include "person.h"
#include "animation.h"
#include <unistd.h>

#define BOAT_SIZE 6
#define NUM_GROUPS 2


int main() {
	init_State(BOAT_SIZE,NUM_GROUPS,0.5, 0.5);

    animation_setup();
	init_threads_infrastructure();
    animation_subscribe();
    
    pthread_t t;
    pthread_create(&t, NULL, moveWaves, NULL);
     
    int pessoas[20] = {0,1,1,0,1,0,0,0,0,1,1,0,1,0,1,1,0,1,0,1};

    for(int i = 0; i < 20; i++){
        create_person_thread(pessoas[i]);
        sleep(1);
    }

    join_all_person_threads();
    sleep(3);
    endwin();
	return 0;
}
