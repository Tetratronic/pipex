/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:48:08 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/04 00:48:09 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean2darr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

void	full_clean(char **cmd, char ***params, t_vars *vars)
{
	if (*cmd)
		free(*cmd);
	*cmd = NULL;
	if (*params)
		clean2darr(params);
	*params = NULL;
	close_fds(vars);
}
