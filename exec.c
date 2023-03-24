/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 02:04:23 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/03/18 21:45:02 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_cmd_path(char *cmd, char **envp)
{
	size_t	i;
	char	**splitted_paths;
	char	*cmd_path;

	i = 0;
	if (envp[i] == NULL)
		splitted_paths = ft_split(ENV_PATH, ':');
	else
	{
		while (ft_strncmp(envp[i], "PATH=", 5) != 0)
			i++;
		splitted_paths = ft_split(envp[i] + 5, ':');
	}
	i = 0;
	while (splitted_paths[i])
	{
		splitted_paths[i] = ft_strjoin(splitted_paths[i], "/");
		cmd_path = ft_strjoin(splitted_paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	freee(splitted_paths);
	return (NULL);
}

void	exec(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_splitted;

	cmd_splitted = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(cmd_splitted[0], envp);
	if (!cmd_path)
	{
		write(STDERR_FILENO, ERR_MSG, 7);
		ft_putstr_fd(cmd_splitted[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		freee(cmd_splitted);
		free(cmd_path);
		exit(127);
	}
	if (execve(cmd_path, cmd_splitted, envp) < 0)
		perror1(ERR_EXECVE);
}
