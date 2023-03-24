/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 01:09:32 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/03/18 21:35:06 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 
**	function that frees an array of strings including string inside
*/
void	freee(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	child(t_pipex pipee, char **argv, char **envp)
{
	dup2(pipee.fds[1], STDOUT_FILENO);
	dup2(pipee.infile, STDIN_FILENO);
	close(pipee.fds[0]);
	exec(argv[2], envp);
}

void	parent(t_pipex pipee, char **argv, char **envp)
{
	dup2(pipee.fds[0], STDIN_FILENO);
	dup2(pipee.outfile, STDOUT_FILENO);
	close(pipee.fds[1]);
	exec(argv[3], envp);
}

/* 
**	print the error to STDERR and exits with 1
*/
void	perror1(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

/* 
**	print the error to STDERR and exits with 0
*/
void	perror0(char *error)
{
	perror(ft_strjoin(ERR_MSG, error));
	exit(EXIT_SUCCESS);
}
