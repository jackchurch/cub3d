#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "constance.h"

struct	s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_data	data;
} t_game;

bool	init_window(t_game *game);

// main.c
void	safe_exit(t_game *game);

// To sort
void	render(t_game *game);

#endif