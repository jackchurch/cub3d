#ifndef DRAW_H
# define DRAW_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "cub3d.h"

typedef struct s_rectangle
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rectangle;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
}	t_line;

typedef struct s_line_math
{
	int		delta_x;
	int		delta_y;
	int		longest_side_length;
	float	x_increment;
	float	y_increment;
	float	current_x;
	float	current_y;
	int		abs_x;
	int		abs_y;
}	t_line_math;

void	drawRect(t_game *game, t_rectangle *rect);
void	drawLine(t_game *game, const t_line *line);

#endif