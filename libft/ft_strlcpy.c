/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:32:55 by rkabzins          #+#    #+#             */
/*   Updated: 2022/02/18 01:33:19 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *source, size_t size)
{
	size_t	i;

	if (!dest || !source)
		return (0);
	i = 0;
	while (source[i])
		i++;
	if (size == 0)
		return (i);
	i = 0;
	while (source[i] && i < size - 1)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	i = 0;
	while (source[i])
		i++;
	return (i);
}
