#include "group.h"
int last_id = 0;

Group* new_group(int size){
    Group* g = (Group*) malloc(sizeof(Group));
    g->participants = (Person**) malloc(sizeof(Person*)* size);
    g->size = size;
    g->i = 0;
    g->id = last_id;
    last_id++;
    sem_init(&(g->system_permission), 0, 0);
    pthread_barrier_init(&(g->barrier), NULL, size+1);
    return g;
}

void delete_group(Group* g){
    free(g->participants);
    sem_destroy(&(g->system_permission));
    pthread_barrier_destroy(&(g->barrier));
    free(g);    
}