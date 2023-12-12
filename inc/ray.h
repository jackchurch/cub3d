#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "constance.h"
# include "draw.h"

typedef struct s_ray
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
}	ray_t;

extern ray_t	rays[NUM_RAYS];

void	renderRays(t_game *game);
void	castAllRays(void);

#endif