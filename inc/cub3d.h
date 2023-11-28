#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define ONE_PI M_PI
# define TWO_PI (ONE_PI * 2)
# define HALF_PI (M_PI * 0.5)

# define TILE_SIZE 64
# define MAP_NUM_ROWS 11
# define MAP_NUM_COLS 15

# define MINIMAP_SCALE 0.2

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE) 
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (ONE_PI / 180))

# define NUM_RAYS WINDOW_WIDTH

# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))


# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define ESC 53

typedef struct s_game
{
	void	*mlx;
	void	*win;
} t_game;

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
	int x0;
	int y0;
	int x1;
	int y1;
	int color;
}	t_line;

typedef struct s_player {
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
} t_player;



// player.c
void setup(t_player *player);
void	movePlayer(t_game *game, t_player *player);
void	renderPlayer(t_game *game, t_player *player);


bool mapHasWallAt(float x, float y);
void drawLine(t_game *game, t_line *line);
void	drawRect(t_game *game, t_rectangle *rect);

#endif