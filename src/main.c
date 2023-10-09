
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
		game->map_height++;
		printf("Map height: %d\n", game->map_height);
	}
	close(fd);
	game->map = (char **)ft_calloc(game->map_height + 1, sizeof(char *));
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
	while (i < game->map_height)
		game->map[i++] = get_next_line(fd);
	close(fd);
	// Find game map width
	game->map_width = strlen(game->map[0]) - 1;
	printf("First row width id: %d: %s\n", game->map_width, game->map[0]);

	return (0);
}

void	init_variables(t_game *game)
{
	printf("FUNC INIT_VAR\n");
	game->map_height = 0;
	game->map_width = 0;
}

int	init_program(t_game *game, char *map_name)
{
	printf("FUNC INIT_PROG\n");
	init_variables(game);
	copy_map(game, map_name);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_width,
			game->map_height, "Untitled Game");

	return (1);
}

int	safe_exit(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
		free(game->map[i++]);
	free(game->map);
	free(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	printf("FUNC MAIN\n");
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		printf("failed to calloc game\n");
		return (-1);
	}
	if (argc != 2)
		return (0);
	init_program(game, argv[1]);

	mlx_hook(game->win, 17, 0, safe_exit, game);
	mlx_loop(game->mlx);
	safe_exit(game);
	return (0);
}
