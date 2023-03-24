/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:48:23 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/01/20 22:02:35 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	x;
	unsigned char	*y;
	size_t			i;

	i = 0;
	x = (unsigned char)c;
	y = (unsigned char *)s;
	while (i < n)
	{
		if (y[i] == x)
			return ((void *)&y[i]);
		i++;
	}
	return (NULL);
}
