
#include <stdbool.h>
#include <fcntl.h>
#include "../inc/cub3d.h"

// void	render_player(t_game *game)
// {
// 	return ;
// }

void	render_map(t_game *game)
{
	int	height;
	int	width;

	height = 0;
	while (game->map[height])
	{
		width = 0;
		while (game->map[height][width])
		{
			mlx_pixel_put(game->mlx, game->win, width * TILE_SIZE, height * TILE_SIZE, 0x0012faff);
			width++;
		}
		height++;
	}

	return ;
}

void	render(t_game *game)
{
	render_map(game);
	// render_player(game);
	return ;
}
