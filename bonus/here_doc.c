/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:39:31 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/08 22:08:05 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex_bonus.h"

void	here_doc(char *limiter, t_pipex *rohr)
{
	char	*buf;

	rohr->infile = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (rohr->infile < 0)
		perror1(ERR_HEREDOC);
	while (1)
	{
		write(1, ERR_HEREDOC, 9);
		buf = get_next_line(STDIN_FILENO);
		if (buf < 0)
			exit(1);
		if (!ft_strncmp(limiter, buf, ft_strlen(limiter)))
			break ;
		write(rohr->infile, buf, ft_strlen(buf));
		write(rohr->infile, "\n", 1);
		free(buf);
	}
	free(buf);
	close(rohr->infile);
	rohr->infile = open(".heredoc", O_RDONLY);
	if (rohr->infile < 0)
	{
		unlink(".heredoc");
		perror0(ERR_HEREDOC, -1);
	}
}

void	openn_heredoc(t_pipex *rohr, char **argv, int argc)
{
	rohr->outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (rohr->outfile < 0)
		perror0(argv[argc - 1], rohr->outfile);
	dup2(rohr->infile, STDIN_FILENO);
}
