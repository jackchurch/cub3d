/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:00:15 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/26 18:00:17 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	err_v(char **str)
{
	printf("Error\n\t%s\n", str);
}

int	err_i(char **str)
{
	return (printf("Error\n\t%s\n", str));
}

void	*err_p(char **str)
{
	printf("Error\n\t%s\n", str);
	return (NULL);
}