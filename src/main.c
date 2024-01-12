#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"
#include "../inc/render.h"
#include "../inc/maths.h"
#include "../inc/ray.h"
#include "../inc/constance.h"

void	setup(void)
{
	// Add wall textrues here?
	t_player.x = WINDOW_WIDTH / 2;
	t_player.y = WINDOW_HEIGHT / 2;
	t_player.width = 1;
	t_player.height = 1;
	t_player.turnDirection = 0;
	t_player.walkDirection = 0;
	t_player.rotationAngle = M_PI / 2;
	t_player.walkSpeed = 10;
	t_player.turnSpeed = M_PI / 180 * t_player.walkSpeed;
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

void	movePlayer(t_game *game)
{
	float	moveStep;
	float	newPlayerX;
	float	newPlayerY;

	if (!game)
		return ;
	t_player.rotationAngle += t_player.turnDirection * t_player.turnSpeed;
	moveStep = t_player.walkDirection * t_player.walkSpeed;
	newPlayerX = t_player.x + cos(t_player.rotationAngle) * moveStep;
	newPlayerY = t_player.y + sin(t_player.rotationAngle) * moveStep;
	if (mapContentAt(newPlayerX, newPlayerY) != 1)
	{
		t_player.x = newPlayerX;
		t_player.y = newPlayerY;
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
// 	add angle increment to go to the next ray (rayangle += 60/320) -> convert 60 deg into rads
// }

void	render(t_game *game)
{
	movePlayer(game);
	castAllRays();
	generate3DProjection(game);
	renderMap(game);
	renderRays(game);
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
	game->data.img = mlx_new_image(game->mlx, WINDOW_WIDTH,  WINDOW_HEIGHT);
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel,
		&game->data.line_length, &game->data.endian);
	// process_input(); // See keyhooks
	// update(game); // Add FPS if have time. 
	render(game);
	mlx_loop(game->mlx);
	return (0);
}
