#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	
	printf("my pid: %d \n", (int)getpid());
	int rc = fork();
	printf("This is after fork\n");
	printf("my pid: %d rc: %d \n", (int) getpid(), rc);
}
