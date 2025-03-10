/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:48:08 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/09 22:52:11 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
