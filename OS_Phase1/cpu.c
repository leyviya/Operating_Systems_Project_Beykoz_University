#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
	   fprintf(stderr, "use: cpu <string>\n");
	   exit(1);
    }
    char *str = argv[1];

    while (1) {
	   printf("%s\n", str);
	   Spin(2);
    }
    return 0;
}
