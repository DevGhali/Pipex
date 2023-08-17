/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:39:31 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/08 22:08:05 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex_bonus.h"

int count_words(t_pipex *pipee, int index, int j, int count)
{
    while (pipee->cmd[index] != '\0')
    {
        if (decider(pipee->cmd[index], pipee->quote) == 1)
        {
            pipee->quote = helper_quote(pipee->quote, pipee->cmd[index], &index);
            continue ;
        }
        if (decider(pipee->cmd[index], pipee->quote) == 0)
        {
            if (j > 0)
            {
                count++;
                j = 0;
            }
        }
        else
            j++;
        index++;
    }
    return (count);
}

void initialize_struct(t_pipex *pipee, char *cmd, char **envp, int flag)
{
    pipee->cmd = cmd;
    pipee->quote = '\0';
    pipee->word_count = count_words(pipee, 0, 0, 0);
    pipee->result = malloc(pipee->word_count * sizeof(char *));
    pipee->result[0] = (char *)malloc(ft_strlen(cmd) * sizeof(char));
    pipee->cmd_splitted = split_string(pipee, 0, 0, 0);
    pipee->cmd_path = find_cmd_path(pipee->cmd_splitted[0], envp, pipee);
    if (!pipee->cmd_path && flag)
    {
        write(STDERR_FILENO, ERR_MSG, 7);
        ft_putstr_fd(pipee->cmd, STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        if (pipee->cmd_splitted != NULL)
            free_arr(pipee->cmd_splitted);
    }
}

char	**split_string(t_pipex *pipee, int i, int j, int k)
{
    while (pipee->cmd[i] != '\0')
    {
        if (decider(pipee->cmd[i], pipee->quote) == 1)
        {
            pipee->quote = helper_quote(pipee->quote, pipee->cmd[i], &i);
            continue ;
        }
        if (decider(pipee->cmd[i], pipee->quote) == 0)
        {
            if (j > 0)
            {
                pipee->result[k][j] = '\0';
                k++;
                pipee->result[k] = malloc(ft_strlen(pipee->cmd) * sizeof(char));
                j = 0;
            }
        }
        else
            pipee->result[k][j++] = pipee->cmd[i];
        i++;
    }
    if (j > 0)
        pipee->result[k++][j] = '\0';
    pipee->result[k] = NULL;
    return (pipee->result);
}

char	*find_cmd_path(char *cmd, char **envp, t_pipex *pipee)
{
    size_t	i;

    if (access(cmd, F_OK) == 0 || cmd == NULL)
        return (cmd);
    i = 0;
    if (envp[i] == NULL)
        pipee->splitted_paths = ft_split(ENV_PATH, ':');
    else
    {
        while (ft_strncmp(envp[i], "PATH=", 5) != 0)
            i++;
        pipee->splitted_paths = ft_split(envp[i] + 5, ':');
    }
    i = 0;
    while (pipee->splitted_paths[i])
    {
        pipee->splitted_paths[i] = ft_strjoin(pipee->splitted_paths[i], "/");
        pipee->cmd_path = ft_strjoin(pipee->splitted_paths[i], cmd);
        if (access(pipee->cmd_path, F_OK) == 0)
            return (pipee->cmd_path);
        free(pipee->cmd_path);
        i++;
    }
    free_arr(pipee->splitted_paths);
    return (NULL);
}

void	exec_bonus(t_pipex *pipee, char *cmd, char **envp)
{
    if (!check_quotes(cmd))
        perror_exit1(pipee, "command not found");
    if (ft_strncmp(cmd, " ", ft_strlen(cmd)) != 0)
    {
        initialize_struct(pipee, cmd, envp, 0);
        execve(pipee->cmd_path, pipee->cmd_splitted, envp);
    }
}