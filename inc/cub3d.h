#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define FALSE 0
# define TRUE 1

# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ESC 53

# define FOV_ANGLE (60 * M_PI / 180)
# define ONE_PI M_PI
# define TWO_PI (M_PI * 2)

# define TILE_SIZE 64
# define PLAYER_SIZE 1
# define MINIMAP_SCALE 1

typedef struct s_rectangle
{
	int	x;
	int	y;
	int	width;
	int	height;
	int color;
}	t_rectangle;

typedef struct s_line
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	color;
}	t_line;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

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
	
	t_color color;
}	t_player;


typedef	struct s_game
{
	t_player	*player;
	int		map_num_rows;
	int		map_num_cols;
	int		window_width;
	int		window_height;
	int		num_rays;
	char	**map;
	void	*mlx;
	void	*win;
	void	*img;
}	t_game;

// init_mlx.c
bool	init_program(t_game *game, char *map_name);

// Main.c
int		safe_exit(t_game *game);
int		keys(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);

// exit.c
int		safe_exit(t_game *game);

// render.c
void	render(t_game *game);
void	render_player(t_game *game);


#endif