#ifndef CUB_FILE_H
# define CUB_FILE_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "mlx.h"
# include "cub3d.h"
# include "constance.h"

typedef struct s_map
{
	char	**map;
	int		longest_row;
	int		rows;
}	t_map;

typedef struct s_input
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	int		*ceiling_color;
	int		*floor_color;
	t_map	map;
}	t_input;

bool	init_cub_file(char *file_name);
int		open_cub_file(char *file_name);
bool	is_xpm_file(char *file_name);
char	*remove_tail_whitespace(char *in_string);
void	find_first_char(char *current_line, int *i);
bool	is_white_space(char c);
char	*isolate_element_path(char *str, int i);
int		ceiling_floor_branch(char *current_line, int element_type);

#endif