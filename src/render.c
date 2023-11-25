
#include <stdbool.h>
#include <fcntl.h>
#include "../inc/cub3d.h"


void	draw_rect(t_game *game, t_rectangle *rect)
{
	int	i;
	int	j;
	
	i = rect->x;
	while (i <= (rect->x + rect->width))
	{
		j = rect->y;
		while (j <= (rect->y + rect->height))
		{
			mlx_pixel_put(game->mlx, game->win, i, j, rect->color);
			j++;
		}
		i++;
	}
	return ;
}

// TODO
void	draw_line(t_game *game, t_line *line)
{
	mlx_pixel_put(game->mlx, game->win, line->end_x, line->end_y, line->color);
	return ;
}

int	ft_tile_color(char c)
{
	if (c == '1')
		return (0x000000FF);
	else
		return (0x00FFFFFF);
}

void	render_map(t_game *game)
{
	int	i;
	int	j;
	t_rectangle	rect;

	i = 0;
	while (i < game->map_num_rows)
	{
		j = 0;
		while (j < game->map_num_cols)
		{
			rect.x = j * TILE_SIZE * MINIMAP_SCALE;
			rect.y = i * TILE_SIZE * MINIMAP_SCALE;
			rect.width = TILE_SIZE * MINIMAP_SCALE;
			rect.height = TILE_SIZE * MINIMAP_SCALE;
			rect.color = ft_tile_color(game->map[i][j]);

			// printf("tile_color %d game->map[%d][%d]\n", rect.color, i, j);
			draw_rect(game, &rect);
			j++;
		}
		i++;
	}
}

void	render_player(t_game *game)
{
	t_rectangle	rect;
	t_line		line;

	rect.x = game->player->x * MINIMAP_SCALE;
	rect.y = game->player->y * MINIMAP_SCALE;
	rect.width = game->player->width * MINIMAP_SCALE;
	rect.height = game->player->height * MINIMAP_SCALE;
	rect.color = 0x000000FF;
	draw_rect(game, &rect);

	line.start_x = game->player->x * MINIMAP_SCALE;
	line.start_y = game->player->y * MINIMAP_SCALE;
	line.end_x = (game->player->x + cos(game->player->rot_angle) * 50) * MINIMAP_SCALE;
	line.end_y = (game->player->y + sin(game->player->rot_angle) * 50) * MINIMAP_SCALE;
	line.color = 0x000000FF;
	draw_line(game, &line);
}

// void	move_player(t_game *game)
// {
	
// }

void	render(t_game *game)
{
	render_map(game);
	// render_rays(game);
	render_player(game);

	return ;
}