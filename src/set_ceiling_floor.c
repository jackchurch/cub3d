/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ceiling_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:18:51 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:18:54 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "map.h"
#include "structs.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"

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
		i++;
	}
	return (false);
}

int	for_each_value(t_input *input, char *value, int element_type)
{
	char	*str;

	str = ft_strtrim(value, " 	");
	if (any_invalid_chars(str) == true || value == NULL)
		input->map.count.invalid_char++;
	else if (!(is_xpm_file(str)))
		input->map.count.not_xpm++;
	else
	{
		input->paths[element_type] = ft_strdup(str);
		input->complete++;
	}
	free(str);
	return (0);
}

unsigned int	ceiling_floor_color(t_input *input, char *str)
{
	char	**values;
	int		r;
	int		g;
	int		b;
	int		i;

	values = ft_split(str, ',');
	i = -1;
	while (++i < 3)
	{
		values[i] = ft_strtrim(values[i], " 	");
		if (any_invalid_chars(values[i]))
			input->map.count.colors = 1;
	}
	r = ft_atoi(values[0]);
	g = ft_atoi(values[1]);
	b = ft_atoi(values[2]);
	while (*values)
		free(*values++);
	input->complete++;
	if (r > 255 || g > 255 || b > 255)
		return (0);
	return (r * 256 * 256 + g * 256 + b);
}

int	get_count(t_input *input, char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == ',' && ++count > 2)
		{
			input->map.count.comma++;
			return (1);
		}
	}
	return (0);
}

int	ceiling_floor_branch(t_input *input, char *current_line, int element_type)
{
	char	*str;

	if (element_type < 0)
		return (-1);
	str = isolate_element_path(current_line);
	if (str == NULL)
		input->map.count.invalid_char++;
	if (get_count(input, str))
	{
		free(str);
		return (-1);
	}
	if (element_type == FLOOR)
		input->floor_color = ceiling_floor_color(input, str);
	else if (element_type == CEILING)
		input->ceiling_color = ceiling_floor_color(input, str);
	else
		for_each_value(input, str, element_type);
	free(str);
	return (0);
}
