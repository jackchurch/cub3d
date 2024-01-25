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
	bool	found_wall_hit;
	float	wall_hit_x;
	float	wall_hit_y;
	int		wall_content;
	float	next_touch_x;
	float	next_touch_y;
	bool	is_vertical;
}	t_wall_hit;

extern t_ray	g_rays[NUM_RAYS];

void	render_rays(t_game *game);
void	wall_hit_params(t_wall_hit *params);
void	ray_cast(t_wall_hit *hit, int stripId,
			float ray_angle, float hit_distance);
void	wall_found(t_wall_hit *orientation, float y_to_check,
			float x_to_check, bool is_vertical);
void	cast_all_rays(void);
void	cast_one_ray(float ray_angle, int stripId,
			t_wall_hit *vertical, t_wall_hit *horizontal);
void	horizontal_intersection(t_wall_hit *horizontal, float ray_angle);
void	vertical_intersection(t_wall_hit *vertical, float ray_angle);
int		is_ray_facing_down(float angle);
int		is_ray_facing_up(float angle);
int		is_ray_facing_right(float angle);
int		is_ray_facing_left(float angle);
void	calculate_steps(float ray_angle, float *xstep,
			float *ystep, char axis);

#endif