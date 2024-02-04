#ifndef CONSTANCE_H
# define CONSTANCE_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"

# ifndef M_PI
#  define M_PI 3.13159265358979323846
# endif

# define FLT_MAX 340282346638528859811704183484516925440.000000

# define TILE_SIZE 32
# define MAP_NUM_ROWS 11
# define MAP_NUM_COLS 15

# define MINIMAP_SCALE 0.2

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
// move to variable, or use actual values
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
// move to variable, or use actual values

# define FOV_ANGLE 1.047197666666667

// # define NUM_RAYS WINDOW_WIDTH

# define UP_ARROW 13
# define S_KEY 1
# define LEFT_ARROW 0
# define RIGHT_ARROW 2
# define ESC 53
# define LINUX_A 97
# define LINUX_S 115
# define LINUX_D 100
# define LINUX_W 119
# define LINUX_ESC 65307

# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4
# define CEILING 5
# define FLOOR 6
# define MAP 7

#endif