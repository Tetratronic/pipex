/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:56:57 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/04 19:56:58 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	count_words(char *str)
{
	int	result;

	result = 0;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;;
		if (ft_isalpha(*str))
			result++;
		if (*str && (*str == '\'' || *str == '\"'))
		{
			skip(&(*str));
			result++;
		}
		while (*str && ft_isalpha(*++str))
			;
	}
	return (result);
}

static char	*get_word(const char *s)
{
	size_t	len;
	char	*result;

	if (!s)
		return (NULL);
	len = 0;
	if (s[len] == '\'' || s[len] == '\"')
		return (get_quoted_content(&s[len]))
	while (s[len] && s[len] != ' ')
		len++;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != ' ')
	{
		result[len] = s[len];
		len++;
	}
	result[len] = '\0';
	return (result);
}

char	**tokenize(char *params)
{
	char	**result;
	size_t	count;
	size_t	i;
	size_t	j;
	
	count = count_words(params);
	result = (char **)malloc((count + 1) * sizeof((char *)));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < count)
	{
		while (params[j] && params[j] == ' ')
			j++;
		result[i] = get_word(&params[j]);
		if (!result[i])
			return (abort_split(result, i));
		if (params[j] == '\'' || params[j] == '\"')
			skip(&j);
		while (params[j] && params[j] != ' ')
			j++;
	}
	result[count] = NULL;
	return (result);
}

