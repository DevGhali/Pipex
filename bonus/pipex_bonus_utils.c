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

void	openn(t_pipex *rohr, char **argv, int argc)
{
	rohr->outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (rohr->outfile < 0)
		perror0(argv[argc - 1], -1);
	rohr->infile = open(argv[1], O_RDONLY);
	if (rohr->infile < 0)
		perror0(argv[1], rohr->outfile);
	dup2(rohr->infile, STDIN_FILENO);
}

void	freee(char **str)
{
	size_t	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void	perror0(char *msg, int fd)
{
	if (fd != -1)
		write(fd, "       0\n", 9);
	write(STDERR_FILENO, "pipex: ", 7);
	perror(msg);
	exit(0);
}

void	perror1(char *msg)
{
	perror(msg);
	exit(1);
}

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
