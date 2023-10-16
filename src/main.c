
#include <stdbool.h>
#include <fcntl.h>
#include "../inc/cub3d.h"

int	player_x, player_y;

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

void	deallocate_mlx(t_game *game)
{
	printf("deallocate_mlx\n");
	free(game->win);
	free(game->mlx);
	return ;
}

void	deallocate_map(t_game *game)
{
	int	i;
	printf("deallocate_map\n");
	i = 0;
	while (i < game->map_height)
		free(game->map[i++]);
	free(game->map);
	return ;
}

int	safe_exit(t_game *game)
{
	printf("safe_exit\n");
	deallocate_map(game);
	deallocate_mlx(game);
	free(game);
	exit(0);
}
void	update(t_game *game)
{
	mlx_destroy_image(game->mlx, game->slime);
	game->slime = mlx_xpm_file_to_image(game->mlx, "images/slime.xpm", &player_x, &player_y);
	mlx_put_image_to_window(game->mlx, game->win, game->slime, player_x, player_y);
}
int	keys(int keycode, t_game *game)
{
	if (keycode == 53)
		safe_exit(game);
	if (keycode == 0)
		player_x += 50;
	update(game);
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
    mlx_hook(game->win, 2, 0, keys, game);
	mlx_key_hook(game->win, keys, game);
	return (true);
}



void	assign_images(t_game *game)
{
	game->slime = mlx_xpm_file_to_image(game->mlx, "images/slime.xpm", &player_x, &player_y);
	mlx_put_image_to_window(game->mlx, game->win, game->slime, player_x, player_y);
}

int	main(int argc, char *argv[])
{
	t_game	*game;
 
	player_x = 0; 
	player_y = 0;

	printf("FUNC MAIN\n");
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		printf("failed to calloc game\n");
		return (-1);
	}
	char* temp_name = argc != 2 ? "valid.ber" : argv[1];
	if (init_program(game, temp_name) == false)
		safe_exit(game);
	assign_images(game);
	update(game);
	mlx_loop(game->mlx);

	return (0);
}
