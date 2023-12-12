#include "../inc/cub3d.h"
#include "../inc/draw.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	if (x < 0 || y < 0 || x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return ;
	// vvvvvv this is the color buffer in your notes vvvvvvv
	dst = (data->addr + (y * data->line_length + x * data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void drawLine(t_game *game, t_line *line) {
    
	int x0 = line->x0;
	int y0 = line->y0;
	int x1 = line->x1;
	int y1 = line->y1;
	int color = line->color;
	int deltaX = (x1 - x0);
    int deltaY = (y1 - y0);

    int longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    float xIncrement = deltaX / (float)longestSideLength;
    float yIncrement = deltaY / (float)longestSideLength;

    float currentX = x0;
    float currentY = y0;

    for (int i = 0; i < longestSideLength; i++) {
		my_mlx_pixel_put(&game->data, round(currentX), round(currentY), color);
        currentX += xIncrement;
        currentY += yIncrement;
    }
}