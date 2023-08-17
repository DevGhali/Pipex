/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:49:50 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/12 20:16:15 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex_bonus.h"

int	check_quotes(char *cmd)
{
    int	count;
    int	i;

    i = 0;
    count = 0;
    while (cmd[i])
    {
        if (cmd[i] == 34 || cmd[i] == 39)
            count++;
        i++;
    }
    if (count % 2 == 0)
        return (1);
    return (0);
}

char	helper_quote(char quote, char ret, int *i)
{
	(*i)++;
	if (quote == '\0')
		return (ret);
	return ('\0');
}

int	decider(char c, char quote)
{
	if (c == '\'' && quote != '\"')
		return (1);
	if (c == '\"' && quote != '\'')
		return (1);
	if (quote == '\0' && (c == ' ' || c == '\t'))
		return (0);
	return (2);
}


