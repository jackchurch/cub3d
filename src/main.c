#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"
#include "../inc/render.h"
#include "../inc/maths.h"
#include "../inc/ray.h"
#include "../inc/constance.h"

	// Add wall textrues here?
void	setup(void)
{
	t_player.x = WINDOW_WIDTH / 2;
	t_player.y = WINDOW_HEIGHT / 2;
	t_player.width = 1;
	t_player.height = 1;
	t_player.turn_direction = 0;
	t_player.walk_direction = 0;
	t_player.rotation_angle = M_PI / 2;
	t_player.walk_speed = 10;
	t_player.turn_speed = M_PI / 180 * t_player.walk_speed;
}

void	safe_exit(t_game *game)
{
	if (game->win)
		free(game->win);
	if (game->mlx)
		free(game->mlx);
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
	t_player.rotation_angle += t_player.turn_direction * t_player.turn_speed;
	move_step = t_player.walk_direction * t_player.walk_speed;
	new_player_x = t_player.x + cos(t_player.rotation_angle) * move_step;
	new_player_y = t_player.y + sin(t_player.rotation_angle) * move_step;
	if (map_content_at(new_player_x, new_player_y) != 1)
	{
		t_player.x = new_player_x;
		t_player.y = new_player_y;
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
	cast_all_rays();
	generate3DProjection(game);
	render_map(game);
	render_rays(game);
	renderPlayer(game);
	mlx_put_image_to_window(game->mlx, game->win, game->data.img, 0, 0);
}

int	main(void)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	init_window(game);
	setup();
	game->data = (t_data){0};
	game->data.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bpp,
			&game->data.line_length, &game->data.endian);
	// process_input(); // See keyhooks
	// update(game); // Add FPS if have time. 
	render(game);
	mlx_loop(game->mlx);
	return (0);
}
