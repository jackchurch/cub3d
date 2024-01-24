#include <fcntl.h>

#include "../inc/map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"

int	num_of_str(char **str)
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

int	any_inside_whitespace(char *str)
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
				return (-1);
			digit_found = true;
		}
		else if (is_white_space(str[i]))
			white_space_found = true;
		else if (!is_white_space(str[i] && !ft_isdigit(str[i])))
			return (-1);
		i++;
	}
}

int	valid_range(int i)
{
	if (i >= 0 && i <= 255)
		return (1);
	return (-1);
}

int	valid_nums(char **str)
{
	int		i;
	char	*one_colour;
	int		rgb[3];

	i = 0;
	if (num_of_str(str) != 3)
		return (-1);
	while (i < 3)
	{
		one_colour = ft_strtrim(str[i], " 	");
		if (any_inside_whitespace(one_colour) == -1)
			return (-1);
		if (ft_strlen(one_colour) >= 4)
			return (-1);
		rgb[i] = ft_atoi(one_colour);
		if (valid_range(rgb[i]) == -1)
			return (-1);
		free(one_colour);
		free(str[i]);
		i++;
		// add to struct
	}

}

int	celing_floor_branch(char *current_line, int element_type)
{
	char	**str;
	int		;

	str = ft_split(current_line, ',');

	if (valid_nums(str) < 0)
		return (-1);
	return (0);
}