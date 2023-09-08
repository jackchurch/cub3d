/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:45:37 by jchurch           #+#    #+#             */
/*   Updated: 2022/02/14 19:11:32 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	negative;

	i = 0;
	negative = 1;
	while (*str && ((*str >= '\t' && *str <= '\r') || *str == ' '))
		str++;
	if (*str == '+' && *(str + 1) >= '0' && *(str + 1) <= '9')
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10;
		i = i + (*str - 48);
		str++;
	}
	i = i * negative;
	return (i);
}
