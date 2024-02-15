/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:37:22 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/15 14:58:24 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)str;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)&s[ft_strlen(s)]);
		s++;
	}
	if ((char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
}
