#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static volatile int counter = 0;

void *thread_function(void *arg){
	printf("%s: gebins\n", (char *) arg);
	for(int i= 0; i<1e5; i++){
		counter += 1;
	}
	printf("%s: done\n", (char *)arg);
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t th1, th2;
	printf("main begins, counter = %d\n", counter);

	pthread_create(&th1, NULL, thread_function, "A");
	pthread_create(&th2, NULL, thread_function, "B");

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	printf("main ends, counter = %d\n", counter);
	return 0;
}