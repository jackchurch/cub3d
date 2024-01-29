#include <fcntl.h>

#include "../inc/map.h"
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

int	valid_spacing(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		
	}
}

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

int	for_each_value(char *value, int i, t_map *map, int element_type)
{
	char	*str;


	// Remove leading and tailing whitespace for each number (R G B)
	str = ft_strtrim(value, " 	");
	// If no numbers error; and also if number at index [0] and index [2] but white space at index [1], error as the number has a space in it. 
	if (any_invalid_chars(str) == true)
		return (-1);
	if (element_type == CELING)
	{
		// Set struct with colour for R G Or B
		map->celing[i] = ft_atoi(str);
		if (valid_range(map->celing[i]) == false)
			return (-1);
	}
	else
	{
		// WTF, can I use function pointers to set celing or floor
		map->celing[i] = ft_atoi(str);
		if (valid_range(map->celing[i]) == false)
		return (-1);
	}
}

int	celing_floor_branch(char *current_line, int element_type)
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
		if (for_each_value(values[i], i, map, element_type) == -1)
			return (-1);
	}
	return (0);
}