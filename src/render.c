
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
			mlx_put_image_to_window(game->mlx, game->win, game->ground,
				width * 50, height * 50);
			if (game->map[height][width] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->slime,
					width * 5, height * 50);
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

void	assign_images(t_game *game)
{
	game->slime = mlx_xpm_file_to_image(game->mlx, "images/slime.xpm",
			&game->player_x, &game->player_y);
	game->ground = mlx_xpm_file_to_image(game->mlx, "images/forestground50.xpm",
			&game->player_x, &game->player_y);
}