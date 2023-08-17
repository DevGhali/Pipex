/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:22:46 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/12 20:16:22 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex_bonus.h"

void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	perror_exit1(t_pipex *pipee, char *error)
{
	perror(error);
	exit(1);
}

void	perror_exit0(t_pipex *pipee, char *error, int fd)
{
    if (fd != -1)
        write(fd, "       0\n", 9);
    if (pipee->outfile >= 0)
        close(pipee->outfile);
    if (pipee->infile >= 0)
        close(pipee->infile);
    write(STDERR_FILENO, "pipex: ", 7);
    perror(error);
    exit(0);
}
