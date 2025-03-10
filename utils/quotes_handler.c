/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 00:51:05 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/09 22:52:14 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	expose_spaces(char *params)
{
	int	i;

	i = 0;
	while (params[i])
	{
		if (params[i] == '\x1F')
			params[i] = ' ';
		i++;
	}
}

void	trim_quotes(char **params)
{
	char	*temp;

	while (*params)
	{
		if (**params == '\'' || **params == '\"')
		{
			temp = ft_strtrim(*params, "\'\"");
			if (!temp)
				return (expose_spaces(*params));
			free(*params);
			*params = temp;
		}
		expose_spaces(*params);
		params++;
	}
}

void	hide_spaces(char *params)
{
	int	i;
	int	in_quotes;
	int	in_dquotes;

	in_quotes = 0;
	in_dquotes = 0;
	i = 0;
	while (params[i])
	{
		if (params[i] == '\'')
			in_quotes = !in_quotes;
		if (in_quotes && params[i] == ' ')
			params[i] = '\x1F';
		else if (params[i] == '\"')
			in_dquotes = !in_dquotes;
		if (in_dquotes && params[i] == ' ')
			params[i] = '\x1F';
		i++;
	}
}
