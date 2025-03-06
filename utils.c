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

void	close_fds(t_vars *vars)
{
	int	fd[4];
	int	i;

	fd[0] = vars->pipe[0];
	fd[1] = vars->pipe[1];
	fd[2] = vars->infile;
	fd[3] = vars->outfile;
	i = 0;
	while (i < 4)
	{
		if (fd[i] >= 0)
			close(fd[i]);
		i++;
	}
}

static char	**available_paths(char **env)
{
	int		i;
	char	**possible_paths;

	i = -1;
	possible_paths = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			possible_paths = ft_split((&(*(env[i])) + 5), ':');
			break ;
		}
	}
	return (possible_paths);
}

char	*compose_path(char *cmd, char **env)
{
	char	**possible_paths;
	int		i;
	char	*fullcmd;
	char	*temp;

	possible_paths = available_paths(env);
	if (!possible_paths)
		return (ft_strdup(cmd));
	i = -1;
	while (possible_paths[++i])
	{
		temp = ft_strjoin(possible_paths[i], "/");
		fullcmd = ft_strjoin(temp, cmd);
		free(temp);
		temp = NULL;
		if (access(fullcmd, X_OK) == 0)
			return (clean2darr(&possible_paths), fullcmd);
		free(fullcmd);
	}
	clean2darr(&possible_paths); 
	return (ft_strdup(cmd));
}

char	*find_cmd(char *arg, char **env)
{
	char	**cmd;
	char	*name;
	char	*fullpath;

	cmd = ft_split(arg, ' ');
	if (!cmd || !*cmd)
	{
		if (cmd)
			clean2darr(&cmd);
		return (ft_strdup(arg));
	}
	trim_quotes(cmd);
	name = cmd[0];
	if (ft_strchr(name, '/') == NULL)
		fullpath = compose_path(name, env);
	else
		fullpath = ft_strdup(name);
	clean2darr(&cmd);
	return (fullpath);
}
