/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:46:18 by codespace         #+#    #+#             */
/*   Updated: 2023/01/15 20:55:58 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		x;
	int		y;
	int		s1_len;

	s1_len = ft_strlen((char *)s1);
	x = 0;
	y = 0;
	ret = (char *)malloc(sizeof(char) * (s1_len + ft_strlen((char *)s2) + 1));
	if (ret == NULL)
		return (NULL);
	while (s1[x] != '\0')
	{
		ret[x] = s1[x];
		x++;
	}
	while (s2[y] != '\0')
	{
		ret[x] = s2[y];
		x++;
		y++;
	}
	ret[s1_len + ft_strlen((char *)s2)] = '\0';
	return (ret);
}
