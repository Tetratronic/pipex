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

int	initialize_io(char **argv, t_vars *vars)
{
	vars->infile = open(argv[1], O_RDONLY);
	vars->outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (vars->infile < 0 || vars->outfile < 0)
		return (perror("Failed to open I/O files"), 0);
	return (1);
}

void	init_pipe(int *p)
{
	if (pipe(p) < 0)
	{
		perror("failed to make pipe");
		exit(EXIT_FAILURE);
	}
}
