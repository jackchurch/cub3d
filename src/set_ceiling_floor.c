#include <fcntl.h>

#include "map.h"
#include "structs.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"

int	num_of_strs(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

/* int	valid_spacing(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		
	}
} */

/*
This needs some work. 

Needs to have these return true for invalid_char
`4 5`

Needs to allow these to return false for no invalid char found
` 45`
`45 `

using 2 booleans to help rember what previously found. 
*/
bool	any_invalid_chars(char *str)
{
	int		i;
	bool	digit_found;
	bool	white_space_found;

	i = 0;
	white_space_found = false;
	digit_found = false;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
		{
			if (digit_found == true && white_space_found == true)
				return (true); 
			digit_found = true;
		}
		else if (is_white_space(str[i]))
			white_space_found = true;
		else if (!is_white_space(str[i] && !ft_isdigit(str[i])))
			return (true);
		i++;
	}
	return (false);
}

bool	valid_range(int i)
{
	if (i >= 0 && i <= 255)
		return (true);
	return (false);
}

void	input_path(t_input *input, char *path, int element_type)
{
	if (element_type == NORTH)
		input->north_path = ft_strdup(path);
	if (element_type == SOUTH)
		input->south_path = ft_strdup(path);
	if (element_type == EAST)
		input->east_path = ft_strdup(path);
	if (element_type == WEST)
		input->west_path = ft_strdup(path);
}

int	for_each_value(t_input *input, char *value, int element_type)
{
	char	*str;

	str = ft_strtrim(value, " 	");
	if (any_invalid_chars(str) == true)
		return (-1);
	input_path(input, str, element_type);
	free(str);
	return (0);
}

unsigned int	ceiling_floor_color(char *str)
{
	char	**values;
	int		r;
	int		g;
	int		b;

	values = ft_split(str, ',');
	r = ft_atoi(values[0]);
	g = ft_atoi(values[1]);
	b = ft_atoi(values[2]);
	while (*values)
		free(*values++);
	if (r > 255 || g > 255 || b > 255)
		return (0);
	return (r * 256 * 256 + g * 256 + b);
}

int	ceiling_floor_branch(t_input *input, char *current_line, int element_type)
{
	char	*str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	str = isolate_element_path(current_line);
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		if (count > 2)
			return (-1);
		i++;
	}
	if (element_type != FLOOR && element_type != CEILING)
		for_each_value(input, str, element_type);
	else if (element_type == FLOOR)
		input->floor_color = ceiling_floor_color(str);
	else if (element_type == CEILING)
		input->ceiling_color = ceiling_floor_color(str);
	free(str);
	return (0);
}
