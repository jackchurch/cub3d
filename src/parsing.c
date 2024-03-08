/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:52:14 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/27 13:52:16 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "map.h"
#include "cub_file.h"

int	map_invalid(char check)
{
	if (check == '0' || check == '1' || check == 'N'
		|| check == 'E' || check == 'S' || check == 'W' || check == 'D')
		return (0);
	return (1);
}

int	map_check(char **map, int i, int j)
{
	if (map_invalid(map[i - 1][j]) || map_invalid(map[i + 1][j])
		|| map_invalid(map[i][j + 1]) || map_invalid(map[i][j - 1]))
		return (1);
	return (0);
}

int	walk_area(char check)
{
	if (check == '0' || check == 'N' || check == 'S'
		|| check == 'E' || check == 'W' || check == 'D')
		return (1);
	return (0);
}

int	map_parsing(t_input *input, char **map)
{
	int	i;
	int	j;

	i = -1;
	if (input->map.count.map_exists == 0)
		return (check_vars(input));
	if (input->complete < NUM_OF_ELEMENTS
		|| !is_only_one(map[input->map.rows - 1]) || !is_only_one(map[0]))
		input->map.count.valid += 1;
	while (++i < input->map.rows && input->map.count.valid == 0)
	{
		j = -1;
		while (++j < input->map.longest_row
			&& input->map.count.valid == 0
			&& map[i][j])
		{
			if (walk_area(map[i][j]))
				input->map.count.valid += map_check(map, i, j);
		}
	}
	return (check_vars(input));
}
