#include "state.h"
#include "threads.h"



int main() {
	init_State(4,3, 0.25, 0.5, 0.25);
	init_threads_infrastructure();

    create_person_thread(1);
    create_person_thread(1);
    create_person_thread(2);
    create_person_thread(2);
    join_all_person_threads();

	return 0;
}
