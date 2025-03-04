/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:54:48 by abenkaro          #+#    #+#             */
/*   Updated: 2025/02/26 18:12:03 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>

typedef struct s_vars {
	int	pipe[2];
	int	curr_in;
	int	curr_out;
	int	infile;
	int	outfile;
}			t_vars;

void	initialize_io(char **argv, t_vars *vars);
void	init_pipe(int *pipe);
void	close_fds(int fd1, int fd2, int fd3, int fd4);
char	*abs_path(char *arg, char **env);
void	clean2darr(char ***arr);
void	seal(char *params);
void	unseal(char **params);

#endif
