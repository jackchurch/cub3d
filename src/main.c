
#include <stdbool.h>
#include <fcntl.h>
#include "../inc/cub3d.h"


void	update(t_game *game)
{
	mlx_destroy_image(game->mlx, game->slime);
	game->slime = mlx_xpm_file_to_image(game->mlx, "images/slime.xpm",
			&game->player_x, &game->player_y);
	// mlx_put_image_to_window(game->mlx, game->win,
	// 	game->slime, game->player_x, game->player_y);
}

int	keys(int keycode, t_game *game)
{
	if (keycode == 53)
		safe_exit(game);
	if (keycode == RIGHT)
		game->player_x += 50;
	update(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	printf("FUNC MAIN\n");
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (-1);
	char* temp_name = argc != 2 ? "valid.ber" : argv[1];
	if (init_program(game, temp_name) == false)
		safe_exit(game);
	assign_images(game);
	render(game);
	// update(game);
	mlx_loop(game->mlx);
	return (0);
}
