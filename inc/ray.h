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
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
}	t_ray;

typedef struct s_wall_hit
{
	float	xstep;
	float	ystep;
	int		*found_wall_hit;
	float	*wall_hit_x;
	float	*wall_hit_y;
	int		*wall_content;
	float	next_touch_x;
	float	next_touch_y;
	int		is_vertical;
}	t_wall_hit;

extern t_ray	g_rays[NUM_RAYS];

void	renderRays(t_game *game);
void	castAllRays(void);

#endif