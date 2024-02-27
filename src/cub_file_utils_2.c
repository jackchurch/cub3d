/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:06:31 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 17:06:33 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../inc/map.h"
#include "constance.h"
#include "cub3d.h"
#include "cub_file.h"

char	player_spawn(t_map *map, int i, int j, char line)
{
	if (line == 'N' || line == 'S' || line == 'E' || line == 'W')
	{
		map->spawn_loc.y = i;
		map->spawn_loc.x = j;
		if (line == 'S')
			map->rot_angle = M_PI / 2;
		else if (line == 'N')
			map->rot_angle = M_PI * 1.5;
		else if (line == 'E')
			map->rot_angle = M_PI * 2;
		else if (line == 'W')
			map->rot_angle = M_PI;
		map->count.spawn_dir++;
		return (line);
	}
	return (0);
}

/*
Return element type only if element has a space or tab after the last valid char.
ie C345,654,344 will fail.
C   645,421,334 will pass
*/
int	discover_element_type(char *current_line)
{
	char	*line;

	line = ft_strtrim(current_line, " 	");
	if (line[0] == 'C' && is_white_space(line[1]))
		return (CEILING);
	else if (line[0] == 'F' && is_white_space(line[1]))
		return (FLOOR);
	else if (line[0] == 'N' && line[1] == 'O' && is_white_space(line[2]))
		return (NORTH);
	else if (line[0] == 'S' && line[1] == 'O' && is_white_space(line[2]))
		return (SOUTH);
	else if (line[0] == 'E' && line[1] == 'A' && is_white_space(line[2]))
		return (EAST);
	else if (line[0] == 'W' && line[1] == 'E' && is_white_space(line[2]))
		return (WEST);
	return (-1);
}

char	*isolate_element_path(char *str)
{
	char	*ret;
	int		i;
	int		start;

	i = 0;
	while (!(is_white_space(str[i])))
		i++;
	if (str[i] == '\n' || str[i] == '\0')
		return (NULL);
	while (is_white_space(str[i]))
		i++;
	start = i;
	while (str[i])
		i++;
	ret = malloc(i - start);
	i = 0;
	while (str[start] != '\n' && str[start])
		ret[i++] = str[start++];
	ret[i] = '\0';
	free(str);
	return (ret);
}

int	row_update(t_map *map, int length)
{
	int	j;

	j = 0;
	while (j < map->rows)
	{
		map->content[j] = ft_realloc(map->content[j],
				map->longest_row, length + 1);
		ft_memset(map->content[j]
			+ map->longest_row, 0, length - map->longest_row + 1);
		j++;
	}
	return (length);
}
