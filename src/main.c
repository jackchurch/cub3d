
#include <stdbool.h>
#include <fcntl.h>
#include "../inc/cub3d.h"

int	map_has_wall_at(t_game *game, float new_x, float new_y)
{
	int		map_grid_col;
	int		map_grid_row;
	char	result;

	map_grid_col = floor(new_x / TILE_SIZE);
	map_grid_row = floor(new_y / TILE_SIZE);
	result = game->map[map_grid_row][map_grid_col]; // [row 0][column 0] -> [r0][c1] -> etc
	if (result == '1')
		return (TRUE);
	return (FALSE);
}

void	move_player(t_game *game)
{
	float	move_step;
	float	new_x;
	float	new_y;

	game->player->rot_angle += game->player->turn_dir * game->player->turn_speed;
	move_step = game->player->walk_dir * game->player->walk_speed;
	new_x = game->player->x + cos(game->player->rot_angle) * move_step;
	new_y = game->player->y + sin(game->player->rot_angle) * move_step;
	if (map_has_wall_at(game, new_x, new_y) == FALSE)
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
	return ;
}

int	keys(int keycode, t_game *game)
{
	if (keycode == LEFT)
		game->player->turn_dir = -1;
	else if (keycode == RIGHT)
		game->player->turn_dir = 1;
	else if (keycode == UP)
		game->player->walk_dir = 1;
	else if (keycode == DOWN)
		game->player->walk_dir = -1;
	else if (keycode == ESC)
		safe_exit(game);
	// render_player(game);
	move_player(game);
	game->player->turn_dir = 0;
	game->player->turn_dir = 0;
	game->player->walk_dir = 0;
	game->player->walk_dir = 0;
	render(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == LEFT)
		game->player->turn_dir = 0;
	else if (keycode == RIGHT)
		game->player->turn_dir = 0;
	else if (keycode == UP)
		game->player->walk_dir = 0;
	else if (keycode == DOWN)
		game->player->walk_dir = 0;
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
	mlx_loop(game->mlx);
	return (0);
}
