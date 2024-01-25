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

int	for_each_value(char *value, int i, t_map *map, int element_type)
{
	char	*str;

	str = ft_strtrim(value, " 	");
	if (any_invalid_chars(str) == true)
		return (-1);
	if (element_type == CELING)
	{
		map->celing[i] = ft_atoi(str);
		if (valid_range(map->celing[i]) == false)
			return (-1);
	}
	else
	{
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
	str = isolate_element_path(current_line, 1);
	values = ft_split(str, ',');
	free(str);
	while (values[i] != NULL)
	{
		if (i == 3)
			return (-1);
		if (for_each_value(values[i], i, map, element_type) == -1)
			return (-1);
	}
	return (0);
}