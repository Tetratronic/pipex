/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:49:01 by abenkaro          #+#    #+#             */
/*   Updated: 2025/01/30 10:16:54 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(char *s1)
{
	size_t	len;
	char	*result;
	char	*ptr;

	if (!s1)
		return (NULL);
	len = gnl_strlen(s1);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ptr = result;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (result);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*result;
	char	*ptr;
	size_t	total_size;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_strdup(s2));
	if (!s2)
		return (gnl_strdup(s1));
	total_size = gnl_strlen(s1) + gnl_strlen(s2);
	result = malloc(total_size + 1);
	if (!result)
		return (NULL);
	ptr = result;
	while (*s1 != '\0')
		*ptr++ = *s1++;
	while (*s2 != '\0')
		*ptr++ = *s2++;
	*ptr = '\0';
	return (result);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*clean(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}
