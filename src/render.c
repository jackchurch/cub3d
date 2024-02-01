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
	while (++i < game->num_rays)
	{
		projected_wall_height = (int)((TILE_SIZE / (game->rays[i].distance
						* cos(game->rays[i].ray_angle - player.rotation_angle)))
				* ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2)));
		rect.x = i;
		rect.y = WINDOW_HEIGHT / 2 - projected_wall_height / 2;
		rect.width = 1;
		rect.height = projected_wall_height;
		rect.color = color_assignment(game, i);
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
