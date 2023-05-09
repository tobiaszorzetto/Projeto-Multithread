#include "person.h"

Person* new_person(int type){
    Person* p = (Person*) malloc(sizeof(Person));
    p->type = type;
    sem_init(&(p->system_permission),0,0);
    sem_init(&(p->r_system_permission),0,0);
    return p;
}