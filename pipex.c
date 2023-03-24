/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:27:11 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/03/17 19:26:31 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipex pipee, char **argv, char **envp)
{
	if (pipe(pipee.fds) < 0)
		perror1(ERR_PIPE);
	pipee.pid = fork();
	if (pipee.pid == -1)
		perror1(ERR_FORK);
	if (pipee.pid == 0)
		child(pipee, argv, envp);
	waitpid(pipee.pid, NULL, WNOHANG);
	parent(pipee, argv, envp);
}

/*
** Main function 
*/
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipee;

	if (argc != 5)
		perror1(ERR_ARGC);
	pipee.outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (pipee.outfile < 0)
		perror1(argv[4]);
	pipee.infile = open(argv[1], O_RDONLY);
	if (pipee.infile < 0)
	{
		if (pipee.outfile != -1)
			write(pipee.outfile, "       0\n", 9);
		perror0(argv[1]);
	}
	pipex(pipee, argv, envp);
	return (0);
}
