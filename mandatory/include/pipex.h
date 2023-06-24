/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:26:56 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/13 14:19:21 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
**	Libraries
*/
# include "../../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

/*
**  Macros
*/
# define ERR_ARGC "bad number of arguments"
# define ERR_MSG "pipex: "
# define ERR_INFILE "infile open error"
# define ERR_OUTFILE "outfile open error"
# define ERR_PIPE "error creating pipe"
# define ERR_FORK "error FORKING"
# define ERR_CMD "command not found or problem executing"
# define ERR_EXECVE "execve"
# define ENV_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:"

/*
**  Structs
*/
typedef struct s_pipex
{
	int		fds[2];
	pid_t	pid;
	pid_t	pid2;
	int		infile;
	int		outfile;
	char	**splitted_paths;
	char	*cmd_path;
	char	**cmd_splitted;
	char	quote;
	char	*cmd;
	char	**result;
}		t_pipex;

/*
**  Functions
*/

void	perror11(char *error);
void	perror00(char *error);
void	pipex(t_pipex pipee, char **argv, char **envp);
void	child(t_pipex pipee, char **argv, char **envp);
void	parent(t_pipex pipee, char **argv, char **envp);
void	exec(char *argv, char **envp);
char	*find_cmd_path(char *cmd, char **envp, t_pipex *pipee);
void	freee(char **str);
int		check_quotes(char *cmd);
#endif