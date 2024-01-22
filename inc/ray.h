#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "constance.h"
# include "draw.h"

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		isRayFacingRight;
	int		wall_hit_content;
}	t_ray;

typedef struct s_wall_hit
{
	float	xstep;
	float	ystep;
	int		*foundWallHit;
	float	*wall_hit_x;
	float	*wall_hit_y;
	int		*wallContent;
	float	nextTouchX;
	float	nextTouchY;
	int		isVertical;
}	t_wall_hit;

extern t_ray	rays[NUM_RAYS];

void	renderRays(t_game *game);
void	castAllRays(void);

#endif