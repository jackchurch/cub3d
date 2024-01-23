#include "../inc/cub3d.h"
#include "../inc/draw.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return ;
	// vvvvvv this is the color buffer in your notes vvvvvvv
	dst = (data->addr + (y * data->line_length + x * data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	drawRect(t_game *game, t_rectangle *rect)
{
	int	i;
	int	j;
	
	i = rect->x;
	while (i <= (rect->x + rect->width))
	{
		j = rect->y;
		while (j <= (rect->y + rect->height))
		{
			my_mlx_pixel_put(&game->data, i, j, rect->color);
			j++;
		}
		i++;
	}
	return ;
}

void	drawLine(t_game *game, const t_line *line)
{
	t_line_math	drawn;
	int			i;

	drawn.abs_x = abs(drawn.delta_x);
	drawn.abs_y = abs(drawn.delta_y);
	drawn.delta_x = (line->x1 - line->x0);
	drawn.delta_y = (line->y1 - line->y0);
	if (drawn.abs_x) >= drawn.abs_y)
		drawn.longest_side_length = drawn.abs_x;
	else
		drawn.longest_side_length = drawn.abs_y;
	drawn.x_increment = drawn.delta_x / (float)drawn.longest_side_length;
	drawn.y_increment = drawn.delta_y / (float)drawn.longest_side_length;
	drawn.current_x = line->x0;
	drawn.current_y = line->y0;
	i = -1;
	while (++i < drawn.longest_side_length)
	{
		my_mlx_pixel_put(&game->data, round(drawn.current_x),
			round(drawn.current_y), line->color);
		drawn.current_x += drawn.x_increment;
		drawn.current_y += drawn.y_increment;
	}
}