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
	t_axis				axis;

	ft_memset(&horizontal, 0, sizeof(horizontal));
	ft_memset(&axis, 0, sizeof(axis));
	find_intercept(&horizontal, &axis, ray_angle);
	calculate_steps(ray_angle, axis.x_step, axis.y_step, 'x');
	axis.next_touch_x = axis.x_intercept;
	axis.next_touch_y = axis.y_intercept;
	while (is_inside_map(axis.next_touch_x, axis.next_touch_y))
	{
		axis.x_to_check = axis.next_touch_x;
		axis.y_to_check = axis.next_touch_y;
		if (is_ray_facing_up(ray_angle))
			axis.y_to_check--;
		if (map_content_at(axis.x_to_check, axis.y_to_check) == 1)
		{
			wall_found(&horizontal, axis.next_touch_x, axis.next_touch_y, false);
			break ;
		}
		axis.next_touch_x += axis.x_step;
		axis.next_touch_y += axis.y_step;
	}
	return (horizontal);
}

//////////////////////////////////////////////
// Vertical ray grid intersection code.
//////////////////////////////////////////////
t_wall_hit	vertical_intersection(float ray_angle)
{
	static t_wall_hit	vertical;
	t_axis				axis;

	ft_memset(&vertical, 0, sizeof(vertical));
	ft_memset(&axis, 0, sizeof(axis));
	find_intercept(&vertical, &axis, ray_angle);
	calculate_steps(ray_angle, axis.x_step, axis.y_step, 'y');
	axis.next_touch_x = axis.x_intercept;
	axis.next_touch_y = axis.y_intercept;
	while (is_inside_map(axis.next_touch_x, axis.next_touch_y))
	{
		axis.x_to_check = axis.next_touch_x;
		axis.y_to_check = axis.next_touch_y;
		if (is_ray_facing_left(ray_angle))
			axis.x_to_check--;
		if (map_content_at(axis.x_to_check, axis.y_to_check) == 1)
		{
			wall_found(&vertical, axis.next_touch_x, axis.next_touch_y, true);
			break ;
		}
		axis.next_touch_x += axis.x_step;
		axis.next_touch_y += axis.y_step;
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
	orientation->distance = distance_between_points(t_player.x, t_player.y,
		orientation->wall_hit_x, orientation->wall_hit_y);
}

void	find_intercept(t_wall_hit *orientation, t_axis *axis, float ray_angle)
{
	orientation->distance = FLT_MAX;
	axis->x_intercept = floor(t_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		axis->x_intercept += TILE_SIZE;
	axis->y_intercept = t_player.y + (axis->x_intercept
		- t_player.x) * tan(ray_angle);
}