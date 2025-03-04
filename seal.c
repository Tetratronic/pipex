/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 05:31:40 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/04 05:36:33 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
