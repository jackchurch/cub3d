#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ESC 53
# define TILE_SIZE 32
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 400

typedef	struct s_game
{
	int		map_height;
	int		map_width;

	char	**map;
	void	*mlx;
	void	*win;
	void	*img;
	void	*slime;
}	t_game;

int a = 5;

#endif