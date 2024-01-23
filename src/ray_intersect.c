#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

extern t_ray	g_rays[NUM_RAYS];

//////////////////////////////////////////////
// Horizintal ray grid intersection code.
//////////////////////////////////////////////
void	horizontal_intersection(t_wall_hit *horizontal, float ray_angle)
{
	float		yintercept;
	float		xintercept;
	float		x_to_check;
	float		y_to_check;

	yintercept = floor(t_player.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		yintercept += TILE_SIZE;
	xintercept = t_player.x + (yintercept - t_player.y) / tan(ray_angle);
	calculate_steps(ray_angle, &horizontal->xstep, &horizontal->ystep, 'x');
	horizontal->next_touch_x = xintercept;
	horizontal->next_touch_y = yintercept;
	while (is_inside_map(horizontal->next_touch_x, horizontal->next_touch_y))
	{
		x_to_check = horizontal->next_touch_x;
		if (is_ray_facing_up(ray_angle))
			y_to_check = horizontal->next_touch_y - 1;
		if (map_content_at(x_to_check, y_to_check) == 1)
		{
			wall_found(horizontal, y_to_check, x_to_check, false);
			break ;
		}
		step_increment(horizontal);
	}
}

//////////////////////////////////////////////
// Vertical ray grid intersection code.
//////////////////////////////////////////////
void	vertical_intersection(t_wall_hit *vertical, float ray_angle)
{
	float		yintercept;
	float		xintercept;
	float		x_to_check;
	float		y_to_check;

	xintercept = floor(t_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		xintercept += TILE_SIZE;
	yintercept = t_player.y + (xintercept - t_player.x) * tan(ray_angle);
	calculate_steps(ray_angle, &vertical->xstep, &vertical->ystep, 'y');
	vertical->next_touch_x = xintercept;
	vertical->next_touch_y = yintercept;
	while (is_inside_map(vertical->next_touch_x, vertical->next_touch_y))
	{
		y_to_check = vertical->next_touch_y;
		if (is_ray_facing_left(ray_angle)
			x_to_check = vertical->next_touch_x - 1;
		if (map_content_at(x_to_check, y_to_check) == 1)
		{
			wall_found(vertical, y_to_check, x_to_check, true);
			break ;
		}
		step_increment(vertical);
	}
}

void	step_increment(t_wall_hit *orientation)
{
	orientation->next_touch_x += orientation->xstep;
	orientation->next_touch_y += orientation->ystep;
}

void	wall_found(t_wall_hit *orientation, float y_to_check,
		float x_to_check, bool is_vertical)
{
	orientation->found_wall_hit = true;
	orientation->wall_hit_x = orientation->next_touch_x;
	orientation->wall_hit_y = orientation->next_touch_y;
	orientation->wall_content = map_content_at((y_to_check / TILE_SIZE), (x_to_check / TILE_SIZE));
	orientation->is_vertical = is_vertical;
}

void	wall_hit_params(t_wall_hit *params)
{
	params->xstep = 0.0;
	params->ystep = 0.0;
	params->found_wall_hit = false;
	params->wall_hit_x = 0.0;
	params->wall_hit_y = 0.0;
	params->wall_content = 0;
	params->next_touch_x = 0.0;
	params->next_touch_y = 0.0;
	params->is_vertical = 0;
}
