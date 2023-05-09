#pragma once
#include "queue.h"
#include "person.h"
#include "group.h"
#include "state.h"
#include "actions.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

extern Queue* person_threads;

void* t_manage_waiting_queue(void* args);

void* t_manage_groups_queue(void* args);

void* t_person(void* args);

void create_person_thread(int type);

void init_threads_infrastructure();

void join_all_person_threads();