#pragma once
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// Recursive function that checks, given a configuration of queues, if there is a group 
// that fits the boat and respects the proportions demanded by each type of person. 
// If any group is found, it's saved in the list valid_group where 
// valid_group[i] = the ammout of people of type i in the boat
int find_group(int free_seats,int type, int* queue_sizes, int* proportions,int num_groups, int* valid_group, int initial_type);
