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

static void	full_clean(char **cmd, char ***params, t_vars *vars, int mode)
{
	if (*cmd)
		free(*cmd);
	*cmd = NULL;
	if (*params)
		clean2darr(params);
	*params = NULL;
	if (mode)
		close_fds(vars->pipe[0], vars->pipe[1], vars->infile, vars->outfile);
}

static void	redirect(char **cmd, char ***params, t_vars *vars)
{
	if (dup2(vars->curr_in, STDIN_FILENO) < 0
		|| dup2(vars->curr_out, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		full_clean(cmd, params, vars, 1);
		exit(1);
	}
}

static void	exec_process(t_vars *vars, char **argv, char **env, int index)
{
	char	*cmd;
	char	**params;
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		cmd = abs_path(argv[2 + index], env);
		seal(argv[2 + index]);
		params = ft_split(argv[2 + index], ' ');
		if (!cmd || !params || !0[params])
			return (full_clean(&cmd, &params, vars, 1), exit(127));
		redirect(&cmd, &params, vars);
		close_fds(vars->pipe[0], vars->pipe[1], vars->infile, vars->outfile);
		trim_quotes(params);
		execve(cmd, params, env);
		perror(cmd);
		full_clean(&cmd, &params, vars, 0);
		exit(127);
	}
	else if (pid == -1)
		return (full_clean(&cmd, &params, vars, 1), exit(1));
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;
	int		i;
	int		status;
	int		last;

	status = 0;
	last = 0;
	if (argc != 5)
		return (ft_putendl_fd("Not Enough Arguments", 2), 1);
	initialize_io(argv, &vars);
	init_pipe(&vars);
	i = -1;
	vars.curr_in = vars.infile;
	vars.curr_out = vars.pipe[1];
	while (++i < 2)
	{
		exec_process(&vars, argv, env, i);
		vars.curr_in = vars.pipe[0];
		vars.curr_out = vars.outfile;
	}
	close_fds(vars.pipe[0], vars.pipe[1], vars.infile, vars.outfile);
	while (wait(&status) >= 0)
		if (WIFEXITED(status))
			last = WEXITSTATUS(status);
	return (last);
}
