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

static void	full_clean(char **cmd, char ***params, t_vars *vars)
{
	if (*cmd)
		free(*cmd);
	*cmd = NULL;
	if (*params)
		clean2darr(params);
	*params = NULL;
	close_fds(vars);
}

static void	redirect_io(char **cmd, char ***params, t_vars *vars)
{
	if (dup2(vars->curr_in, STDIN_FILENO) < 0
		|| dup2(vars->curr_out, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		full_clean(cmd, params, vars);
		exit(1);
	}
}

static int	last_status(void)
{
	int	status;
	int	last;

	status = 0;
	last = 0;
	while (wait(&status) >= 0)
		if (WIFEXITED(status))
			last = WEXITSTATUS(status);
	return (last);
}

static void	exec_process(t_vars *vars, char **argv, char **env, int index)
{
	char	*cmd;
	char	**params;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		cmd = find_cmd(argv[2 + index], env);
		hide_spaces(argv[2 + index]);
		params = ft_split(argv[2 + index], ' ');
		if (!cmd || !params || !0[params])
			return (full_clean(&cmd, &params, vars), exit(127));
		redirect_io(&cmd, &params, vars);
		close_fds(vars);
		trim_quotes(params);
		execve(cmd, params, env);
		perror(cmd);
		full_clean(&cmd, &params, vars);
		exit(127);
	}
	else if (pid == -1)
		return (perror("fork"), close_fds(vars), exit(1));
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;
	int		i;

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
	close_fds(&vars);
	return (last_status());
}
