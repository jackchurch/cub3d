/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:27:31 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:27:33 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_len, size_t new_len)
{
	void	*new_ptr;

	if (new_len == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_len));
	if (new_len <= old_len)
		return (ptr);
	new_ptr = ft_calloc(new_len, 1);
	if (new_ptr)
		ft_memcpy(new_ptr, ptr, old_len);
	free(ptr);
	return (new_ptr);
}
