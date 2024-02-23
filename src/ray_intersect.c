#include "../inc/cub3d.h"
#include "../inc/ray.h"
#include "../inc/maths.h"
#include "../inc/constance.h"
#include "../inc/map.h"

extern t_player	player;

//////////////////////////////////////////////
// Horizintal ray grid intersection code.
//////////////////////////////////////////////
t_wall_hit	horizontal_intersection(t_game *game, float ray_angle)
{
	t_wall_hit	hori;
	t_axis		axis;

	ft_memset(&hori, 0, sizeof(hori));
	ft_memset(&axis, 0, sizeof(axis));
	// hori = (t_wall_hit){0};
	// axis = (t_axis){0};
	find_intercept(&axis, ray_angle, 'x');
	calculate_steps(ray_angle, &axis, 'x');
	printf("horiz.next_touch_x = %f\n",axis.next_touch_x);
	printf("horiz.next_touch_y = %f\n",axis.next_touch_y);
	while (is_inside_map(game, axis.next_touch_x, axis.next_touch_y))
	{
		axis.x_to_check = axis.next_touch_x;
		axis.y_to_check = axis.next_touch_y;
		if (is_ray_facing_up(ray_angle))
			axis.y_to_check--;
		if (map_content_at(game, axis.x_to_check, axis.y_to_check) == '1')
		{
			wall_found(game, &hori, axis, false);
			break ;
		}
		axis.next_touch_x += axis.x_step;
		axis.next_touch_y += axis.y_step;
		printf("horiz.next_touch_x = %f\n",axis.next_touch_x);
		printf("horiz.next_touch_y = %f\n",axis.next_touch_y);
	}
	return (hori);
}

//////////////////////////////////////////////
// Vertical ray grid intersection code.
//////////////////////////////////////////////
t_wall_hit	vertical_intersection(t_game *game, float ray_angle)
{
	static t_wall_hit	vertical;
	t_axis				axis;

	ft_memset(&vertical, 0, sizeof(vertical));
	ft_memset(&axis, 0, sizeof(axis));
	// vertical = (t_wall_hit){0};
	// axis = (t_axis){0};
	find_intercept(&axis, ray_angle, 'y');
	calculate_steps(ray_angle, &axis, 'y');
	printf("vert.next_touch_x = %f\n",axis.next_touch_x);
	printf("vert.next_touch_y = %f\n",axis.next_touch_y);
	while (is_inside_map(game, axis.next_touch_x, axis.next_touch_y))
	{
		axis.x_to_check = axis.next_touch_x;
		axis.y_to_check = axis.next_touch_y;
		if (is_ray_facing_left(ray_angle))
			axis.x_to_check--;
		if (map_content_at(game, axis.x_to_check, axis.y_to_check) == '1')
		{
			wall_found(game, &vertical, axis, true);
			break ;
		}
		axis.next_touch_x += axis.x_step;
		axis.next_touch_y += axis.y_step;
		printf("vert.next_touch_x = %f\n",axis.next_touch_x);
		printf("vert.next_touch_y = %f\n",axis.next_touch_y);
	}
	return (vertical);
}

void	wall_found(t_game *game, t_wall_hit *orientation, t_axis axis, bool is_vertical)
{
	orientation->found_wall_hit = true;
	// orientation->distance = game->win_width + game->win_height;
	orientation->wall_hit_x = axis.next_touch_x;
	orientation->wall_hit_y = axis.next_touch_y;
	orientation->wall_content = map_content_at(game, axis.next_touch_y / TILE_SIZE,
			axis.next_touch_x / TILE_SIZE);
	orientation->is_vertical = is_vertical;
}

void	find_intercept(t_axis *axis, float ray_angle, char dir)
{
	if (dir == 'y')
	{
		axis->x_intercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
		if (is_ray_facing_right(ray_angle))
			axis->x_intercept += TILE_SIZE;
		axis->y_intercept = player.y + (axis->x_intercept
				- player.x) * tan(ray_angle);
	}
	if (dir == 'x')
	{
		axis->y_intercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
		if (is_ray_facing_down(ray_angle))
			axis->y_intercept += TILE_SIZE;
		axis->x_intercept = player.x + (axis->y_intercept
				- player.y) / tan(ray_angle);
	}
}
