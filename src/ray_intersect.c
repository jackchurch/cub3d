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
	horizontal->next_touch_y = floor(t_player.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		horizontal->next_touch_y += TILE_SIZE;
	horizontal->next_touch_x = t_player.x
				+ (horizontal->next_touch_y - t_player.y) / tan(ray_angle);
	calculate_steps(ray_angle, &horizontal->xstep, &horizontal->ystep, 'x');
	while (is_inside_map(horizontal->next_touch_x, horizontal->next_touch_y))
	{
		if (is_ray_facing_up(ray_angle))
			horizontal->next_touch_y--;
		if (map_content_at(horizontal->next_touch_x,
					horizontal->next_touch_y) == 1)
		{
			wall_found(horizontal, horizontal->next_touch_y,
					horizontal->next_touch_x, false);
			break ;
		}
		horizontal->next_touch_x += horizontal->xstep;
		horizontal->next_touch_y += horizontal->ystep;
	}
}

//////////////////////////////////////////////
// Vertical ray grid intersection code.
//////////////////////////////////////////////
void	vertical_intersection(t_wall_hit *vertical, float ray_angle)
{
	vertical->next_touch_x = floor(t_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		vertical->next_touch_y += TILE_SIZE;
	vertical->next_touch_y = t_player.y
				+ (vertical->next_touch_x - t_player.x) * tan(ray_angle);
	calculate_steps(ray_angle, &vertical->xstep, &vertical->ystep, 'y');
	while (is_inside_map(vertical->next_touch_x, vertical->next_touch_y))
	{
		if (is_ray_facing_left(ray_angle))
			vertical->next_touch_x--;
		if (map_content_at(vertical->next_touch_x, vertical->next_touch_y) == 1)
		{
			wall_found(vertical, vertical->next_touch_y,
						vertical->next_touch_x, true);
			break ;
		}
		vertical->next_touch_x += vertical->xstep;
		vertical->next_touch_y += vertical->ystep;
	}
}

void	wall_found(t_wall_hit *orientation, float y_to_check,
		float x_to_check, bool is_vertical)
{
	orientation->found_wall_hit = true;
	orientation->wall_hit_x = x_to_check;
	orientation->wall_hit_y = y_to_check;
	orientation->wall_content = map_content_at((y_to_check / TILE_SIZE),
				(x_to_check / TILE_SIZE));
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
