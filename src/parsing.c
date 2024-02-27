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

int	map_parsing(t_game *game, char **map)
{
	int	i;
	int	j;
	int	check;

	i = -1;
	if (!is_only_one(map[0]) || !is_only_one(map[game->input.map.rows - 1]))
	{
		err_i("Invalid Map Content. Please check map and try again!");
		game->update.end_game = 1;
		return (1);
	}
	while (++i < game->input.map.rows)
	{
		j = -1;
		while (++j < game->input.map.longest_row)
		{
			if (map[i][j] == '0')
				check = map_check(map, i, j);
			if (check == 1)
			{
				err_i("Invalid Map Content. Please check map and try again.");
				game->update.end_game = 1;
				safe_exit(game);
				return (1);
			}
		}
	}
	return (0);
}
