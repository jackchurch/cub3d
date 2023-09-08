/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:16:07 by jchurch           #+#    #+#             */
/*   Updated: 2022/02/14 18:08:37 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p_char;
	size_t	total_memory;

	total_memory = count * size;
	p_char = malloc(total_memory);
	if (!(p_char))
		return (NULL);
	ft_bzero(p_char, total_memory);
	return (p_char);
}
