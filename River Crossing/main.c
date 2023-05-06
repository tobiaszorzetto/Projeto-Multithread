#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define GROUP_SIZE 4
pthread_barrier_t barrier;
sem_t state_mutex;
int groups[2] = {0,0};
sem_t queues[2];	

typedef enum { false, true } bool;

void sem_post_n(sem_t* sem,int n) {
	for (int i = 0; i < n; i++) {
		sem_post(sem);
	}
}

void* generic_thread(void* arg) {
	bool is_captain = false;
	int type = *((char*)arg);
	int r_type = (type + 1) % 2;

	if (sem_trywait(&state_mutex) != 0) {	
		printf("waiting to join\n");
		sem_wait(&state_mutex);
	}
	printf("looking for group\n");
	groups[type] += 1;
	if (groups[type] == GROUP_SIZE) {
		printf("found group\n");
		sem_post_n(&(queues[type]), GROUP_SIZE);
		groups[type] = 0;
		is_captain = true;
	}
	else if (groups[type] == GROUP_SIZE / 2 && groups[r_type] >= GROUP_SIZE / 2) {
		printf("found group\n");
		sem_post_n(&(queues[type]), GROUP_SIZE / 2);
		sem_post_n(&(queues[r_type]), GROUP_SIZE / 2);
		groups[r_type] -= GROUP_SIZE/2;
		groups[type] = 0;
		is_captain = true;
	}
	else {
		printf("didn't find group\n");
		sem_post(&state_mutex);
	}

	sem_wait(&(queues[type]));
	printf("boarding\n");

	pthread_barrier_wait(&barrier);

	if (is_captain) {
		printf("rowing\n");
		sem_post(&state_mutex);
	}

	return NULL;
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


int main() {
	init_structs();

	pthread_t t1,t2,t3,t4;
	int type = 0;
	pthread_create(&t1, NULL, generic_thread, &type);
	pthread_create(&t2, NULL, generic_thread, &type);
	pthread_create(&t3, NULL, generic_thread, &type);
	pthread_create(&t4, NULL, generic_thread, &type);

	pthread_join(t1,NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	destroy_structs();
	return 0;
}
