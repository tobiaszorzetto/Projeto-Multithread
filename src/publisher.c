#include "publisher.h"

Publisher* new_publisher(){
    Publisher* p = (Publisher*) malloc(sizeof(Publisher));
    p->free_index = 0;
    return p;
}

void subscribe(Publisher* pub, void(*function)(void*)){
    pub->subscribers[pub->free_index] = function;
    pub->free_index++;
}

void publish(Publisher* pub, void* arg){
    for(int i=0; i<pub->free_index;i++){
        (*pub->subscribers[i])(arg); 
    }
}