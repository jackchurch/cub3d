#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

extern t_player	player;

void	calculate_steps(float ray_angle, float *xstep, float *ystep, char axis)
{
	if (axis == 'x')
	{
		*ystep = TILE_SIZE;
		if (is_ray_facing_up(ray_angle))
			*ystep *= -1;
		*xstep = TILE_SIZE / tan(ray_angle);
		if (is_ray_facing_left(ray_angle) && *xstep > 0)
			*xstep *= -1;
		if (is_ray_facing_right(ray_angle) && *xstep < 0)
			*xstep *= -1;
	}
	if (axis == 'y')
	{
		*xstep = TILE_SIZE;
		if (is_ray_facing_left(ray_angle))
			*xstep *= -1;
		*ystep = TILE_SIZE * tan(ray_angle);
		if (is_ray_facing_up(ray_angle) && *ystep > 0)
			*ystep *= -1;
		if (is_ray_facing_down(ray_angle) && *ystep < 0)
			*ystep *= -1;
	}
}

void	cast_one_ray(t_game *game, float ray_angle, int stripId)
{
	t_wall_hit	horizontal;
	t_wall_hit	vertical;

	normalize_angle(&ray_angle);
	horizontal = horizontal_intersection(game, ray_angle);
	vertical = vertical_intersection(game, ray_angle);
	if (horizontal.found_wall_hit)
		horizontal.distance = distance_between_points(player.x, player.y,
				horizontal.wall_hit_x, horizontal.wall_hit_y);
	if (vertical.found_wall_hit)
		vertical.distance = distance_between_points(player.x, player.y,
				vertical.wall_hit_x, vertical.wall_hit_y);
	//printf("Vert Distance: %f\nHori Distance: %f\n", vertical.distance, horizontal.distance);
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
	ray_angle = player.rotation_angle - FOV_ANGLE / 2;
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
		line.x0 = player.x * MINIMAP_SCALE;
		line.y0 = player.y * MINIMAP_SCALE;
		line.x1 = game->rays[i].wall_hit_x * MINIMAP_SCALE;
		line.y1 = game->rays[i].wall_hit_y * MINIMAP_SCALE;
		line.color = 0x00FFC8D7;
		draw_line(game, &line);
		i++;
	}
}
