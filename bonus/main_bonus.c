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

#include "pipex_bonus.h"

static void	redirect_io(char **cmd, char ***params, t_vars *vars)
{
	if (dup2(vars->curr_in, STDIN_FILENO) < 0
		|| dup2(vars->curr_out, STDOUT_FILENO) < 0)
	{
		full_clean(cmd, params, vars, 1);
		free(vars->pipes);
		free(vars->hd_name);
		exit(1);
	}
}

static int	last_status(pid_t lastpid)
{
	int		status;
	int		exitcode;

	status = 0;
	exitcode = 0;
	waitpid(lastpid, &status, 0);
	if (WIFEXITED(status))
		exitcode = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		;
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
			return (perror("malloc"), full_clean(&cmd, &params, vars, 1),
				free(vars->pipes), free(vars->hd_name), exit(127), -1);
		prepare_execution(&cmd, &params, vars);
		execve(cmd, params, env);
		perror(cmd);
		full_clean(&cmd, &params, vars, 0);
		free(vars->pipes);
		free(vars->hd_name);
		exit(127);
	}
	else if (pid == -1)
		return (close_fds(vars), free(vars->pipes), free(vars->hd_name),
			exit(1), pid);
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;
	int		i;
	pid_t	last;

	if (argc < 5)
		return (ft_putendl_fd("Invalid arguments !", 2), 1);
	if (argc >= 6 && !ft_strncmp("here_doc", argv[1], 9))
		heredoc_io(argv++, &vars, argc--);
	else
		initialize_io(argv, &vars, argc);
	init_pipes(&vars, argc);
	i = -1;
	while (++i < argc - 3)
	{
		vars.curr_in = vars.pipes[i * 2];
		vars.curr_out = vars.pipes[i * 2 + 1];
		last = exec_process(&vars, argv, env, i);
	}
	close_fds(&vars);
	free(vars.pipes);
	vars.pipes = NULL;
	if (access(vars.hd_name, F_OK) == 0)
		unlink(vars.hd_name);
	free(vars.hd_name);
	return (last_status(last));
}
