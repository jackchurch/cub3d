
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#include "../inc/cub3d.h"

void	init_player(t_game *game)
{
	game->player->x = WINDOW_WIDTH / 2;
	game->player->y = WINDOW_HEIGHT / 2;
	game->player->width = game->player->x + PLAYER_SIZE;
	game->player->height = game->player->y + PLAYER_SIZE;
	game->player->turn_dir = 0;
	game->player->walk_dir = 0;
	game->player->rot_angle = M_PI_2;
	game->player->walk_speed = 100;
	game->player->turn_speed = 45 * M_PI_2;
	return ;
}

int	copy_map(t_game *game, char *map_name)
{
	int	i;
	int	fd;

	printf("FUNC COPY_MAP\n");
	i = 0;

	printf("Mapname: %s\n", map_name);
	fd = open(map_name, O_RDONLY);
	printf("fd: %d\n", fd);
	if (fd < 0)
		return (-1);
	// Find height
	while (get_next_line(fd))
	{
		game->map_height++;
	}
	printf("map_height: %d\n", game->map_height);
	close(fd);
	game->map = (char **)ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map)
	{
		return (-1);
	}
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		return (-1);
	}
	while (i < game->map_height)
	{
		game->map[i] = get_next_line(fd);
		printf("map line number: %i and contents: %s\n", i, game->map[i]);
		i++;
	}
	close(fd);
	// Find game map width
	game->map_width = strlen(game->map[0]) - 1;
	printf("game->map_width and height: %d %d\n", game->map_width, game->map_height);
	return (0);
}

void	init_variables(t_game *game)
{
	printf("FUNC INIT_VAR\n");
	game->map_height = 0;
	game->map_width = 0;
}

bool	init_program(t_game *game, char *map_name)
{
	printf("FUNC INIT_PROG\n");
	game->mlx = mlx_init();
	init_variables(game);
	init_player(game);
	copy_map(game, map_name);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Legally Distinct Slï'm Game");
	if (!game->win)
		safe_exit(game);
	// init_map(game);
	mlx_hook(game->win, 17, 0, safe_exit, game);
	mlx_hook(game->win, 2, 0, keys, game);
	mlx_key_hook(game->win, keys, game);
	return (true);
}

