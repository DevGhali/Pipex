/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 01:09:32 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/13 13:53:39 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr[i])
	{
		while (arr[i])
		{
			if (arr[i] != NULL)
				free(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	first_child(t_pipex *pipee, char **argv, char **envp)
{
	dup2(pipee->fds[1], STDOUT_FILENO);
	dup2(pipee->infile, STDIN_FILENO);
	close(pipee->fds[0]);
	exec(pipee, argv[2], envp);
}

void	second_child(t_pipex *pipee, char **argv, char **envp)
{
	dup2(pipee->fds[0], STDIN_FILENO);
	dup2(pipee->outfile, STDOUT_FILENO);
	close(pipee->fds[1]);
	exec(pipee, argv[3], envp);
}

void	perror_exit1(t_pipex *pipee, char *error)
{
	if (pipee->outfile >= 0)
		close(pipee->outfile);
	if (pipee->infile >= 0)
		close(pipee->infile);
	perror(error);
	exit(1);
}

void	perror_exit0(t_pipex *pipee, char *error)
{
    if (pipee->outfile != -1)
        write(pipee->outfile, "       0\n", 9);
	if (pipee->outfile >= 0)
		close(pipee->outfile);
	if (pipee->infile >= 0)
		close(pipee->infile);
	write(STDERR_FILENO, "pipex: ", 7);
	perror(error);
	exit(0);
}
