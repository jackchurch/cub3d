#include "../inc/ft_mlx.h"
#include "../inc/constance.h"

int	key_release(int keycode)
{
	if (keycode == LEFT_ARROW)
		t_player.turn_direction = 0;
	else if (keycode == RIGHT_ARROW)
		t_player.turn_direction = 0;
	else if (keycode == UP_ARROW)
		t_player.walk_direction = 0;
	else if (keycode == S_KEY)
		t_player.walk_direction = 0;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == LEFT_ARROW)
		t_player.turn_direction = -1;
	else if (keycode == RIGHT_ARROW)
		t_player.turn_direction = 1;
	else if (keycode == UP_ARROW)
		t_player.walk_direction = 1;
	else if (keycode == S_KEY)
		t_player.walk_direction = -1;
	else if (keycode == ESC)
		safe_exit(game);
	// renderPlayer(game);
	// movePlayer(game);
	// renderMap(game);
	// renderPlayer(game);
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
	mlx_hook(game->win, 2, 0, key_hook, game);
	mlx_hook(game->win, 3, 0, key_release, game);
	return (true);
}
