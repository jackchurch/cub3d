#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define	FLT_MAX 340282346638528859811704183484516925440.000000

# define	TILE_SIZE 64
# define	MAP_NUM_ROWS 11
# define	MAP_NUM_COLS 15

# define	MINIMAP_SCALE 0.2

# define	WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE) 
# define	WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define	FOV_ANGLE_workings_out (60 * (M_PI / 180)) 
# define	FOV_ANGLE 1.047197666666667

# define	NUM_RAYS WINDOW_WIDTH

# define	UP_ARROW 13
# define	S_KEY 1
# define	LEFT_ARROW 0
# define	RIGHT_ARROW 2
# define	ESC 53

# define	NORTH 1
# define	EAST 2
# define	SOUTH 3
# define	WEST 4



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

struct s_player
{
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
}	t_player;

struct s_ray
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	int wasHitVertical;
	int isRayFacingUp;
	int isRayFacingDown;
	int isRayFacingLeft;
	int isRayFacingRight;
	int wallHitContent;
}	rays[NUM_RAYS];

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

// init.c
// void setup();




#endif