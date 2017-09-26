#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	if (argc==1) {
		return -1;
	}
	// assume there are no options
	unsigned int delay = atoi(argv[1]);
	sleep(delay);
	return 0;
}
