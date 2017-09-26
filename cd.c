#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	int ret;
	if (argc==1) {
		return 0;
	}
	// assume there are no options
	const char *path = argv[1];
	ret = chdir(path);
	if (ret) {
		char msg[512];
		snprintf(msg, sizeof(msg), "%s %s: chdir failed", argv[0], path);
		perror(msg);
		return -1;
	}
	// execl("/bin/ls", "-tarl", nullptr);
	return 0;
}
