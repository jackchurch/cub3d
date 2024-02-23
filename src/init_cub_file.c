/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:16:40 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:41 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"

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

	if (is_only_one(current_line))
		return (MAP);
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
	while (str[i] && !(is_white_space(str[i])))
		i++;
	ret = malloc(i - start);
	i = 0;
	while (str[start] != '\n' && str[start])
		ret[i++] = str[start++];
	ret[i] = '\0';
	free(str);
	return (ret);
}

int	init_map(t_map *map, char *line)
{
	int		length;
	int		j;
	int		i;

	length = ft_strlen(line);
	i = map->rows;
	if (!map->content)
		map->content = malloc(sizeof(char *));
	else
		map->content = ft_realloc(map->content, sizeof(char *) * i, sizeof(char *) * (i + 1));
	length = ft_strlen(line);
	if (line[length - 1] == '\n')
		length--;
	if (length > map->longest_row)
	{
		j = 0;
		while (j < i)
		{
			map->content[j] = ft_realloc(map->content[j], map->longest_row, length + 1);
			ft_memset(map->content[j] + map->longest_row, 0, length - map->longest_row + 1);
			j++;
		}
		map->longest_row = length;
	}
	map->content[i] = malloc(length + 1);
	j = 0;
	while (j < length)
	{
		map->content[i][j] = line[j];
		map->spawn_dir = player_spawn(map, i, j, line[j]);
		j++;
	}
	map->content[i][j] = '\0';
	map->rows++;
	return (1);
}

int	do_shit(t_input *input, char *current_line)
{
	char	*str_1;

	str_1 = ft_strdup(current_line);
	if (input->map.loading_map == false)
		input->element_type = discover_element_type(str_1);
	if (input->element_type == -1)
		return (-1);
	if (input->element_type == MAP || input->map.loading_map == true)
	{
		if (input->map.loading_map == false)
			input->map.loading_map = true;
		init_map(&input->map, current_line);
	}
	else
		ceiling_floor_branch(input, str_1, input->element_type);
	return (0);
}

t_input	init_cub_file(char *file_name)
{
	int			fd;
	char		*current_line;
	t_input 	input;
	t_coords	loc;

	ft_memset(&input, 0, sizeof(t_input));
	ft_memset(&input.map, 0, sizeof(t_map));
	ft_memset(&loc, 0, sizeof(t_coords));
	input.map.spawn_loc = loc;
	input.map.loading_map = false;
	input.map.spawn_dir = 0;
	input.map.rows = 0;
	fd = open_cub_file(file_name);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		while (current_line[0] == '\n')
			current_line = get_next_line(fd);
		do_shit(&input, current_line);
		current_line = get_next_line(fd);
		if (input.map.loading_map == true && is_only_one(current_line))
			input.map.loading_map = false;
	}
	free(current_line);
	close(fd);
	return (input);
}
