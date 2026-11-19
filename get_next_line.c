/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-hou <soel-hou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 11:49:01 by soel-hou          #+#    #+#             */
/*   Updated: 2026/11/18 13:00:52 by soel-hou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	update_reminder(char **reminder, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(*reminder, buffer);
	if (temp == NULL)
		return (0);
	free(*reminder);
	*reminder = temp;
	return (1);
}

static ssize_t	read_to_reminder(int fd, char **reminder, char *buffer)
{
	ssize_t	reader;

	reader = 1;
	while ((*reminder == NULL || ft_strchr(*reminder, '\n') == NULL)
		&& reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		if (reader < 0)
			return (-1);
		buffer[reader] = '\0';
		if (reader > 0 && update_reminder(reminder, buffer) == 0)
			return (-1);
	}
	return (reader);
}

static char	*extract_line(char *reminder)
{
	char	*result;
	char	*newline;
	size_t	len;

	newline = ft_strchr(reminder, '\n');
	if (newline != NULL)
		len = newline - reminder + 1;
	else
		len = ft_strlen(reminder);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, reminder, len + 1);
	return (result);
}

static int	update_reminder_after_line(char **reminder)
{
	char	*newline;
	char	*temp;

	newline = ft_strchr(*reminder, '\n');
	if (newline == NULL)
	{
		free(*reminder);
		*reminder = NULL;
		return (1);
	}
	temp = ft_strdup(newline + 1);
	if (temp == NULL)
		return (0);
	free(*reminder);
	if (temp[0] == '\0')
	{
		free(temp);
		*reminder = NULL;
	}
	else
		*reminder = temp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	if (read_to_reminder(fd, &reminder, buffer) == -1)
		return (free(reminder), reminder = NULL, free(buffer), NULL);
	if (reminder == NULL || reminder[0] == '\0')
		return (free(reminder), reminder = NULL, free(buffer), NULL);
	result = extract_line(reminder);
	if (result == NULL)
		return (free(buffer), NULL);
	if (update_reminder_after_line(&reminder) == 0)
	{
		free(result);
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (result);
}
