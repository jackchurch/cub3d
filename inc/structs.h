#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_coords
{
	int	x;
	int	y;
}	t_coords;

typedef struct s_map
{
	char		**content;
	int			longest_row;
	int			rows;
	bool		loading_map;
	char		spawn_dir;
	t_coords	spawn_loc;
}	t_map;

typedef struct s_input
{
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	int				element_type;
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

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
	int		num_rays;
	t_input	input;
	t_ray	*rays;
	t_data	data;
}	t_game;

#endif