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

char	**split_string(t_pipex rohr, int i, int j, int k)
{
	while (rohr.cmd[i] != '\0')
	{
		if (decider(rohr.cmd[i], rohr.quote) == 1)
		{
			rohr.quote = helper_quote(rohr.quote, rohr.cmd[i], &i);
			continue ;
		}
		if (decider(rohr.cmd[i], rohr.quote) == 0)
		{
			if (j > 0)
			{
				rohr.result[k][j] = '\0';
				k++;
				rohr.result[k] = malloc(ft_strlen(rohr.cmd) * sizeof(char));
				j = 0;
			}
		}
		else
			rohr.result[k][j++] = rohr.cmd[i];
		i++;
	}
	if (j > 0)
		rohr.result[k++][j] = '\0';
	rohr.result[k] = NULL;
	return (rohr.result);
}

char	*find_cmd_path(char *cmd, char **envp, t_pipex *rohr)
{
	size_t	i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	if (envp[i] == NULL)
		rohr->splitted_paths = ft_split(ENV_PATH, ':');
	else
	{
		while (ft_strncmp(envp[i], "PATH=", 5) != 0)
			i++;
		rohr->splitted_paths = ft_split(envp[i] + 5, ':');
	}
	i = 0;
	while (rohr->splitted_paths[i])
	{
		rohr->splitted_paths[i] = ft_strjoin(rohr->splitted_paths[i], "/");
		rohr->cmd_path = ft_strjoin(rohr->splitted_paths[i], cmd);
		if (access(rohr->cmd_path, F_OK) == 0)
			return (rohr->cmd_path);
		free(rohr->cmd_path);
		i++;
	}
	freee(rohr->splitted_paths);
	return (NULL);
}

void	exec(char *cmd, char **envp)
{
	t_pipex	rohr;

	if (!check_quotes(cmd))
		perror1("command not found");
	rohr.cmd = cmd;
	rohr.quote = '\0';
	rohr.result = malloc((ft_strlen(rohr.cmd) / 2 + 1) * sizeof(char *));
	rohr.result[0] = (char *)malloc(ft_strlen(rohr.cmd) * sizeof(char));
	rohr.cmd_splitted = split_string(rohr, 0, 0, 0);
	rohr.cmd_path = find_cmd_path(rohr.cmd_splitted[0], envp, &rohr);
	if (!rohr.cmd_path)
	{
		write(STDERR_FILENO, ERR_MSG, 7);
		ft_putstr_fd(rohr.cmd_splitted[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (execve(rohr.cmd_path, rohr.cmd_splitted, envp) < 0)
		perror1(ERR_EXECVE);
}
