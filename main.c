#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd = open("test.txt", O_CREAT | O_RDWR, 0644);
	dprintf(fd, "helfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeewwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwlo\nworld\nim taha nahid and im testing this function i hopre it doesnt work");
	lseek(fd, 0, SEEK_SET);
	char*line;
	for (int i = 0; i < 3; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
}
