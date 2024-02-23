#ifndef DRAW_H
# define DRAW_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "cub3d.h"

void	draw_rect(t_game *game, t_rectangle *rect);
void	draw_line(t_game *game, const t_line *line);

#endif