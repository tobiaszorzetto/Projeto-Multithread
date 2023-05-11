#include "grouping_algorithm.h"
#define exec_and_return_if_true(f,...)({\
    int sol = f(__VA_ARGS__);\
    if(sol == 1){return sol;}\
})

int find_group(int free_seats,int type, int* queue_sizes, int* proportions,int num_groups, int* valid_group, int initial_type){
    int next_type = (type+1)%num_groups;

    
    if(next_type == initial_type){
        if(queue_sizes[type] >= free_seats && proportions[type] <= free_seats){
            valid_group[type] = free_seats;
            return 1;
        }
        else if(free_seats ==0){
            valid_group[type] = free_seats;
            return 1;
        }
        else{
            return 0;
        }
    }

    int upper_limit = queue_sizes[type]< free_seats? queue_sizes[type]: free_seats; 
    for(int i=proportions[type]; i<=upper_limit; i++){
        valid_group[type] = i;
        exec_and_return_if_true(find_group,free_seats-i, next_type, queue_sizes, proportions, num_groups, valid_group, initial_type);
    }

    if(type != initial_type){
        valid_group[type] = 0;
        exec_and_return_if_true(find_group,free_seats, next_type,queue_sizes, proportions, num_groups, valid_group, initial_type);
    }
    return 0;
}