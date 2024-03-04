/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:18:31 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:18:39 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

extern t_player	g_player;

void	calculate_steps(float ray_angle, t_axis *axis, char dir)
{
	if (dir == 'x')
	{
		axis->y_step = TILE_SIZE;
		if (is_ray_facing_up(ray_angle))
			axis->y_step *= -1;
		axis->x_step = TILE_SIZE / tan(ray_angle);
		if (is_ray_facing_left(ray_angle) && axis->x_step > 0)
			axis->x_step *= -1;
		if (is_ray_facing_right(ray_angle) && axis->x_step < 0)
			axis->x_step *= -1;
	}
	if (dir == 'y')
	{
		axis->x_step = TILE_SIZE;
		if (is_ray_facing_left(ray_angle))
			axis->x_step *= -1;
		axis->y_step = TILE_SIZE * tan(ray_angle);
		if (is_ray_facing_up(ray_angle) && axis->y_step > 0)
			axis->y_step *= -1;
		if (is_ray_facing_down(ray_angle) && axis->y_step < 0)
			axis->y_step *= -1;
	}
	axis->next_touch_x = axis->x_intercept;
	axis->next_touch_y = axis->y_intercept;
}

void	cast_one_ray(t_game *game, float ray_angle, int stripId)
{
	t_wall_hit	horizontal;
	t_wall_hit	vertical;

	normalize_angle(&ray_angle);
	horizontal = horizontal_intersection(game, ray_angle);
	vertical = vertical_intersection(game, ray_angle);
	horizontal.distance = FLT_MAX;
	vertical.distance = FLT_MAX;
	if (horizontal.found_wall_hit == true)
	{
		horizontal.distance = distance_between_points(g_player.x, g_player.y,
				horizontal.wall_hit_x, horizontal.wall_hit_y);
	}
	if (vertical.found_wall_hit == true)
	{
		vertical.distance = distance_between_points(g_player.x, g_player.y,
				vertical.wall_hit_x, vertical.wall_hit_y);
	}
	if (vertical.distance < horizontal.distance)
		ray_cast(game, &vertical, stripId, ray_angle);
	else
		ray_cast(game, &horizontal, stripId, ray_angle);
}

void	ray_cast(t_game *game, t_wall_hit *hit, int stripId, float ray_angle)
{
	game->rays[stripId].distance = hit->distance;
	game->rays[stripId].wall_hit_x = hit->wall_hit_x;
	game->rays[stripId].wall_hit_y = hit->wall_hit_y;
	game->rays[stripId].wall_hit_content = hit->wall_content;
	game->rays[stripId].was_hit_vertical = hit->is_vertical;
	game->rays[stripId].ray_angle = ray_angle;
	game->rays[stripId].is_ray_facing_down = is_ray_facing_down(ray_angle);
	game->rays[stripId].is_ray_facing_up = is_ray_facing_up(ray_angle);
	game->rays[stripId].is_ray_facing_left = is_ray_facing_left(ray_angle);
	game->rays[stripId].is_ray_facing_right = is_ray_facing_right(ray_angle);
}

void	cast_all_rays(t_game *game)
{
	int		strip_id;
	float	ray_angle;

	strip_id = 0;
	ray_angle = g_player.rotation_angle - FOV_ANGLE / 2;
	while (strip_id < game->num_rays)
	{
		cast_one_ray(game, ray_angle, strip_id);
		ray_angle += FOV_ANGLE / game->num_rays;
		strip_id++;
	}
}

void	render_rays(t_game *game)
{
	int		i;
	t_line	line;

	i = 0;
	while (i < game->num_rays)
	{
		line.x0 = g_player.x * game->input.map.minimap_scale;
		line.y0 = g_player.y * game->input.map.minimap_scale;
		line.x1 = game->rays[i].wall_hit_x * game->input.map.minimap_scale;
		line.y1 = game->rays[i].wall_hit_y * game->input.map.minimap_scale;
		line.color = 0x00FFC8D7;
		draw_line(game, &line);
		i++;
	}
}
