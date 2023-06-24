/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:11:33 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/12 20:12:59 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../../libft/libft.h"
# include "../../get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>

# define ERR_ARG "Number of args is wrong"
# define ERR_PIPE "Error while creating a pipe"
# define ERR_FORK "Error while forking"
# define ERR_DUP "Error while duplicating"
# define ERR_EXECVE "Error EXECVE"
# define ERR_MSG "pipex: "
# define ENV_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:"
# define ERR_OPEN "Error while opening"
# define ERR_HEREDOC "heredoc> "

typedef struct s_pipex
{
	pid_t	pid;
	int		ends[2];
	int		infile;
	int		outfile;
	int		cmd_index;
	char	**splitted_paths;
	char	*cmd_path;
	char	**cmd_splitted;
	char	quote;
	char	*cmd;
	char	**result;
	int		x;
}		t_pipex;

void	perror0(char *msg, int fd);
void	perror1(char *msg);
void	freee(char **str);
void	openn(t_pipex *rohr, char **argv, int argc);
void	openn_heredoc(t_pipex *rohr, char **argv, int argc);
void	here_doc(char *limiter, t_pipex *rohr);
char	*find_cmd_path(char *cmd, char **envp, t_pipex *rohr);
void	exec(char *cmd, char **envp);
int		check_quotes(char *cmd);
void	pipex(t_pipex rohr, char **argv, char **envp);
#endif