#include "person.h"
t_args* new_t_args(int type, int*groups) {
	t_args* new_args = (t_args*)malloc(sizeof(t_args));
	new_args->type = type;
	new_args->groups = groups;
}

pthread_t create_person(int type, int* groups) {
	pthread_t t;
	t_args* args = new_t_args(type, groups);
	pthread_create(&t, NULL, generic_thread, args);
	return t;
}

void join_group(int type, int* groups) { groups[type] += 1; }

void pass_group(int type, int r_type, int num_type, int num_r_type, int* groups) {
	sem_post_n(&(queues[type]), num_type);
	sem_post_n(&(queues[r_type]), num_r_type);
	groups[type] -= num_type;
	groups[r_type] -= num_r_type;
}

void* generic_thread(void* arg) {
	t_args params = *((t_args*) arg);
	
	int* groups = params.groups;

	int type = params.type;
	int r_type = (type + 1) % 2;

	int is_captain = FALSE;
	
	if (sem_trywait(&state_mutex) != 0) {
		animate_wrapper(WAITING, sem_wait, &state_mutex);
	}

	animate_wrapper(LOOKING, join_group, type, groups);

	if (groups[type] == GROUP_SIZE) {
		animate_wrapper(FOUND_GROUP, pass_group, type, r_type, GROUP_SIZE, 0, groups);
		is_captain = TRUE;
	}

	else if (groups[type] == GROUP_SIZE / 2 && groups[r_type] >= GROUP_SIZE / 2 && GROUP_SIZE % 2 == 0) {
		animate_wrapper(FOUND_GROUP, pass_group,type, r_type, GROUP_SIZE/2, GROUP_SIZE/2, groups);
		is_captain = TRUE;
	}

	else {
		animate_wrapper(NOT_FOUND_GROUP, sem_post, &state_mutex);
	}

	animate_wrapper(BOARDING, sem_wait, &(queues[type]));

	pthread_barrier_wait(&barrier);

	if (is_captain) {
		animate_wrapper(ROWING,sem_post,&state_mutex);
	}

	return NULL;
}