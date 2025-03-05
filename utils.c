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

char	*fetch_path(char *cmd, char **env)
{
	static char	**possible_paths;
	int			i;
	char		*fullcmd;
	char		*temp;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			possible_paths = ft_split((&(*(env[i])) + 5), ':');
			break ;
		}
	}
	i = -1;
	if (!possible_paths)
		return (ft_strdup(cmd));
	while (possible_paths[++i])
	{
		temp = ft_strjoin(possible_paths[i], "/");
		fullcmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(fullcmd, X_OK) == 0)
			return (clean2darr(&possible_paths), fullcmd);
		free(fullcmd);
	}
	return (clean2darr(&possible_paths), ft_strdup(cmd));
}

char	*abs_path(char *arg, char **env)
{
	char	**cmd;
	char	*name;
	char	*fullname;

	cmd = ft_split(arg, ' ');
	if (!cmd || !*cmd)
	{
		if(cmd)
			clean2darr(&cmd);
		return (ft_strdup(arg));
	}
	trim_quotes(cmd);
	name = cmd[0];
	if (ft_strchr(name, '/') == NULL)
	{
		fullname = fetch_path(name, env);
		clean2darr(&cmd);
		return (fullname);
	}
	fullname = ft_strdup(name);
	clean2darr(&cmd);
	return (fullname);
}
