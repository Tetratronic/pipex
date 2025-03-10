/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:54:48 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/09 22:51:15 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>

typedef struct s_vars {
	int		*pipes;
	int		curr_in;
	int		curr_out;
	int		infile;
	int		outfile;
	char	*hd_name;
}			t_vars;

void	initialize_io(char **argv, t_vars *vars, int argc);
void	init_pipes(t_vars *vars, int argc);
void	close_fds(t_vars *vars);
char	*find_cmd(char *arg, char **env);
void	clean2darr(char ***arr);
void	hide_spaces(char *params);
void	expose_spaces(char *params);
void	trim_quotes(char **params);
void	full_clean(char **cmd, char ***params, t_vars *vars, int mode);

#endif
