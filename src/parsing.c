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
	if (input->map.count.spawn_dir > 1)
		return (err_i("Please only use one spawn location."));
	if (input->map.count.spawn_dir < 1)
		return (err_i("Please provide a spawn location: 'N', 'E', 'S' or 'W'"));
	if (input->map.count.valid > 0)
		return (err_i("Invalid Map Content. Please check and try again."));
	if (input->map.count.colors != 0)
		return (err_i("Invalid color code spacing."));
	return (0);
}

int	map_parsing(t_game *game, char **map)
{
	int	i;
	int	j;

	i = -1;
	if (!is_only_one(map[0]) || !is_only_one(map[game->input.map.rows - 1]))
		game->input.map.count.valid += 1;
	while (++i < game->input.map.rows && game->input.map.count.valid == 0)
	{
		j = -1;
		while (++j < game->input.map.longest_row
			&& game->input.map.count.valid == 0)
		{
			if (walk_area(map[i][j]))
				game->input.map.count.valid += map_check(map, i, j);
		}
	}
	return (check_vars(&game->input));
}
