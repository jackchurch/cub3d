/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:18:45 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:18:47 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/render.h"
#include "../inc/draw.h"
#include "../inc/constance.h"
#include "../inc/cub3d.h"
#include "../inc/ray.h"

extern t_player	g_player;

void	render_player(t_game *game)
{
	t_rectangle	player_rect;
	t_line		player_line;

	player_rect.x = g_player.x * MINIMAP_SCALE;
	player_rect.y = g_player.y * MINIMAP_SCALE;
	player_rect.width = g_player.width * MINIMAP_SCALE;
	player_rect.height = g_player.height * MINIMAP_SCALE;
	player_rect.color = 0x00E0B0FF;
	draw_rect(game, &player_rect);
	player_line.x0 = g_player.x * MINIMAP_SCALE;
	player_line.y0 = g_player.y * MINIMAP_SCALE;
	player_line.x1 = (g_player.x + cos(g_player.rotation_angle) * 40)
		* MINIMAP_SCALE;
	player_line.y1 = (g_player.y + sin(g_player.rotation_angle) * 40)
		* MINIMAP_SCALE;
	player_line.color = 0x00E0B0FF;
	draw_line(game, &player_line);
}

void	draw_ceiling(t_game *game)
{
	t_rectangle	ceiling;
	t_rectangle	floor;

	ceiling.x = 0;
	ceiling.y = 0;
	ceiling.width = game->win_width;
	ceiling.height = game->win_height / 2;
	ceiling.color = game->input.ceiling_color;
	draw_rect(game, &ceiling);
	floor.x = 0;
	floor.y = game->win_height / 2;
	floor.width = game->win_width;
	floor.height = game->win_height / 2;
	floor.color = game->input.floor_color;
	draw_rect(game, &floor);
}

void	wall_direction_init(t_game *game, int height, int dir, int i)
{
	game->walls[dir].loc.x = i;
	game->walls[dir].loc.y = game->win_height
		/ 2 - height / 2;
	game->walls[dir].width = 1;
	game->walls[dir].height = height;
}

int	find_direction(t_game *game, int i)
{
	if (game->rays[i].is_ray_facing_down && !game->rays[i].was_hit_vertical)
		return (SOUTH);
	if (game->rays[i].is_ray_facing_up && !game->rays[i].was_hit_vertical)
		return (NORTH);
	if (game->rays[i].is_ray_facing_left && game->rays[i].was_hit_vertical)
		return (WEST);
	if (game->rays[i].is_ray_facing_right && game->rays[i].was_hit_vertical)
		return (EAST);
	return (-1);
}

void	generate_3d_projection(t_game *game)
{
	int			i;
	int			projected_wall_height;
	int			dir;

	i = -1;
	//draw_ceiling(game);
	while (++i < game->num_rays)
	{
		dir = find_direction(game, i);
		if (dir < 0)
			return (err_v("Unknown Ray Projection Direction."));
		projected_wall_height = (int)((TILE_SIZE / (game->rays[i].distance
						* cos(game->rays[i].ray_angle
							- g_player.rotation_angle)))
				* ((game->win_width / 2) / tan(FOV_ANGLE / 2)));
		wall_direction_init(game, projected_wall_height, dir, i);
		draw_walls(game, &game->walls[dir], dir);
	}
}
