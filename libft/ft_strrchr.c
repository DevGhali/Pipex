/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:37:24 by gabd-el-          #+#    #+#             */
/*   Updated: 2023/01/22 16:53:10 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	x;
	char	*ptr;

	x = (char) c;
	ptr = NULL;
	while (*s != '\0')
	{
		if (*s == x)
			ptr = (char *) s;
		s++;
	}
	if (x == '\0')
		return ((char *) s);
	return (ptr);
}
