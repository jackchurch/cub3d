/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:16:54 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:57 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"

char	map_content_at(t_game *game, float x, float y)
{
	int	map_grid_index_y;
	int	map_grid_index_x;

	if (x < 0 || y < 0)
		return (0);
	map_grid_index_y = (int)floor(y / TILE_SIZE);
	map_grid_index_x = (int)floor(x / TILE_SIZE);
	if (map_grid_index_y >= game->input.map.rows
		|| map_grid_index_x >= game->input.map.longest_row)
		return (0);
	return (game->input.map.content[map_grid_index_y][map_grid_index_x]);
}

char	get_map_at(t_game *game, int i, int j)
{
	return (game->input.map.content[i][j]);
}

bool	is_inside_map(t_game *game, float x, float y)
{
	return (x >= 0 && x <= game->input.map.longest_row * TILE_SIZE
		&& y >= 0 && y <= game->input.map.rows * TILE_SIZE);
}

void	tile_rect_init(t_game *game, t_rectangle *map_tile_rect, const t_tile tile)
{
	map_tile_rect->x = tile.x * game->input.map.minimap_scale;
	map_tile_rect->y = tile.y * game->input.map.minimap_scale;
	map_tile_rect->width = TILE_SIZE * game->input.map.minimap_scale;
	map_tile_rect->height = TILE_SIZE * game->input.map.minimap_scale;
	map_tile_rect->color = tile.color;
}

void	render_map(t_game *game)
{
	int			i;
	int			j;
	t_tile		tile;
	t_rectangle	map_tile_rect;

	i = -1;
	while (++i < game->input.map.rows)
	{
		j = -1;
		while (++j < game->input.map.longest_row)
		{
			tile.x = j * TILE_SIZE;
			tile.y = i * TILE_SIZE;
			if (get_map_at(game, i, j) == '1')
				tile.color = 0x000000FF;
			else
				tile.color = 0x00FFFFFF;
			tile_rect_init(game, &map_tile_rect, tile);
			draw_rect(game, &map_tile_rect);
		}
	}
}
