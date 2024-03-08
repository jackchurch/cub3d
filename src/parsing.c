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

int	check_vars(t_input *input)
{
	int	err;

	err = 0;
	if (input->map.rows >= 64)
		err += err_i("Map size too big. Please limit to 64x64.", err);
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
	if (input->map.count.colors != 0)
		err += err_i("Invalid color code.", err);
	if (!input->ceiling_color || !input->floor_color)
		err += err_i("Floor or Ceiling color missing or out of range.", err);
	return (err);
}

int	map_parsing(t_input *input, char **map)
{
	int	i;
	int	j;

	i = -1;
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
