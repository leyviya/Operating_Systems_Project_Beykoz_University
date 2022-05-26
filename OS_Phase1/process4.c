#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	printf("My initial pid: %d \n", (int) getpid());
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "Cannot create process\n");
		exit(1);
	}
	if(rc == 0){
		printf("I am child, my pid: %d \n", (int) getpid());
		char *myargs[3];
		myargs[0] = strdup("wc");
		myargs[1] = strdup("process4.c");
		myargs[2] = NULL;

		execvp(myargs[0], myargs);
		printf("This will not print");
	} else {
		int rc_wait = wait(NULL);
		printf("I am parent, my pid: %d \n", (int) getpid());
	}
	return 0;
}