#include "../inc/cub3d.h"

void	assign_images(t_game *game)
{
	int	x;
	int	y;

	game->images->map_ground = mlx_xpm_file_to_image(game->mlx, 
			"images/forestground50.xpm", &x, &y);
	game->images->map_wall = mlx_xpm_file_to_image(game->mlx, 
			"images/tree50.xpm", &x, &y);
}

void	render_map(t_game *game)
{
	int	i;
	int	j;
	int	tile_x;
	int	tile_y;
	i = 0;
	while (i < game->map_num_rows)
	{
		j = 0;
		while (j < game->map_num_cols)
		{
			tile_x = j * TILE_SIZE;
			tile_y = j * TILE_SIZE;

			i++;
		}
	}
}

void	render(t_game *game)
{
	render_map(game);
}