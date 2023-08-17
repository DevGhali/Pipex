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

# define ERR_ARG "Bad Number of Arguments"
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
	int		fds[2];
    pid_t	pid;
    int		infile;
    int		outfile;
    int		cmd_index;
	char	**splitted_paths;
	char	*cmd_path;
	char	**cmd_splitted;
	char	quote;
	char	*cmd;
	char	**result;
    int     word_count;
}		t_pipex;

//pipex_bonus_utils.c
void	perror_exit0(t_pipex *pipee, char *error, int fd);
void	perror_exit1(t_pipex *pipee, char *error);
void	free_arr(char **arr);

//pipex_bonus_utils2.c
int		check_quotes(char *cmd);
char	helper_quote(char quote, char ret, int *i);
int     decider(char c, char quote);

//pipex_bonus.c
void	pipex(t_pipex *pipee, char **argv, int argc, char **envp);

//exec_bonus.c
void	exec_bonus(t_pipex *pipee, char *cmd, char **envp);
char	**split_string(t_pipex *pipee, int i, int j, int k);
char	*find_cmd_path(char *cmd, char **envp, t_pipex *pipee);
int     count_words(t_pipex *pipee, int index, int j, int count);
void    initialize_struct(t_pipex *pipee, char *cmd, char **envp, int flag);

//here_doc.c
void	here_doc(char *limiter, t_pipex *pipee, char **argv, int argc);

#endif