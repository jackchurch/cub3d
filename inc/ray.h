#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
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
	float	distance;
	bool	found_wall_hit;
	float	wall_hit_x;
	float	wall_hit_y;
	int		wall_content;
	float	next_touch_x;
	float	next_touch_y;
	bool	is_vertical;
}	t_wall_hit;

typedef struct s_axis
{
	float				x_step;
	float				y_step;
	float				x_intercept;
	float				y_intercept;
	float				next_touch_x;
	float				next_touch_y;
	float				x_to_check;
	float				y_to_check;
}	t_axis;

extern t_ray	g_rays[NUM_RAYS];

void		render_rays(t_game *game);
void		ray_cast(t_wall_hit *hit, int stripId, float ray_angle);
void		wall_found(t_wall_hit *orientation, float y_to_check,
				float x_to_check, bool is_vertical);
void		find_intercept(t_wall_hit *orientation, t_axis *axis,
				float ray_angle, char dir);
void		cast_all_rays(void);
void		cast_one_ray(float ray_angle, int stripId);
t_wall_hit	horizontal_intersection(float ray_angle);
t_wall_hit	vertical_intersection(float ray_angle);
int			is_ray_facing_down(float angle);
int			is_ray_facing_up(float angle);
int			is_ray_facing_right(float angle);
int			is_ray_facing_left(float angle);
void		calculate_steps(float ray_angle, float *xstep,
				float *ystep, char axis);

#endif