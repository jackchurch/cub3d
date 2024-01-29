#include "../inc/render.h"
#include "../inc/draw.h"
#include "../inc/constance.h"
#include "../inc/cub3d.h"
#include "../inc/ray.h"

void	render_player(t_game *game)
{
	t_rectangle	player_rect;
	t_line		player_line;

	player_rect.x = t_player.x * MINIMAP_SCALE;
	player_rect.y = t_player.y * MINIMAP_SCALE;
	player_rect.width = t_player.width * MINIMAP_SCALE;
	player_rect.height = t_player.height * MINIMAP_SCALE;
	player_rect.color = 0x00E0B0FF;
	draw_rect(game, &player_rect);
	player_line.x0 = t_player.x * MINIMAP_SCALE;
	player_line.y0 = t_player.y * MINIMAP_SCALE;
	player_line.x1 = (t_player.x + cos(t_player.rotation_angle) * 40)
		* MINIMAP_SCALE;
	player_line.y1 = (t_player.y + sin(t_player.rotation_angle) * 40)
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
	ceiling.width = WINDOW_WIDTH;
	ceiling.height = WINDOW_HEIGHT / 2;
	ceiling.color = 0x00FAF0E6;
	draw_rect(game, &ceiling);
	floor.x = 0;
	floor.y = WINDOW_HEIGHT / 2;
	floor.width = WINDOW_WIDTH;
	floor.height = WINDOW_HEIGHT / 2;
	floor.color = 0x008B9E8A;
	draw_rect(game, &floor);
}

void	generate_3d_projection(t_game *game)
{
	int			i;
	int			projected_wall_height;
	t_rectangle	rect;

	i = -1;
	draw_ceiling(game);
	while (++i < NUM_RAYS)
	{
		projected_wall_height = (int)((TILE_SIZE / (g_rays[i].distance
					* cos(g_rays[i].ray_angle - t_player.rotation_angle)))
				* ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2)));
		rect.x = i;
		rect.y = WINDOW_HEIGHT / 2 - projected_wall_height / 2;
		rect.width = 1;
		rect.height = projected_wall_height;
		rect.color = color_assignment(i);
		draw_rect(game, &rect);
	}
}

/*
int			wall_top_pixel;
int			wall_bottom_pixel;

wall_top_pixel = (WINDOW_HEIGHT / 2) - (projected_wall_height / 2);
if (wall_top_pixel < 0)
	wall_top_pixel = 0;
wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (projected_wall_height / 2);
if (wall_bottom_pixel > WINDOW_HEIGHT)
wall_bottom_pixel = WINDOW_HEIGHT;
*/

int	color_assignment(int i)
{
	if (g_rays[i].is_ray_facing_down && !g_rays[i].was_hit_vertical)
		return (0x0000FFFF);
	if (g_rays[i].is_ray_facing_up && !g_rays[i].was_hit_vertical)
		return (0x00FFFF00);
	if (g_rays[i].is_ray_facing_left && g_rays[i].was_hit_vertical)
		return (0x00FF00FF);
	if (g_rays[i].is_ray_facing_right && g_rays[i].was_hit_vertical)
		return (0x0000FF00);
	return (0x00000000);
}
