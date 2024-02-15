/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:33:34 by rkabzins          #+#    #+#             */
/*   Updated: 2022/02/18 01:34:00 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*s;
	size_t	dest_size;
	size_t	src_size;
	size_t	result;
	size_t	i;

	s = (char *)src;
	i = 0;
	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (size > dest_size)
		result = dest_size + src_size;
	else
		result = src_size + size;
	while (s[i] && (dest_size + 1) < size)
	{
		dest[dest_size] = s[i];
		dest_size++;
		i++;
	}
	dest[dest_size] = 0;
	return (result);
}
