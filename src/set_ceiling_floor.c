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
	// While string exists
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

int	for_each_value(t_input *input, char *value, int i, int element_type)
{
	char	*str;
	int		color;

	// Remove leading and tailing whitespace for each number (R G B)
	str = ft_strtrim(value, " 	");
	// If no numbers error; and also if number at index [0] and index [2] but white space at index [1], error as the number has a space in it. 
	if (any_invalid_chars(str) == true)
		return (-1);
	color = ft_atoi(str);
	if (element_type == CEILING || element_type == FLOOR)
	{
		if (color < 0 || color > 255)
			return (-1);
		if (element_type == CEILING)
			input->ceiling_color[i] = color;
		else
			input->floor_color[i] = color;
	}
	else
		input_path(input, str, element_type);
	return (0);
}

int	ceiling_floor_branch(t_input *input, char *current_line, int element_type)
{
	char	*str;
	char	**values;
	int		i;

	i = 0;
	// str = Remove the C or F from the return string and then remove any leading white space.
	str = isolate_element_path(current_line, 1);
	// Split the string based on commas, this also removes the commas
	values = ft_split(str, ',');
	free(str);
	while (values[i] != NULL)
	{
		// if there are more than 3 value, then the RGB is invalid
		// TODO: if it is 0 or 1 we also need to error before the while loop starts. ie `If number of strings is != 2` error
		if (i == 3)
			return (-1);
		if (for_each_value(input, values[i], i, element_type) == -1)
			return (-1);
		i++;
	}
	return (0);
}
