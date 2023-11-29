#include "../inc/cub3d.h"


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
			mlx_pixel_put(game->mlx, game->win, i, j, rect->color);
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
		mlx_pixel_put(game->mlx, game->win, round(currentX), round(currentY), color);
        currentX += xIncrement;
        currentY += yIncrement;
    }
}
