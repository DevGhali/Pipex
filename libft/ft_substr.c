/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabd-el- <gabd-el-@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:01:43 by codespace         #+#    #+#             */
/*   Updated: 2023/02/01 12:02:19 by gabd-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (len >= 18446744073709551615UL)
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
		sub = (char *) malloc(sizeof(char) * (1));
	else
	{
		if ((ft_strlen(s) >= len))
			sub = (char *)malloc(sizeof(char) * (len + 1));
		else
			sub = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
		if (sub == NULL)
			return (NULL);
		i = -1;
		while (++i < len && s[start + i] != '\0')
			sub[i] = s[start + i];
	}
	if (sub == NULL)
		return (NULL);
	sub[i] = '\0';
	return (sub);
}
