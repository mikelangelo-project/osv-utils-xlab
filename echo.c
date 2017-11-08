#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	if (argc >= 2) {
		printf("%s", argv[1]);
	}
	for (int ii=2; ii<argc; ii++) {
		printf(" %s", argv[ii]);
	}
	printf("\n");
	return 0;
}
