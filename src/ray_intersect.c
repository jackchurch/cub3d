#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

extern t_ray	g_rays[NUM_RAYS];

//////////////////////////////////////////////
// Horizintal ray grid intersection code.
//////////////////////////////////////////////
t_wall_hit	horizontal_intersection(float ray_angle)
{
	static t_wall_hit	horizontal;
	float				x_step;
	float				y_step;
	float				x_intercept;
	float				y_intercept;
	float				next_touch_x;
	float				next_touch_y;
	float				x_to_check;
	float				y_to_check;

	ft_memset(&horizontal, 0, sizeof(horizontal));
	horizontal.distance = FLT_MAX;
	y_intercept = floor(t_player.y / TILE_SIZE) * TILE_SIZE;
	//horizontal.next_touch_y = floor(t_player.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		y_intercept += TILE_SIZE;
	x_intercept = t_player.x + (y_intercept - t_player.y) / tan(ray_angle);
	//calculate_steps(ray_angle, &horizontal.xstep, &horizontal.ystep, 'x');
	y_step = TILE_SIZE;
	if (is_ray_facing_up(ray_angle))
		y_step *= -1;
	x_step = TILE_SIZE / tan(ray_angle);
	if (is_ray_facing_left(ray_angle) && x_step > 0)
		x_step *= -1;
	if (is_ray_facing_right(ray_angle) && x_step < 0)
		x_step *= -1;
	next_touch_x = x_intercept;
	next_touch_y = y_intercept;
	while (is_inside_map(next_touch_x, next_touch_y))
	{
		x_to_check = next_touch_x;
		y_to_check = next_touch_y;
		if (is_ray_facing_up(ray_angle))
			y_to_check--;
		if (map_content_at(x_to_check, y_to_check) == 1)
		{
			wall_found(&horizontal, next_touch_x, next_touch_y, false);
			horizontal.distance = distance_between_points(t_player.x, t_player.y,
				horizontal.wall_hit_x, horizontal.wall_hit_y);
			break ;
		}
		next_touch_x += x_step;
		next_touch_y += y_step;
	}
	return (horizontal);
}

//////////////////////////////////////////////
// Vertical ray grid intersection code.
//////////////////////////////////////////////
t_wall_hit	vertical_intersection(float ray_angle)
{
	static t_wall_hit	vertical;
	float				x_step;
	float				y_step;
	float				x_intercept;
	float				y_intercept;
	float				next_touch_x;
	float				next_touch_y;
	float				x_to_check;
	float				y_to_check;

	ft_memset(&vertical, 0, sizeof(vertical));
	vertical.distance = FLT_MAX;
	x_intercept = floor(t_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		x_intercept += TILE_SIZE;
	y_intercept = t_player.y + (x_intercept - t_player.x) * tan(ray_angle);
	//calculate_steps(ray_angle, &vertical.xstep, &vertical.ystep, 'y');
	x_step = TILE_SIZE;
	if (is_ray_facing_left(ray_angle))
		x_step *= -1;
	y_step = TILE_SIZE / tan(ray_angle);
	if (is_ray_facing_up(ray_angle) && y_step > 0)
		y_step *= -1;
	if (is_ray_facing_down(ray_angle) && y_step < 0)
		y_step *= -1;
	next_touch_x = x_intercept;
	next_touch_y = y_intercept;
	while (is_inside_map(next_touch_x, next_touch_y))
	{
		x_to_check = next_touch_x;
		y_to_check = next_touch_y;
		if (is_ray_facing_left(ray_angle))
			x_to_check--;
		if (map_content_at(x_to_check, y_to_check) == 1)
		{
			wall_found(&vertical, next_touch_x, next_touch_y, true);
			vertical.distance = distance_between_points(t_player.x, t_player.y,
				vertical.wall_hit_x, vertical.wall_hit_y);
			break ;
		}
		next_touch_x += x_step;
		next_touch_y += y_step;
	}
	return (vertical);
}

void	wall_found(t_wall_hit *orientation, float x_to_check,
		float y_to_check, bool is_vertical)
{
	orientation->found_wall_hit = true;
	orientation->wall_hit_x = x_to_check;
	orientation->wall_hit_y = y_to_check;
	orientation->wall_content = map_content_at((y_to_check / TILE_SIZE),
			(x_to_check / TILE_SIZE));
	orientation->is_vertical = is_vertical;
}

/*void	wall_hit_params(t_wall_hit *params)
{
	params->xstep = 0.0;
	params->ystep = 0.0;
	params->found_wall_hit = false;
	params->wall_hit_x = 0.0;
	params->wall_hit_y = 0.0;
	params->wall_content = 0;
	params->next_touch_x = 0.0;
	params->next_touch_y = 0.0;
	params->is_vertical = false;
}
*/