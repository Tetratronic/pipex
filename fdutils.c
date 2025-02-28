/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:59:53 by abenkaro          #+#    #+#             */
/*   Updated: 2025/02/28 00:59:57 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(int fd1, int fd2, int fd3, int fd4)
{
	int	fd[4];
	int	i;

	fd[0] = fd1;
	fd[1] = fd2;
	fd[2] = fd3;
	fd[3] = fd4;
	i = 0;
	while (i < 4)
	{
		if (fd[i] != -1)
			close(fd[i]);
		i++;
	}
}

char	*abs_path(char *arg)
{
	char	**cmd;
	char	*name;
	int		j;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		exit(-1);
	name = ft_strdup(cmd[0]);
	j = 0;
	while (cmd[j])
		free(cmd[j++]);
	free(cmd);
	if (access(name, X_OK) == 0)
		return (name);
	return (NULL);
}


