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
# include <string.h>

/*
**  Macros
*/
# define ERR_ARGC "bad number of arguments"
# define ERR_MSG "pipex: "
# define ERR_PIPE "error creating pipe"
# define ERR_FORK "error FORKING"
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
    int     word_count;
}		t_pipex;

/*
**  Functions
*/
// pipex_utils.c
void	perror_exit1(t_pipex *pipee, char *error);
void	perror_exit0(t_pipex *pipee, char *error);
void	free_arr(char **arr);
void	first_child(t_pipex *pipee, char **argv, char **envp);
void	second_child(t_pipex *pipee, char **argv, char **envp);


// pipex.c
void	pipex(t_pipex *pipee, char **argv, char **envp);

// exec.c
void	exec(t_pipex *pipee, char *cmd, char **envp);
char	*find_cmd_path(char *cmd, char **envp, t_pipex *pipee);
char	**split_string(t_pipex *pipee, int i, int j, int k);
void    initialize_struct(t_pipex *pipee, char *cmd, char **envp);
int     count_words(t_pipex *pipee, int index, int j, int count);

// pipex_utils2.c
int		check_quotes(char *cmd);
char	helper_quote(char quote, char ret, int *i);
int     decider(char c, char quote);

#endif