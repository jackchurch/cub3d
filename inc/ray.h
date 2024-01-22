#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "constance.h"
# include "draw.h"

typedef struct s_ray
{
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	int		wasHitVertical;
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		isRayFacingRight;
	int		wallHitContent;
}	t_ray;

typedef struct s_wall_hit
{
	float	xstep;
	float	ystep;
	int		*foundWallHit;
	float	*wallHitX;
	float	*wallHitY;
	int		*wallContent;
	float	nextTouchX;
	float	nextTouchY;
	int		isVertical;
}	t_wall_hit;

extern t_ray	rays[NUM_RAYS];

void	renderRays(t_game *game);
void	castAllRays(void);

#endif