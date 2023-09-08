/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:42:31 by jchurch           #+#    #+#             */
/*   Updated: 2022/02/27 17:42:34 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;

	if (!*lst || !*del)
		return ;
	while (*lst)
	{
		p = (**lst).next;
		ft_lstdelone(*lst, del);
		*lst = p;
	}
}
