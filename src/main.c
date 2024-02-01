#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"
#include "../inc/render.h"
#include "../inc/maths.h"
#include "../inc/ray.h"
#include "../inc/constance.h"
#include <math.h>

t_player	player;

	// Add wall textrues here?
void	setup(void)
{
	player.x = game->win_width / 2;
	player.y = game->win_height / 2;
	player.width = 1;
	player.height = 1;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.rotation_angle = M_PI / 2;
	player.walk_speed = 10;
	player.turn_speed = M_PI / 180 * player.walk_speed;
}

void	safe_exit(t_game *game)
{
	if (game->win)
		free(game->win);
	if (game->mlx)
		free(game->mlx);
	if (game->rays)
		free(game->rays);
	if (game)
		free(game);
	exit(0);
}

void	move_player(t_game *game)
{
	float	move_step;
	float	new_player_x;
	float	new_player_y;

	if (!game)
		return ;
	player.rotation_angle += player.turn_direction * player.turn_speed;
	move_step = player.walk_direction * player.walk_speed;
	new_player_x = player.x + cos(player.rotation_angle) * move_step;
	new_player_y = player.y + sin(player.rotation_angle) * move_step;
	if (map_content_at(new_player_x, new_player_y) != 1)
	{
		player.x = new_player_x;
		player.y = new_player_y;
	}
}

// 320 pixls window width
// 60 deg FOV -> must convert to rads
//
// while (column < 320width)
// {
// 	cast a ray
// 	trace the ray until it intersects with a wall (map[i][j] == 1)
// 	record the intersection x,y and ray distance
// 	add angle increment to go to the next ray (ray_angle += 60/320)to rads
// }

void	render(t_game *game)
{
	move_player(game);
	cast_all_rays(game);
	generate_3d_projection(game);
	render_map(game);
	render_rays(game);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->data.img, 0, 0);
}

int	main(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	init_window(game);
	game->win_width = MAP_NUM_COLS * TILE_SIZE;
	game->win_height = MAP_NUM_ROWS * TILE_SIZE;
	setup();
	game->num_rays = game->win_width;
	game->data = (t_data){0};
	game->rays = (t_ray *)ft_calloc(game->num_rays, sizeof(t_ray));
	game->data.img = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bpp,
			&game->data.line_length, &game->data.endian);
	// process_input(); // See keyhooks
	// update(game); // Add FPS if have time.
	render(game);
	mlx_loop(game->mlx);
	return (0);
}
