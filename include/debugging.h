#pragma once
#include "publisher.h"
#include "state.h"
#include "change.h"

void debugging_setup();

void debugging_waiting_queue(void* args);

void debugging_individuals_queue(void* args);

void debugging_groups_queue(void* args);