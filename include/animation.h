#pragma once

#include <ncurses.h>
#include "queue.h"
#include "person.h"
#include "state.h"
#include <string.h>
#include <unistd.h>
#include "group.h"
#include "change.h"

#define MARGIN_LEN 110
#define MAX_BOAT_SIZE 100
#define TOP_MARGIN_POS 1
#define BOT_MARGIN_POS 11
#define WIN_WIDTH 150


// Initializes ncurses settings and animation screen
void animation_setup();

// Defines animation subscribers
void animation_subscribe();


// Updates individuals queues in animation
void individuals_queue(void* args);

// Updates groups queues in animation
void groups_queue(void* args);

// Initializes all windows used in the animation
void initializeWindows();

// Animates the moving waves
void* moveWaves();

// Initializes margin windows and draws the river margins on the screen
void drawRiverMargins();

// Initializes waves windows and draws the waves on the screen
void drawWaves();

// Draws the queues of individuals that are waiting for a group
void drawQueue();

// Draws the queue of formed groups that are waiting for a boat
void drawGroupsQueue();

// Returns a string that represents the goups queue
char* getGroupsQueue();

// Returns a string that represents the boat formed by the group "g"
char* getBoat(Group* g);

// Returns a string that represents the queue of individuals of a certain "type"
// that are waiting for a group
char* getQueue(int type);

// Runs the animation of a boat crossing the river with group "g"
void runBoat(Group* g);