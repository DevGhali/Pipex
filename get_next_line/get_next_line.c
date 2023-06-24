/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:23:00 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/06/08 19:06:08 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*set_next_line(char *stati)
{
	char	*set_line;
	size_t	i;

	i = 0;
	while (stati[i] != '\n' && stati[i] != '\0')
		i++;
	if (stati[i] == '\0')
		return (free(stati), NULL);
	if (i == 0 && stati[i] == '\n')
	{
		set_line = (char *)malloc(sizeof(char) * ft_strlen(stati));
		if (set_line == NULL)
			return (free(stati), NULL);
		ft_strlcpy(set_line, &stati[i + 1], ft_strlen(stati));
		return (free(stati), set_line);
	}
	set_line = (char *)malloc(sizeof(char) * ft_strlen(stati) - i + 1);
	if (!set_line)
		return (free(stati), NULL);
	ft_strlcpy(set_line, &stati[i + 1], ft_strlen(stati) - i);
	return (free(stati), set_line);
}

char	*print_next_line(char *stati)
{
	char	*print_line;
	size_t	i;

	i = 0;
	if (stati[i] == '\0')
		return (NULL);
	while (stati[i] != '\n' && stati[i] != '\0')
		i++;
	if (i == 0 && stati[i] == '\n')
	{
		print_line = (char *)malloc(sizeof(char) * 2);
		if (print_line == NULL)
			return (NULL);
		print_line[0] = '\n';
		print_line[1] = '\0';
		return (print_line);
	}
	print_line = (char *)malloc(sizeof(char) * i + 2);
	if (!print_line)
		return (NULL);
	ft_strlcpy(print_line, stati, i + 2);
	return (print_line);
}

char	*read_buf(char *stati, int fd)
{
	char	*buf;
	int		nb_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	nb_read = -1;
	while (nb_read != 0 && !ft_strchrr(stati, '\n'))
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
			return (free(buf), free(stati), NULL);
		buf[nb_read] = '\0';
		stati = ft_strjoinn(stati, buf);
	}
	return (free(buf), stati);
}

char	*get_next_line(int fd)
{
	static char	*stati;
	char		*print_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	stati = read_buf(stati, fd);
	if (!stati)
		return (NULL);
	print_line = print_next_line(stati);
	stati = set_next_line(stati);
	return (print_line);
}
