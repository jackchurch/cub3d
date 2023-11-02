
#include <stdbool.h>
#include <fcntl.h>
#include "../inc/cub3d.h"


// void	update(t_game *game)
// {

// }

int	keys(int keycode, t_game *game)
{
	if (keycode == 53)
		safe_exit(game);
	if (keycode == RIGHT)
		game->player->x += 50;
	// update(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	printf("FUNC MAIN\n");
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	game->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!game)
		return (-1);
	char* temp_name = argc != 2 ? "valid.ber" : argv[1];
	if (init_program(game, temp_name) == false)
		safe_exit(game);
	render(game);
	// update(game);
	mlx_loop(game->mlx);
	return (0);
}
