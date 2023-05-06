#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define GROUP_SIZE 4

#define TRUE 1
#define FALSE 0

#define SERF 1
#define HACKER 0 

#define WAITING 0
#define LOOKING 1
#define FOUND_GROUP 2
#define NOT_FOUND_GROUP 3
#define BOARDING 4
#define ROWING 5

#define animate_wrapper(animation_type,func,...)\
{\
	func(__VA_ARGS__);\
	switch(animation_type)\
	{\
		case WAITING:\
			printf("waiting to join\n");\
			break;\
		case LOOKING:\
			printf("looking for group\n");\
			break;\
		case FOUND_GROUP:\
			printf("found group\n");\
			break;\
		case NOT_FOUND_GROUP:\
			printf("didn't find group\n");\
			break;\
		case BOARDING:\
			printf("boarding\n");\
			break;\
		case ROWING:\
			printf("rowing\n");\
			break;\
		default:\
			break;\
	}\
}

pthread_barrier_t barrier;
sem_t state_mutex;
sem_t queues[2];


void sem_post_n(sem_t* sem, int n);

void init_structs();

void destroy_structs();