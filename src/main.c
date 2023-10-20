
#include <stdbool.h>
#include <fcntl.h>

#include "../inc/cub3d.h"


int	main(int argc, char *argv[])
{
	t_game	*game;

	printf("FUNC MAIN\n");
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		exit(-1);
	char* temp_name = argc != 2 ? "valid.ber" : argv[1];
	if (init_program(game, temp_name) == false)
		safe_exit(game);
	

	mlx_loop(game->mlx);
	return (0);
}
