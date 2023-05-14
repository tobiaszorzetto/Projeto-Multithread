#pragma once
#include "queue.h"
#include "change.h"
#include "person.h"
#include "group.h"
#include "state.h"
#include "actions.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM_PERSON_THREADS 20
extern Queue* person_threads;

// thread responsible for taking people out of the waiting queue
// and allowing them to try to find a group
void* t_manage_waiting_queue(void* args);

// thread responsible for taking groups out of the groups queue
// and allowing them to leave, in other words, board the boat
void* t_manage_groups_queue(void* args);

// thread responsible for describing the actions of a given person
// up until they board a boat
void* t_person(void* args);

// creates a person and a thread with the function t_person responsible
// for simulating the actions of this individual
void create_person_thread(int type);

// creates a thread with the function t_manage_waiting_queue and a thread 
// with the function t_manage_groups_queue, both functions described above.
// The function also initializes the queue that will contain every person's thread
void init_threads_infrastructure();

// a function that ensures the main thread only ends after all person threads 
// have finished execution(found a group)
void join_all_person_threads();