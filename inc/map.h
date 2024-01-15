#ifndef MAP_H
# define MAP_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "mlx.h"
# include "cub3d.h"
# include "constance.h"


void renderMap(t_game *game);
int	mapContentAt(float x, float y);
bool isInsideMap(float x, float y);



#endif