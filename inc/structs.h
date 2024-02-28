/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:21:37 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:21:39 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "constance.h"

typedef struct s_coords
{
	int	x;
	int	y;
}	t_coords;

typedef struct s_image
{
	void		*img;
	int			*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	t_coords	loc;
}	t_image;

typedef struct s_count
{
	int	spawn_dir;
	int	valid;
	int	colors;
	int	invalid_char;
	int	comma;
	int	not_xpm;
	int	filepath;
}	t_count;

typedef struct s_map
{
	char		**content;
	int			longest_row;
	int			rows;
	char		spawn_dir;
	t_coords	spawn_loc;
	float		rot_angle;
	t_count		count;
}	t_map;

typedef struct s_input
{
	char			*paths[4];
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	int				element_type;
	int				complete;
	t_map			map;
}	t_input;

typedef struct s_rectangle
{
	int				x;
	int				y;
	int				width;
	int				height;
	unsigned int	color;
}	t_rectangle;

typedef struct s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	unsigned int	color;
}	t_line;

typedef struct s_line_math
{
	int		delta_x;
	int		delta_y;
	int		longest_side_length;
	float	x_increment;
	float	y_increment;
	float	current_x;
	float	current_y;
	int		abs_x;
	int		abs_y;
}	t_line_math;

typedef struct s_tile
{
	int				x;
	int				y;
	unsigned int	color;
}	t_tile;

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
	float	x_step;
	float	y_step;
	float	x_intercept;
	float	y_intercept;
	float	next_touch_x;
	float	next_touch_y;
	float	x_to_check;
	float	y_to_check;
}	t_axis;

typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	int		strafe_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_update
{
	float	refresh_rate;
	int		end_game;
	int		animate;
}	t_update;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			num_rays;
	int			tile_size;
	t_image		walls[4];
	int			texture[4][TILE_SIZE * TILE_SIZE];
	t_update	update;
	t_input		input;
	t_ray		*rays;
	t_data		data;
}	t_game;

#endif
