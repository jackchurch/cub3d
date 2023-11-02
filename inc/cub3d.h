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
# define TILE_SIZE 50
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 512
# define PLAYER_SIZE 10

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
	int		map_height;
	int		map_width;
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

// exit.c
int		safe_exit(t_game *game);

// render.c
void	render(t_game *game);


#endif