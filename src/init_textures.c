/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:41:38 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 17:41:39 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	fill_textures(t_game *game, int i)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->input.map.rows)
	{
		x = -1;
		while (++x < game->input.map.longest_row)
		{
			game->texture[i][game->input.map.rows * y + x]
				= (game->walls[i].addr[game->input.map.rows * y + x]);
		}
	}
}

int	init_textures(t_game *game)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		game->walls[i].img = mlx_xpm_file_to_image(game->mlx,
				game->input.paths[i], &game->tile_size, &game->tile_size);
		if (!game->walls[i].img)
			return (1);
		game->walls[i].addr = (int *)mlx_get_data_addr(game->walls[i].img,
				&game->walls[i].bpp,
				&game->walls[i].line_length, &game->walls[i].endian);
		if (!game->walls[i].addr)
			return (2);
		fill_textures(game, i);
		free(game->input.paths[i]);
	}
	return (0);
}
