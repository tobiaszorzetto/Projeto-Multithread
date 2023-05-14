#pragma once
#include "person.h"
#include "group.h"
#include "state.h"
#include "queue.h"
#include "grouping_algorithm.h"
#include "change.h"
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

//Inserts a given pernson into the global state
//in other words, includes the person in the waiting queue
void join_system(Person* p);

//Adds a given person to the list of participants of a given group
void join_group(Person* p, Group* g);

//Removes n elements from a given queue and places them in a given group
//whilst also notifying a publisher of every dequeue that happens 
void send_n_to_group(int n, Queue* q, Group* g, Publisher* pub);

//Looks through the queues for each type of person and tries to find a
//valid group that includes the given person. If a group is fonud, the person
//is included in it and the group joins the groups queue, otherwise, the person
//joins the queue of people with its type
void try_to_find_group(Person* p);
