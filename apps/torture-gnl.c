#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	char *buf;

	if (argc == 2)
	{
		int fd = open(argv[1], O_RDONLY);
		assert(fd >= 0);
		while (get_next_line(fd, &buf) > 0)
		{
			printf(":%30s : \'%s\'", "#", buf);
			free(buf);
			buf = NULL;
		}
		free(buf);
		return (0);
	}
	else
	{
		return (1);
	}
}
