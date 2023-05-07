#include <pthread.h>
#include "helper.h"
#include "person.h"
#include "animation.h"

Fila* filaAnimation= initQueue();

int main() {
	init_structs();
	int groups[2] = { 0,0 };

	pthread_t t1,t2,t3,t4;

	t1 = create_person(SERF, groups, filaAnimation);
	t2 = create_person(SERF, groups, filaAnimation);
	t3 = create_person(HACKER, groups, filaAnimation);
	t4 = create_person(HACKER, groups, filaAnimation);

	pthread_join(t1,NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	destroy_structs();
	return 0;
}
