#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include "structs.h"
# include <math.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "constance.h"
# include "ray.h"
# include "cub_file.h"

bool	init_window(t_game *game);

// main.c
void	safe_exit(t_game *game);

// To sort
void	render(t_game *game);

int		update(t_game *game);

#endif