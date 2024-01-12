#include "../inc/cub3d.h"
#include "../inc/draw.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return ;
	// vvvvvv this is the color buffer in your notes vvvvvvv
	dst = (data->addr + (y * data->line_length + x * data->bits_per_pixel / 8));
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

	drawn.absX = abs(drawn.deltaX);
	drawn.absY = abs(drawn.deltaY);
	drawn.deltaX = (line->x1 - line->x0);
	drawn.deltaY = (line->y1 - line->y0);
	if (drawn.absX) >= drawn.absY)
		drawn.longestSideLength = drawn.absX;
	else
		drawn.longestSideLength = drawn.absY;
	drawn.xIncrement = drawn.deltaX / (float)drawn.longestSideLength;
	drawn.yIncrement = drawn.deltaY / (float)drawn.longestSideLength;
	drawn.currentX = line->x0;
	drawn.currentY = line->y0;
	i = -1;
	while (++i < drawn.longestSideLength)
	{
		my_mlx_pixel_put(&game->data, round(drawn.currentX),
			round(drawn.currentY), line->color);
		drawn.currentX += drawn.xIncrement;
		drawn.currentY += drawn.yIncrement;
	}
}
