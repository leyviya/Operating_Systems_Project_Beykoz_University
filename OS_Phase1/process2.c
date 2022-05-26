#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("My initial pid: %d \n", (int) getpid());
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "Cannot create process\n");
		exit(1);
	}
	if(rc == 0){
		printf("I am child, my pid: %d \n", (int) getpid());
	} else {
		printf("I am parent, my pid: %d \n", (int) getpid());
	}
	return 0;
}