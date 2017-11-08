#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int ret;
	if (argc==1) {
		return 0;
	}
	// assume there are no options
	const char *file = argv[1];
	int fd = open(file, O_RDONLY);
	if (fd < 0) {
		ret = errno;
		char msg[512];
		snprintf(msg, sizeof(msg), "%s %s: open failed", argv[0], file);
		perror(msg);
		return ret;
	}
	char buf[1024] = "";
	ssize_t nread, nwritten, bufsz=sizeof(buf);
	while ((nread=read(fd, buf, bufsz)) > 0) {
		nwritten = write(STDOUT_FILENO, buf, nread);
		if (nwritten != nread) {
			return errno;
		}
	}
	return 0;
}
