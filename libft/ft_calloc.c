/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:34:12 by rkabzins          #+#    #+#             */
/*   Updated: 2022/02/18 01:34:41 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	if (!n || !size)
	{
		size = 1;
		n = size;
	}
	ptr = malloc(n * size);
	if (ptr)
		ft_bzero(ptr, n * size);
	return (ptr);
}
