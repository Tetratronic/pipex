/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:53:44 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/04 21:59:31 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void	**trim_quotes(char **params)
{
	int		j;
	char	*temp;

	while (*params)
	{
		if ((**params == '\'' || **params == '\"'))
		{
			temp = ft_strtrim(*params, "\'\"");
			if (!temp)
				exit(1);
			free(*params);
			*params = temp;
		}
		params++;
	}
	j = 0;
	while ((*params)[j])
	{
		if ((*params)[j] && (*params)[j] == '\x1F')
			(*params)[j] = ' ';
		j++;
	}
}

void	seal(char *params)
{
	int	i;
	
	i = 0;
	while (params[i] && params[i] != '\'')
		i++;
	if (!params[i])
		return ;
	while (params[i] && params[++i] != '\'')
	{
		if (params[i] == ' ')
			params[i] = '\x1F';
	}
}

void	unseal(char **params)
{
	int	j;

	while (*params)
	{
		j = 0;
		while ((*params)[j])
		{
			if ((*params)[j] && (*params)[j] == '\x1F')
				(*params)[j] = ' ';
			j++;
		}
		params++;
	}
}
