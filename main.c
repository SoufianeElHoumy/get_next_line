#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// int main(void)
// {
// 	int fd = open("test.txt", O_CREAT | O_RDWR, 0644);
// 	dprintf(fd, "helfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeewwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwlo\nworld\nim taha nahid and im testing this function i hopre it doesnt work");
// 	lseek(fd, 0, SEEK_SET);
// 	char*line;
// 	for (int i = 0; i < 3; i++)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 	}
// }



// int    main(void)
// {
//     char *line = NULL;
//     int fd = open("txt.txt", O_CREAT | O_RDWR);
//     // write(fd, "hello\nworld\n42", 14);
// 	dprintf(fd, "hello\n");
// 	dprintf(fd, "hello1\n");
// 	dprintf(fd, "hello2\n");
//     close(fd);
//     fd = open("txt.txt", O_RDONLY);

//     line = get_next_line(fd);
//     printf("%s", line);
//     free(line);
//     line = get_next_line(fd);
//     printf("%s", line);
//     free(line);
//     line = get_next_line(fd);
//     printf("%s", line);
//     free(line);

//     close(fd);
// }


// int main()
// {
// 	int fd = open("soufian", O_CREAT | O_RDWR, 0444);
// 	int x = dprintf(fd, "hello");
// 	printf("%d", x);
// }










int main()
{
	int fd = open("test", O_CREAT | O_RDWR, 0644);
	dprintf(fd, "benzzamlkaykhchih\nkaml");
	int x = open("test", O_RDWR);
	char	*s;
	while ((s = get_next_line(x)))
		printf("%s", s);
}