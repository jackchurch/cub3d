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
#include "structs.h"

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

int	check_more_vars(t_input *input, int err)
{
	if (input->map.rows >= 64)
		err += err_i("Map size too big. Please limit to 64x64.", err);
	return (err);
}

int	check_vars(t_input *input)
{
	int	err;

	err = 0;
	if (input->map.count.map_exists == 0)
		err += err_i("No Map.", err);
	if (input->map.count.not_xpm > 0)
		err += err_i("Please ensure texture files are .xpm format.", err);
	if (input->map.count.comma > 0)
		err += err_i("Invalid color formatting.", err);
	if (input->map.count.invalid_char > 0)
		err += err_i("Invalid characters in cub elements.", err);
	else if (input->complete <= NUM_OF_ELEMENTS)
		err += err_i("Please check all input elements are present.", err);
	if (input->map.count.spawn_dir > 1)
		err += err_i("Please only use one spawn location.", err);
	if (input->map.count.spawn_dir < 1)
		err += err_i("Please provide a spawn location: N, S, E or W.", err);
	if (input->map.count.valid > 0)
		err += err_i("Invalid cub file. Please check and try again.", err);
	if (input->map.count.colors != 3)
		err += err_i("Invalid color code.", err);
	if (!input->ceiling_color || !input->floor_color)
		err += err_i("Floor or Ceiling color missing or out of range.", err);
	err += check_more_vars(input, err);
	return (err);
}
