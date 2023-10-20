
#include <stdbool.h>
#include <fcntl.h>

#include "../inc/cub3d.h"

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
	{
		printf("failed to open fd 1\n");
		return (-1);
	}
	// Find height
	while (get_next_line(fd))
	{
		game->map_num_rows++;
		printf("Map height: %d\n", game->map_num_rows);
	}
	close(fd);
	game->map = (char **)ft_calloc(game->map_num_rows + 1, sizeof(char *));
	if (!game->map)
	{
		printf("failed to calloc game->map\n");
		return (-1);
	}
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		printf("failed to open fd 2\n");
		return (-1);
	}
	while (i < game->map_num_rows)
		game->map[i++] = get_next_line(fd);
	close(fd);
	// Find game map width
	game->map_num_cols = strlen(game->map[0]) - 1;
	printf("First row width id: %d: %s\n", game->map_num_cols, game->map[0]);

	return (0);
}

void	init_variables(t_game *game)
{
	printf("FUNC INIT_VAR\n");
	game->map_num_rows = 0;
	game->map_num_cols = 0;
}

int	keys(int keycode, t_game *game)
{
	if (keycode == ESC)
		safe_exit(game);
	return (0);
}

bool	init_program(t_game *game, char *map_name)
{
	printf("FUNC INIT_PROG\n");
	init_variables(game);
	copy_map(game, map_name);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Untitled Game");
	if (!game->win)
		safe_exit(game);
	mlx_hook(game->win, 17, 0, safe_exit, game);
	mlx_key_hook(game->win, keys, game);
	init_player(game);
	render(game);
	return (true);
}
