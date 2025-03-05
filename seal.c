/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkaro <abenkaro@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:53:44 by abenkaro          #+#    #+#             */
/*   Updated: 2025/03/04 21:59:31 by abenkaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void unseal(char *params)
{
    int i = 0;
    
    while (params[i])
    {
        if (params[i] == '\x1F')
            params[i] = ' ';
        i++;
    }
}

void trim_quotes(char **params)
{
    char *temp;
    
    while (*params)
    {
        if (**params == '\'' || **params == '\"')
        {
            temp = ft_strtrim(*params, "\'\"");
            if (!temp)
                exit(1);
            free(*params);
            *params = temp;
        }
		unseal(*params);
        params++;
    }
}

void seal(char *params)
{
    int i = 0;
    int in_quotes = 0;
    
    while (params[i])
    {
        if (params[i] == '\'' || params[i] == '\"')
            in_quotes = !in_quotes;
        if (in_quotes && params[i] == ' ')
            params[i] = '\x1F';
        i++;
    }
}

