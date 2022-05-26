#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_function(void *arg){
	printf("%s\n", (char *)arg);
	return NULL;
}

int main(int argc, char const *argv[]){
	pthread_t th1, th2;
	printf("main begins\n");

	pthread_create(&th1, NULL, thread_function, "A");
	pthread_create(&th2, NULL, thread_function, "B");
	printf("main ends\n");

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	return 0;
}