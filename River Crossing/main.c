#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define GROUP_SIZE 4
sem_t barrier;
sem_t state_mutex;
int hackers;
sem_t hackerQueue;
int serfs;
sem_t serfQueue;

typedef enum { false, true } bool;

void sem_post_n(sem_t* sem,int n) {
	for (int i = 0; i < n; i++) {
		sem_post(sem);
	}
}

void* hacker_thread(void* arg) {
	bool is_captain = false;

	printf("waiting to join\n");
	sem_wait(&state_mutex);
	printf("looking for group\n");
	hackers += 1;
	if(hackers == GROUP_SIZE){
		printf("found group\n");
		sem_post_n(&hackerQueue, GROUP_SIZE);
		hackers = 0;
		is_captain = true;
	}
	else if (hackers == GROUP_SIZE/2 && serfs >= GROUP_SIZE/2) {
		printf("found group\n");
		sem_post_n(&hackerQueue, GROUP_SIZE / 2);
		sem_post_n(&serfQueue, GROUP_SIZE / 2);
		serfs -= 2;
		hackers = 0;
		is_captain = true;
	}
	else {
		printf("didn't find group\n");
		sem_post(&state_mutex);
	}

	sem_wait(&hackerQueue);
	printf("boarding\n");

	sem_wait(&barrier);

	if (is_captain) {
		printf("rowing\n");
		sem_post(&state_mutex);
	}

	return NULL;
}

void* serf_thread(void* arg) {
	bool is_captain = false;

	sem_wait(&state_mutex);
	serfs += 1;
	if (serfs == GROUP_SIZE) {
		printf("found group\n");
		sem_post_n(&serfQueue, GROUP_SIZE);
		serfs = 0;
		is_captain = true;
	}
	else if (serfs == GROUP_SIZE / 2 && hackers >= GROUP_SIZE / 2) {
		printf("found group\n");
		sem_post_n(&hackerQueue, GROUP_SIZE / 2);
		sem_post_n(&serfQueue, GROUP_SIZE / 2);
		serfs = 0;
		hackers -= 2;
		is_captain = true;
	}
	else {
		printf("didn't find group\n");
		sem_post(&state_mutex);
	}

	sem_wait(&serfQueue);
	printf("boarding\n");

	sem_wait(&barrier);
	if (is_captain) {
		printf("rowing\n");
		sem_post(&state_mutex);
	}

	return NULL;
}


void init_semaphores() {
	sem_init(&state_mutex, 0, 1);
	sem_init(&barrier, 0, GROUP_SIZE);
	sem_init(&hackerQueue, 0, 0);
	sem_init(&serfQueue, 0, 0);

}

void destroy_semaphores() {
	sem_destroy(&state_mutex);
	sem_destroy(&barrier);
	sem_destroy(&hackerQueue);
	sem_destroy(&serfQueue);
}


int main() {
	init_semaphores();

	pthread_t t1,t2,t3,t4;
	pthread_create(&t1, NULL, hacker_thread, NULL);
	pthread_create(&t2, NULL, hacker_thread, NULL);
	pthread_create(&t3, NULL, hacker_thread, NULL);
	pthread_create(&t4, NULL, hacker_thread, NULL);

	pthread_join(t1,NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	destroy_semaphores();
	return 0;
}
