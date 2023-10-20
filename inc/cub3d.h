#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
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

# define FOV_ANGLE (60 * (PI_2) / 180))
# define NUM_RAYS (WINDOW_WIDTH)


typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_dir; // -1 for left
	int		walk_dir; // -1 for out of screen
	float	rot_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

typedef	struct s_images
{
	void	*map_ground;
	void	*map_wall;
}	t_images;


typedef	struct s_game
{
	t_player	*player;
	t_images	*images;
	int			map_num_rows;
	int			map_num_cols;
	char		**map;
	void		*mlx;
	void		*win;
	void		*img;
}	t_game;

bool	init_program(t_game *game, char *map_name);
int		safe_exit(t_game *game);
void	init_player(t_game *game);
void	render(t_game *game);

#endif