/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 02:04:23 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/12 20:13:56 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

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

char	**split_string(t_pipex pipee, int i, int j, int k)
{
	while (pipee.cmd[i] != '\0')
	{
		if (decider(pipee.cmd[i], pipee.quote) == 1)
		{
			pipee.quote = helper_quote(pipee.quote, pipee.cmd[i], &i);
			continue ;
		}
		if (decider(pipee.cmd[i], pipee.quote) == 0)
		{
			if (j > 0)
			{
				pipee.result[k][j] = '\0';
				k++;
				pipee.result[k] = malloc(ft_strlen(pipee.cmd) * sizeof(char));
				j = 0;
			}
		}
		else
			pipee.result[k][j++] = pipee.cmd[i];
		i++;
	}
	if (j > 0)
		pipee.result[k++][j] = '\0';
	pipee.result[k] = NULL;
	return (pipee.result);
}

char	*find_cmd_path(char *cmd, char **envp, t_pipex *pipee)
{
	size_t	i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	if (envp[i] == NULL)
		pipee->splitted_paths = ft_split(ENV_PATH, ':');
	else
	{
		while (ft_strncmp(envp[i], "PATH=", 5) != 0)
			i++;
		pipee->splitted_paths = ft_split(envp[i] + 5, ':');
	}
	i = 0;
	while (pipee->splitted_paths[i])
	{
		pipee->splitted_paths[i] = ft_strjoin(pipee->splitted_paths[i], "/");
		pipee->cmd_path = ft_strjoin(pipee->splitted_paths[i], cmd);
		if (access(pipee->cmd_path, F_OK) == 0)
			return (pipee->cmd_path);
		free(pipee->cmd_path);
		i++;
	}
	freee(pipee->splitted_paths);
	return (NULL);
}

void	exec(char *cmd, char **envp)
{
	t_pipex	pipee;

	if (!check_quotes(cmd))
		perror11("command not found");
	pipee.cmd = cmd;
	pipee.quote = '\0';
	pipee.result = malloc((ft_strlen(pipee.cmd) / 2 + 1) * sizeof(char *));
	pipee.result[0] = (char *)malloc(ft_strlen(pipee.cmd) * sizeof(char));
	pipee.cmd_splitted = split_string(pipee, 0, 0, 0);
	pipee.cmd_path = find_cmd_path(pipee.cmd_splitted[0], envp, &pipee);
	if (!pipee.cmd_path)
	{
		write(STDERR_FILENO, ERR_MSG, 7);
		ft_putstr_fd(pipee.cmd_splitted[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (execve(pipee.cmd_path, pipee.cmd_splitted, envp) < 0)
		perror11(ERR_EXECVE);
}
