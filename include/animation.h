#ifndef animationh

#define animationh

#include "helper.h"

#define MAX_ANIMATION_SIZE 100

typedef struct Fila
{
	int items[MAX_ANIMATION_SIZE];
	int front;
	int rear;
} Fila;

void enQueue(int animation_type, Fila* fila);

int deQueue(Fila* fila);

Fila* initQueue();

void runBoat();
char* getQueue(int* groups, int type);
char* getBoat(int* groups, int* groupsAntigo);
int formQueue();

void animate(int animation_type, Fila* fila);

#endif



