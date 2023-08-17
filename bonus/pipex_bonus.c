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

void	pipex(t_pipex *pipee, char **argv, int argc, char **envp)
{
	if (pipe(pipee->fds) < 0)
		perror_exit1(pipee, ERR_PIPE);
	pipee->pid = fork();
	if (pipee->pid == -1)
		perror_exit1(pipee, ERR_FORK);
	if (pipee->pid == 0)
	{
        close(pipee->fds[0]);
        dup2(pipee->fds[1], STDOUT_FILENO);
        exec_bonus(pipee, argv[pipee->cmd_index], envp);
    }
	else
	{
        waitpid(pipee->pid, 0, 0);
        close(pipee->fds[1]);
        dup2(pipee->fds[0], STDIN_FILENO);
    }
}

static  void    open_files(t_pipex *pipee, char **argv, int argc)
{
    pipee->outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0664);
    if (pipee->outfile < 0)
        perror_exit0(pipee,argv[argc - 1], -1);
    pipee->infile = open(argv[1], O_RDONLY);
    if (pipee->infile < 0)
        perror_exit0(pipee,argv[1], pipee->outfile);
    dup2(pipee->infile, STDIN_FILENO);
    pipee->cmd_index = 2;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipee;
    int last_cmd;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 9) && argc > 6))
		perror_exit1(&pipee,ERR_ARG);
	if (!ft_strncmp(argv[1], "here_doc", 9) && argc == 6)
		here_doc(argv[2], &pipee, argv, argc);
	else
		open_files(&pipee, argv, argc);
    last_cmd = argc - 2;
    while(last_cmd > 1)
        initialize_struct(&pipee, argv[last_cmd--], envp, 1);
    while (pipee.cmd_index < (argc - 2))
	{
        pipex(&pipee, argv, argc, envp);
        pipee.cmd_index++;
	}
	dup2(pipee.outfile, STDOUT_FILENO);
	exec_bonus(&pipee, argv[argc - 2], envp);
	return (0);
}
