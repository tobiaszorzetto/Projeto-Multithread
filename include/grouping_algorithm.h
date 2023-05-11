#pragma once
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

int find_group(int free_seats,int type, int* queue_sizes, int* proportions,int num_groups, int* valid_group, int initial_type);
