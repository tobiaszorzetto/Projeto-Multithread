#include "helper.h"

 pthread_barrier_t barrier;
 sem_t state_mutex;
 sem_t queues[2];

void sem_post_n(sem_t* sem, int n) {
	for (int i = 0; i < n; i++) {
		sem_post(sem);
	}
}

void init_structs() {
	sem_init(&state_mutex, 0, 1);
	pthread_barrier_init(&barrier, NULL, GROUP_SIZE);
	sem_init(&(queues[0]), 0, 0);
	sem_init(&(queues[1]), 0, 0);

}

void destroy_structs() {
	sem_destroy(&state_mutex);
	pthread_barrier_destroy(&barrier);
	sem_destroy(&(queues[0]));
	sem_destroy(&(queues[1]));
}
