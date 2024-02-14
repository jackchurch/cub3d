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

# define TILE_SIZE 64

# define MINIMAP_SCALE 0.1

# define FOV_ANGLE 1.047197666666667

# define MAC_W 13
# define MAC_S 1
# define MAC_A 0
# define MAC_D 2
# define MAC_LEFT 123
# define MAC_RIGHT 124
# define MAC_ESC 53
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