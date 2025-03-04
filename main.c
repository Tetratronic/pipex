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

void	send_child(t_vars vars, char **argv, char **env, int index)
{
	if (fork() == 0)
	{
		int		j;
		char	*cmd;
		char	**params;
	
		cmd = abs_path(argv[2 + index], env);
		params = ft_split(argv[2 + index], ' ');
		if (!cmd || !params || !0[params])
		{
			ft_putstr_fd("Command not found", 2);
			j = 0;
			while (params[j])
				free(params[j++]);
			free(params);
			free(cmd);
			exit(127);
		}
		if (dup2(vars.curr_in, STDIN_FILENO) < 0 || dup2(vars.curr_out, STDOUT_FILENO) < 0)
			perror("dup2");
		close_fds(vars.pipe[0], vars.pipe[1], vars.infile, vars.outfile);
		execve(cmd, params, env);
		perror("execve");
		free(cmd);
		j = 0;
		while (params[j])
			free(params[j++]);
		free(params);
		if (vars.curr_out == vars.outfile)
			exit(127);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;
	int		i;

	if (argc != 5)
		return(ft_putendl_fd("Not Enough Arguments", 2), 1);
	initialize_io(argv, &vars);
	init_pipe(vars.pipe);
	i = -1;
	vars.curr_in = vars.infile;
	vars.curr_out = vars.pipe[1];
	while (++i < 2)
	{
		send_child(vars, argv, env, i);
		vars.curr_in = vars.pipe[0];
		vars.curr_out = vars.outfile;
	}
	close_fds(vars.pipe[0], vars.pipe[1], vars.infile, vars.outfile);
	while(wait(NULL) >= 0)
		;
	return (0);
}
