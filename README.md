*This project has been created as part of the 42 curriculum by soel-hou.*

# get_next_line

## Description

**get_next_line** is a C function that reads a file descriptor and returns its content **one line at a time**, each time it is called.

```c
char *get_next_line(int fd);
```

- It returns the line that was read, **including the terminating `\n`** (except at the end of a file that does not end with a newline).
- It returns `NULL` when there is nothing else to read or when an error occurs.
- It works with files as well as standard input.

The goal of the project is to learn about **static variables**, **file descriptors**, **buffered reading with `read()`** and **dynamic memory management** in C, while keeping the function leak-free and independent from the value of `BUFFER_SIZE`.

### Bonus

The bonus part adds:

- The use of **a single static variable**.
- Support for **multiple file descriptors at the same time**: you can alternate calls between several open files (e.g. `fd 3`, then `fd 4`, then `fd 3` again) without losing the reading state of each one.

### Files

| File | Description |
|------|-------------|
| `get_next_line.c` | Main function and its helpers |
| `get_next_line_utils.c` | Utility functions (string length, search, join, etc.) |
| `get_next_line.h` | Header file (prototypes, `BUFFER_SIZE` default value) |
| `get_next_line_bonus.c` | Bonus: main function with multi-fd support |
| `get_next_line_utils_bonus.c` | Bonus: utility functions |
| `get_next_line_bonus.h` | Bonus: header file |

## Instructions

### Compilation

The function must be compiled with the `-D BUFFER_SIZE=n` flag, where `n` is the size of the buffer used by `read()`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

For the bonus part:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

If `BUFFER_SIZE` is not provided, a default value is defined in the header file.

### Execution

Example of a simple `main.c` for testing:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

Then run:

```bash
./gnl
```

You can test different buffer sizes (e.g. `1`, `42`, `9999`, `10000000`) to make sure the behavior is always the same. Memory leaks can be checked with:

```bash
valgrind --leak-check=full ./gnl
```

## Algorithm

### Explanation

The function relies on a **static variable** that stores the data that was read from the file descriptor but not yet returned to the caller (the "leftover" or "stash"). A static variable keeps its value between calls, which is what allows the function to "remember" where it stopped.

Each call to `get_next_line(fd)` follows these steps:

1. **Read and accumulate**: while the stash does not contain a `\n` and the end of the file has not been reached, call `read(fd, buffer, BUFFER_SIZE)` and append the content of the buffer to the stash.
2. **Extract the line**: once a `\n` is found (or the end of the file is reached), copy everything from the start of the stash up to and including the `\n` into a new string. This is the line that is returned.
3. **Update the stash**: keep only what comes after the `\n` for the next call, and free the rest.
4. **Return** the extracted line. If the stash is empty and `read()` returns `0`, free everything and return `NULL`. If `read()` returns `-1`, free everything and return `NULL`.

For the **bonus**, the single static variable is an **array of stashes indexed by file descriptor** (e.g. `static char *stash[FOPEN_MAX]`), so each open file keeps its own independent reading state.

### Justification

- **Static stash**: it keeps data between calls without using a global variable, and it ensures that no character is lost or read twice even when `read()` returns more than one line.
- **Reading by chunks of `BUFFER_SIZE`**: calling `read()` once per character would be very slow, so reading by blocks reduces the number of system calls. Because the stash accumulates the data, the result is the same whatever the value of `BUFFER_SIZE` (from `1` to very large values).
- **Stopping as soon as a `\n` is found**: the function never reads more of the file than needed, which keeps it efficient and allows it to work with standard input and large files.
- **Array indexed by fd (bonus)**: it gives direct access to the state of any file descriptor in constant time, without needing to browse a list, and respects the "one static variable" constraint.
- **Careful memory handling**: every intermediate string is freed as soon as it is no longer needed, and everything is freed on end of file or error, to avoid memory leaks.

## Resources

### References

- `man 2 read`, `man 2 open`, `man 2 close`
- `man 3 malloc`, `man 3 free`
- [File descriptors (Wikipedia)](https://en.wikipedia.org/wiki/File_descriptor)
- [Static variables in C (GeeksforGeeks)](https://www.geeksforgeeks.org/static-variables-in-c/)
- [Valgrind documentation](https://valgrind.org/docs/manual/manual.html)
- 42 get_next_line subject (PDF)

### Use of AI

AI was used as a **support tool** for this project:

- **Understanding concepts**: explanations about static variables, file descriptors and how `read()` behaves with different buffer sizes.
- **Test ideas**: suggestions of edge cases to test (empty file, file without a trailing newline, very large/very small `BUFFER_SIZE`, invalid fd, multiple fds for the bonus).
