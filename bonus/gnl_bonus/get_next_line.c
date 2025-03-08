/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:34:11 by abenkaro          #+#    #+#             */
/*   Updated: 2025/01/30 10:43:50 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *remainder)
{
	char	*line;
	size_t	i;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update(char *line, char **remainder, char **buffer)
{
	size_t	i;
	size_t	nl_index;
	char	*new_remainder;

	clean(buffer);
	if (!line)
		return (clean(remainder));
	i = 0;
	nl_index = gnl_strlen(line);
	new_remainder = malloc(gnl_strlen(*remainder) - nl_index + 1);
	if (!new_remainder)
		return (clean(remainder));
	while ((*remainder)[nl_index] != '\0')
		new_remainder[i++] = (*remainder)[nl_index++];
	new_remainder[i] = '\0';
	clean(remainder);
	return (new_remainder);
}

void	fill(char **remainder, char *buffer)
{
	char	*tmp;

	tmp = gnl_strjoin(*remainder, buffer);
	free(*remainder);
	*remainder = tmp;
}

char	*check_last(int bytes, char **remainder, char **buffer)
{
	char	*tmp;

	if (bytes == 0 && *remainder && **remainder)
	{
		tmp = gnl_strdup(*remainder);
		clean(remainder);
		clean(buffer);
		return (tmp);
	}
	clean(remainder);
	clean(buffer);
	return (NULL);
}

char	*get_next_line(int fd, int stop)
{
	static char	*remainder;
	char		*line;
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || (size_t)BUFFER_SIZE > MAX)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer || stop)
		return (clean(&remainder), clean(&buffer));
	while (1)
	{
		if (remainder && gnl_strchr(remainder, '\n'))
		{
			line = extract_line(remainder);
			remainder = update(line, &remainder, &buffer);
			return (line);
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes >= 0)
			buffer[bytes] = '\0';
		if (bytes <= 0)
			return (check_last(bytes, &remainder, &buffer));
		fill(&remainder, buffer);
	}
}
