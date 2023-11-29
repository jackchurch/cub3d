#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <math.h>
# include <stdbool.h>
# include <float.h>

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

struct Player {
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
} player;

bool	init_window(t_game *game);

// main.c
void	safe_exit(t_game *game);


// maths.c
float normalizeAngle(float rayAngle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);

// map.c
void renderMap(t_game *game);
int	mapContentAt(float x, float y);


// To sort
void	render(t_game *game);
void	drawRect(t_game *game, t_rectangle *rect);

// render_utils.c
void	drawRect(t_game *game, t_rectangle *rect);
void drawLine(t_game *game, t_line *line);

// render.c
void drawCeling(t_game *game);
void	renderPlayer(t_game *game);

// player.c
// void	movePlayer(t_game *game);



#endif