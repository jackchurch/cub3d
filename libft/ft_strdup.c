/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:34:52 by rkabzins          #+#    #+#             */
/*   Updated: 2022/02/18 01:35:17 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	char	*dest;
	size_t	src_len;

	src_len = ft_strlen(source) + 1;
	dest = malloc(sizeof(char) * (src_len));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, source, (src_len));
	return (dest);
}
