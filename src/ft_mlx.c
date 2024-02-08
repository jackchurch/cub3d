#include "../inc/ft_mlx.h"
#include "../inc/constance.h"

extern t_player	player;

int	key_release(int keycode)
{
	if (keycode == MAC_LEFT || keycode == MAC_RIGHT)
		player.turn_direction = 0;
	if (keycode == MAC_W || keycode == LINUX_W
			|| keycode == MAC_S || keycode == LINUX_S)
		player.walk_direction = 0;
	if (keycode == MAC_A || keycode == MAC_D)
		player.strafe_direction = 0;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == MAC_LEFT)
		player.turn_direction = -1;
	if (keycode == MAC_RIGHT)
		player.turn_direction = 1;
	if (keycode == MAC_A || keycode == LINUX_A)
		player.strafe_direction = -1;
	if (keycode == MAC_D || keycode == LINUX_D)
		player.strafe_direction = 1;
	if (keycode == MAC_W || keycode == LINUX_W)
		player.walk_direction = 1;
	if (keycode == MAC_S || keycode == LINUX_S)
		player.walk_direction = -1;
	if (keycode == MAC_ESC || keycode == LINUX_ESC)
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
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"Legally Distinct Slï'mę Game");
	if (!game->win)
		safe_exit(game);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	return (true);
}
