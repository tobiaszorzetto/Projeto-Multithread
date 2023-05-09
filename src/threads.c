#include "threads.h"

Queue* person_threads;

void* t_manage_waiting_queue(void* args){
    while(1){
        sem_wait(&(global_state->waiting_queue_sem));
        Person* p = dequeue(global_state->waiting_queue);
        sem_post(&(p->system_permission));

        sem_wait(&(p->r_system_permission)); 
    }
}

void* t_manage_groups_queue(void* args){
    while(1){
        sem_wait(&(global_state->groups_queue_sem));
        Group* g = dequeue(global_state->groups_queue);
        
        for(int i=0; i<g->size; i++){
            Person* p = g->participants[i];
            sem_post(&(p->system_permission));
        }

        pthread_barrier_wait(&(g->barrier));
        printf("rowing\n");
    }
}

void* t_person(void* args){
    Person* p = (Person*) args;

    join_system(p);
    sem_wait(&(p->system_permission));
    
    try_to_find_group(p);
    
    sem_post(&(p->r_system_permission));
    sem_wait(&(p->system_permission));    
    printf("person of type %d boarding\n", p->type);

    pthread_barrier_wait(p->group_barrier);
    return NULL;
}

void create_person_thread(int type){
    pthread_t* t = (pthread_t*)malloc(sizeof(pthread_t));
    Person* p = new_person(type);
    pthread_create(t, NULL , t_person, p);
    enqueue(t, person_threads);
}
void init_threads_infrastructure(){
    pthread_t tw;
    pthread_t tg;
    pthread_create(&tw, NULL, t_manage_waiting_queue, NULL);
    pthread_create(&tg, NULL, t_manage_groups_queue, NULL);

    person_threads = new_queue(20);
}

void join_all_person_threads(){
    while(person_threads->size !=0){
        pthread_t* t = dequeue(person_threads);
        pthread_join(*t, NULL);
    }
}