/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:15:39 by abenkaro          #+#    #+#             */
/*   Updated: 2025/02/27 23:16:16 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	send_child(t_vars vars, char *cmd, char **params, char **env)
{
	if (fork() == 0)
	{
		if (dup2(vars.curr_in, STDIN_FILENO) < 0 || dup2(vars.curr_out, STDOUT_FILENO) < 0)
			perror("dup2");
		close_fds(vars.pipe[0], vars.pipe[1], vars.infile, vars.outfile);
		execve(cmd, params, env);
		perror("execve");
		if (vars.curr_out == vars.outfile)
			exit(127);
	}
}

void	enough_args(int argc)
{
	if (argc != 5)
	{
		ft_putendl_fd("Not Enough Arguments", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;
	char	*cmd;
	char	**params;
	int		i;
	
	enough_args(argc);
	initialize_io(argv, &vars);
	init_pipe(vars.pipe);
	i = -1;
	vars.curr_in = vars.infile;
	vars.curr_out = vars.pipe[1];
	while (++i < 2)
	{
		cmd = abs_path(argv[2 + i], env);
		params = ft_split(argv[2 + i], ' ');
		send_child(vars, cmd, params, env);
		free(cmd);
		vars.curr_in = vars.pipe[0];
		vars.curr_out = vars.outfile;
	}
	close_fds(vars.pipe[0], vars.pipe[1], vars.infile, vars.outfile);
	while(wait(NULL) >= 0)
		;
	return (0);
}
