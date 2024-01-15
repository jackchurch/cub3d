#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "mlx.h"
# include "cub3d.h"


void	drawCeling(t_game *game);
void	renderPlayer(t_game *game);
void	generate3DProjection(t_game *game);

#endif