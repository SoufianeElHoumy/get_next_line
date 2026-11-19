#include "get_next_line.h"

static int	update_chyata(**chyata, *buffer)
{
	char *temp;

	temp = ft_strjoin(*chyata, buffer)
	if (temp == NULL)
		return (NULL);
	free(*chyata);
	*chyata = temp;
	return (1);
}

static ssize_t	read_to_chyata(fd, **chyata, *buffer)
{
	ssize_t reader;

	reader = 1;
	while (*chyata == NULL || ft_strchr(*chyata, '\n') && reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader < 0)
			return (-1);
		buffer[reader] = '\0';
		if (reader > 0 && update_chyata(chyata, buffer) == 0)
			return (-1);
	}
	return (reader);
}

static char	*extract_line(*chyata)
{
	char	*result;
	char	*newline;
	size_t	len;

	newline = ft_strchr(chyata, '\n');
	if (newline != NULL)
		len = newline - chyata + 1;
	else
		len = ft_strlen(chyata);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, chyata, len + 1);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*chyata;
	char		*result;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE + 1)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	if (read_to_chyata(fd, &chyata, buffer) == -1)
		return (free(chyata), chyata = NULL, free(buffer), NULL);
	if (result == NULL || chyata[0] = '\0')
		return (free(chyata), chyata = NULL, free(buffer), NULL);
	result = extract_line(chyata);
}