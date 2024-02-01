#include "../inc/ft_mlx.h"
#include "../inc/constance.h"

extern t_player	player;

int	key_release(int keycode)
{
	if (keycode == LEFT_ARROW || keycode == LINUX_A)
		player.turn_direction = 0;
	if (keycode == RIGHT_ARROW || keycode == LINUX_D)
		player.turn_direction = 0;
	if (keycode == UP_ARROW || keycode == LINUX_W)
		player.walk_direction = 0;
	if (keycode == S_KEY || keycode == LINUX_S)
		player.walk_direction = 0;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == LEFT_ARROW || keycode == LINUX_A)
		player.turn_direction = -1;
	if (keycode == RIGHT_ARROW || keycode == LINUX_D)
		player.turn_direction = 1;
	if (keycode == UP_ARROW || keycode == LINUX_W)
		player.walk_direction = 1;
	if (keycode == S_KEY || keycode == LINUX_S)
		player.walk_direction = -1;
	if (keycode == ESC || keycode == LINUX_ESC)
		safe_exit(game);
	// render_player(game);
	// move_player(game);
	// render_map(game);
	// render_player(game);
	render(game);
	return (0);
}

bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		safe_exit(game);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Legally Distinct Slï'mę Game");
	if (!game->win)
		safe_exit(game);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	return (true);
}
