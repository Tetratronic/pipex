/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:38:35 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/10 00:25:02 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	file_id(t_vars *vars)
{
	char			*id;
	char			*filename;
	int				rand;
	unsigned long	hash;

	rand = 1337;
	hash = (unsigned long)&rand;
	hash %= 2147483647;
	id = ft_itoa((int)hash);
	if (!id)
		exit(2);
	filename = ft_strjoin("/tmp/.heredoc_", id);
	if (!filename)
		exit (2);
	free(id);
	vars->hd_name = filename;
}

static void	get_input(char *delim, t_vars *vars)
{
	char	*line;
	size_t	delim_len;
	char	*del;

	del = ft_strjoin(delim, "\n");
	if (!del)
		return ;
	delim_len = ft_strlen(del);
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0, 0);
		if (!line || ft_strncmp(line, del, delim_len) == 0)
		{
			get_next_line(0, 1);
			free(line);
			break ;
		}
		ft_putstr_fd(line, vars->infile);
		free(line);
	}
	close(vars->infile);
	vars->infile = open(vars->hd_name, O_RDONLY, 0644);
	free(del);
}

void	heredoc_io(char **argv, t_vars *vars, int argc)
{
	file_id(vars);
	vars->infile = open(vars->hd_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	vars->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (vars->infile < 0 || vars->outfile < 0)
	{
		if (vars->infile < 1)
		{
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(2), 2);
			ft_putstr_fd("\n", 2);
		}
		if (vars->outfile < 1)
		{
			if (vars->infile > 0)
				close(vars->infile);
			perror(argv[argc - 1]);
		}
	}
	get_input(argv[2], vars);
}
