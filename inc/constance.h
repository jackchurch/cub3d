#ifndef CONSTANCE_H
# define CONSTANCE_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define FLT_MAX 340282346638528859811704183484516925440.000000

# define TILE_SIZE 64
# define MAP_NUM_ROWS 11
# define MAP_NUM_COLS 15

# define MINIMAP_SCALE 0.2

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
// move to variable, or use actual values
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
// move to variable, or use actual values

# define FOV_ANGLE_WORKINGS_OUT (60 * (M_PI / 180))
// move to variable, or use actual values

# define FOV_ANGLE 1.047197666666667

# define NUM_RAYS WINDOW_WIDTH

# define UP_ARROW 13
# define S_KEY 1
# define LEFT_ARROW 0
# define RIGHT_ARROW 2
# define ESC 53
# define LINUX_A 38
# define LINUX_S 39
# define LINUX_D 40
# define LINUX_W 25
# define LINUX_ESC 9

# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

#endif