#ifndef MAP_H
# define MAP_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "cub3d.h"
# include "constance.h"

typedef struct s_tile
{
	int	x;
	int	y;
	int	color;
}	t_tile;

void	render_map(t_game *game);
int		map_content_at(float x, float y);
void	tile_rect_init(t_rectangle *map_tile_rect, const t_tile tile);
bool	is_inside_map(float x, float y);

#endif
