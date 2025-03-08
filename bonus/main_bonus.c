/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:15:39 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/08 00:00:22 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static int	last_status(pid_t lastpid)
{
	int		status;
	int		exitcode;

	status = 0;
	exitcode = 0;
	while (waitpid(lastpid, &status, 0) >= 0)
	{
		if (WIFEXITED(status))
			exitcode = WEXITSTATUS(status);
	}
	return ((int)exitcode);
}

static void	prepare_execution(char **cmd, char ***params, t_vars *vars)
{
	redirect_io(cmd, params, vars);
	trim_quotes(*params);
	close_fds(vars);
}

static pid_t	exec_process(t_vars *vars, char **argv, char **env, int index)
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
		if (!cmd || !params)
			return (perror("malloc"), full_clean(&cmd, &params, vars),
				free(vars->pipes), exit(127), -1);
		prepare_execution(&cmd, &params, vars);
		execve(cmd, params, env);
		perror(cmd);
		full_clean(&cmd, &params, vars);
		free(vars->pipes);
		vars->pipes = NULL;
		exit(127);
	}
	else if (pid == -1)
		return (close_fds(vars), free(vars->pipes), exit(1), pid);
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;
	int		i;
	int		k;
	pid_t	last;

	if (argc < 5)
		return (ft_putendl_fd("Invalid arguments !", 2), 1);
	initialize_io(argv, &vars, argc);
	init_pipes(&vars, argc);
	i = 0;
	k = 0;
	while (i < argc - 3)
	{
		vars.curr_in = vars.pipes[k];
		vars.curr_out = vars.pipes[k + 1];
		last = exec_process(&vars, argv, env, i);
		k += 2;
		i++;
	}
	close_fds(&vars);
	free(vars.pipes);
	vars.pipes = NULL;
	return (last_status(last));
}
