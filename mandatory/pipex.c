/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:27:11 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/24 17:03:10 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	pipex(t_pipex pipee, char **argv, char **envp)
{
	if (pipe(pipee.fds) < 0)
		perror11(ERR_PIPE);
	pipee.pid = fork();
	if (pipee.pid == -1)
		perror11(ERR_FORK);
	if (pipee.pid == 0)
		child(pipee, argv, envp);
	else
	{
		waitpid(pipee.pid, NULL, 1);
		pipee.pid2 = fork();
		if (pipee.pid2 == 0)
			parent(pipee, argv, envp);
		waitpid(pipee.pid2, NULL, 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipee;

	if (argc != 5)
		perror11(ERR_ARGC);
	pipee.outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (pipee.outfile < 0)
		perror00(argv[4]);
	pipee.infile = open(argv[1], O_RDONLY);
	if (pipee.infile < 0)
	{
		if (pipee.outfile != -1)
			write(pipee.outfile, "       0\n", 9);
		perror00(argv[1]);
	}
	pipex(pipee, argv, envp);
	return (0);
}
