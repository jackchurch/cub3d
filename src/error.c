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
#include "constance.h"

void	err_v(char *str)
{
	printf("Error\n\t%s\n\n", str);
}

int	err_i(char *str, int i)
{
	if (i == 0)
	{
		printf(BRED);
		printf("\n\n\t\tPlease fix first error before moving on to others.\n");
		printf(BMAG);
		printf("\t\t__________________________________________________\n\n");
		printf(CRESET);
	}
	printf(URED "Error" CRESET BCYN " %d\n" CRESET, i + 1);
	printf("\t%s\n\n", str);
	return (1);
}

void	*err_p(char *str)
{
	printf("Error\n\t%s\n\n", str);
	return (NULL);
}
