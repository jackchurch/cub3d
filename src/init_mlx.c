
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#include "../inc/cub3d.h"

void	init_player(t_game *game)
{
	game->player->x = game->window_width / 2;
	game->player->y = game->window_height / 2;
	game->player->width = PLAYER_SIZE;
	game->player->height = PLAYER_SIZE;
	game->player->turn_dir = 0;
	game->player->walk_dir = 0;
	game->player->rot_angle = TWO_PI;
	game->player->walk_speed = 5;
	game->player->turn_speed = (ONE_PI / 180) * game->player->walk_speed;
	return ;
}

int	copy_map(t_game *game, char *map_name)
{
	int	i;
	int	fd;

	printf("FUNC COPY_MAP\n");
	i = 0;

	game->map_num_rows = 0;
	game->map_num_cols = 0;
	printf("Mapname: %s\n", map_name);
	fd = open(map_name, O_RDONLY);
	printf("fd: %d\n", fd);
	if (fd < 0)
		return (-1);
	// Find height
	while (get_next_line(fd))
		game->map_num_rows++;
	printf("map_num_rows: %d\n", game->map_num_rows);
	close(fd);
	game->map = (char **)ft_calloc(game->map_num_rows + 1, sizeof(char *));
	if (!game->map)
		return (-1);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (i < game->map_num_rows)
	{
		game->map[i] = get_next_line(fd);
		printf("map line number: %i and contents: %s\n", i, game->map[i]);
		i++;
	}
	close(fd);
	// Find game map width
	game->map_num_cols = strlen(game->map[0]) - 1;
	game->window_width = game->map_num_cols * TILE_SIZE;
	game->window_height = game->map_num_rows * TILE_SIZE;
	printf("game->map_num_cols and height: %d %d\n", game->map_num_cols, game->map_num_rows);
	printf("game->window_width and height: %d %d\n", game->window_width, game->window_height);
	game->num_rays = game->window_width;
	return (0);
}

// void	init_variables(t_game *game)
// {
// 	printf("FUNC INIT_VAR\n");

// }

bool	init_program(t_game *game, char *map_name)
{
	printf("FUNC INIT_PROG\n");
	game->mlx = mlx_init();
	// init_variables(game);
	copy_map(game, map_name);
	init_player(game);
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "Legally Distinct Slï'm Game");
	if (!game->win)
		safe_exit(game);
	// init_map(game);
	mlx_hook(game->win, 17, 0, safe_exit, game);
	mlx_hook(game->win, 2, 0, keys, game);
	mlx_hook(game->win, 3, 0, key_release, game);
	// mlx_key_hook(game->win, keys, game);
	return (true);
}

