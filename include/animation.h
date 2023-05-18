#pragma once

#include <ncurses.h>
#include "queue.h"
#include "person.h"
#include "state.h"
#include <string.h>
#include <unistd.h>
#include "group.h"

#define MAX_BOAT_SIZE 50
#define TOP_MARGIN_POS 1
#define BOT_MARGIN_POS 11
#define WIN_WIDTH 150

// void animate(int animation_type, Queue* fila);
void* moveWaves();
void initializeWindows();
void drawRiverMargins();
void drawWaves();
void drawQueue();

// void* runAnimation(void* args);

char* getBoat(Group* g);
char* getQueue(int type);
void runBoat();
// int formQueue();
