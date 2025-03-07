/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:38:35 by abenkaro          #+#    #+#             */
/*   Updated: 2025/02/26 18:21:46 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize_io(char **argv, t_vars *vars, int argc)
{
	vars->infile = open(argv[1], O_RDONLY);
	vars->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (vars->infile < 0 || vars->outfile < 0)
	{
		if (vars->infile < 1)
		{
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(2), 2);
			ft_putstr_fd("\n", 2);
			if (vars->outfile > 0)
				close(vars->outfile);
		}
		if (vars->outfile < 1)
		{
			if (vars->infile > 0)
				close(vars->infile);
			perror(argv[argc - 1]);
		}
		exit(2);
	}
}

void	init_pipes(t_vars *vars, int argc)
{
	int	pipefd[2];
	int	i;
	int	cmds;

	cmds = (argc - 3) * 2;
	vars->pipes = (int *)malloc(cmds * sizeof(int));
	if (!vars->pipes)
		exit(1);
	ft_memset(vars->pipes, -1, cmds * sizeof(int));
	vars->pipes[0] = vars->infile;
	vars->pipes[cmds - 1] = vars->outfile;
	i = 1;
	while (i <= cmds / 2)
	{
		if (pipe(pipefd) < 0)
		{
			close_fds(vars);
			free(vars->pipes);
			vars->pipes = NULL;
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		vars->pipes[i] = pipefd[1];
		vars->pipes[i + 1] = pipefd[0];
		i += 2;
	}
}
