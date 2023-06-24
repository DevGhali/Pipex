/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:11:24 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/08 21:07:51 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex_bonus.h"

void	pipex(t_pipex rohr, char **argv, char **envp)
{
	int	pip_ret;

	pip_ret = pipe(rohr.ends);
	if (pip_ret == -1)
		perror1(ERR_PIPE);
	rohr.pid = fork();
	if (rohr.pid < 0)
		perror1(ERR_FORK);
	if (rohr.pid == 0)
	{
		close(rohr.ends[0]);
		dup2(rohr.ends[1], STDOUT_FILENO);
		exec(argv[rohr.cmd_index], envp);
	}
	else
	{
		waitpid(rohr.pid, 0, WNOHANG);
		close(rohr.ends[1]);
		dup2(rohr.ends[0], STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	rohr;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 9) && argc > 6))
		perror1(ERR_ARG);
	rohr.x = 0;
	if (!ft_strncmp(argv[1], "here_doc", 9) && argc == 6)
	{
		here_doc(argv[2], &rohr);
		openn_heredoc(&rohr, argv, argc);
		rohr.cmd_index = 3;
	}
	else
	{
		openn(&rohr, argv, argc);
		rohr.cmd_index = 2;
	}
	while (rohr.cmd_index < (argc - 2))
	{
		pipex(rohr, argv, envp);
		rohr.cmd_index++;
	}
	dup2(rohr.outfile, STDOUT_FILENO);
	exec(argv[argc - 2], envp);
	return (0);
}
