#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

typedef struct {
	int type;
	int* groups;
}t_args;

void* generic_thread(void* arg);

t_args* new_t_args(int type, int* groups);

pthread_t create_person(int type, int* groups);