#pragma once
#include "person.h"
#include "group.h"
#include "state.h"
#include "queue.h"
#include "grouping_algorithm.h"
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

void join_system(Person* p);

void join_group(Person* p, Group* g);

void send_n_to_group(int n, Queue* q, Group* g);

void try_to_find_group(Person* p);
