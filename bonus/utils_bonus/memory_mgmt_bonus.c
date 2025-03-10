/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mgmt_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:48:08 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/10 04:02:41 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"

void	free_hd(char **hd)
{
	if (*hd)
	{
		free(*hd);
		*hd = NULL;
	}
	hd = NULL;
}

void	clean2darr(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

void	full_clean(char **cmd, char ***params, t_vars *vars, int mode)
{
	if (*cmd)
		free(*cmd);
	*cmd = NULL;
	if (*params)
		clean2darr(params);
	*params = NULL;
	if (mode)
		close_fds(vars);
}
