#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "cub3d.h"

void	draw_ceiling(t_game *game);
void	render_player(t_game *game);
void	generate_3d_projection(t_game *game);
int		color_assignment(int i);

#endif