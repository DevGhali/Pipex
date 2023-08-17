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

static  void    open_heredoc(t_pipex *pipee, char **argv, int argc)
{
    pipee->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND , 0664);
    if (pipee->outfile < 0)
        perror_exit0(pipee, argv[argc - 1], pipee->outfile);
    dup2(pipee->infile, STDIN_FILENO);
    pipee->cmd_index = 3;
}

void	here_doc(char *limiter, t_pipex *pipee, char **argv, int argc)
{
	char	*buf;

    open_heredoc(pipee, argv, argc);
	pipee->infile = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipee->infile < 0)
		perror_exit1(pipee, ERR_HEREDOC);
	while (1)
	{
		write(1, ERR_HEREDOC, 9);
		buf = get_next_line(STDIN_FILENO);
		if (buf < 0)
			exit(1);
		if (!ft_strncmp(limiter, buf, ft_strlen(limiter)))
			break ;
		write(pipee->infile, buf, ft_strlen(buf));
		write(pipee->infile, "\n", 1);
		free(buf);
	}
	free(buf);
	close(pipee->infile);
	pipee->infile = open(".heredoc", O_RDONLY);
	if (pipee->infile < 0)
	{
		unlink(".heredoc");
		perror_exit0(pipee, ERR_HEREDOC, -1);
	}
}
