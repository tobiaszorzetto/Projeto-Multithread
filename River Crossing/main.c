#include <pthread.h>
#include "helper.h"
#include "person.h"

int main() {
	init_structs();
	volatile int groups[2] = { 0,0 };

	pthread_t t1,t2,t3,t4;

	t1 = create_person(SERF, groups);
	t2 = create_person(SERF, groups);
	t3 = create_person(HACKER, groups);
	t4 = create_person(HACKER, groups);

	pthread_join(t1,NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	destroy_structs();
	return 0;
}
