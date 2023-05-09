#include "group.h"

Group* new_group(int size){
    Group* g = (Group*) malloc(sizeof(Group));
    g->participants = (Person**) malloc(sizeof(Person*)* size);
    g->size = size;
    g->i = 0;
    sem_init(&(g->system_permission), 0, 0);
    pthread_barrier_init(&(g->barrier), NULL, size+1);
    return g;
}