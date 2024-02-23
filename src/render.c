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

extern t_player	player;

void	render_player(t_game *game)
{
	t_rectangle	player_rect;
	t_line		player_line;

	player_rect.x = player.x * MINIMAP_SCALE;
	player_rect.y = player.y * MINIMAP_SCALE;
	player_rect.width = player.width * MINIMAP_SCALE;
	player_rect.height = player.height * MINIMAP_SCALE;
	player_rect.color = 0x00E0B0FF;
	draw_rect(game, &player_rect);
	player_line.x0 = player.x * MINIMAP_SCALE;
	player_line.y0 = player.y * MINIMAP_SCALE;
	player_line.x1 = (player.x + cos(player.rotation_angle) * 40)
		* MINIMAP_SCALE;
	player_line.y1 = (player.y + sin(player.rotation_angle) * 40)
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

void	generate_3d_projection(t_game *game)
{
	int			i;
	int			projected_wall_height;
	t_rectangle	rect;

	i = -1;
	draw_ceiling(game);
	while (++i < game->num_rays)
	{
		projected_wall_height = (int)((TILE_SIZE / (game->rays[i].distance
						* cos(game->rays[i].ray_angle - player.rotation_angle)))
				* ((game->win_width / 2) / tan(FOV_ANGLE / 2)));
		rect.x = i;
		rect.y = game->win_height / 2 - projected_wall_height / 2;
		rect.width = 1;
		rect.height = projected_wall_height;
		rect.color = color_assignment(game, i);
		draw_rect(game, &rect);
	}
}

int	color_assignment(t_game *game, int i)
{
	if (game->rays[i].is_ray_facing_down && !game->rays[i].was_hit_vertical)
		return (0x0000FFFF);
	if (game->rays[i].is_ray_facing_up && !game->rays[i].was_hit_vertical)
		return (0x00FFFF00);
	if (game->rays[i].is_ray_facing_left && game->rays[i].was_hit_vertical)
		return (0x00FF00FF);
	if (game->rays[i].is_ray_facing_right && game->rays[i].was_hit_vertical)
		return (0x0000FF00);
	return (0x00000000);
}
