#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "constance.h"
# include "draw.h"

//extern t_ray	rays[game->num_rays];

void		render_rays(t_game *game);
void		ray_cast(t_game *game, t_wall_hit *hit,
				int stripId, float ray_angle);
void		wall_found(t_game *game, t_wall_hit *orientation, t_axis axis, bool is_vertical);
void		find_intercept(t_axis *axis, float ray_angle, char dir);
void		cast_all_rays(t_game *game);
void		cast_one_ray(t_game *game, float ray_angle, int stripId);
t_wall_hit	horizontal_intersection(t_game *game, float ray_angle);
t_wall_hit	vertical_intersection(t_game *game, float ray_angle);
int			is_ray_facing_down(float angle);
int			is_ray_facing_up(float angle);
int			is_ray_facing_right(float angle);
int			is_ray_facing_left(float angle);
void		calculate_steps(float ray_angle, t_axis *axis, char dir);

#endif