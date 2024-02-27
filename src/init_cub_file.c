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
		map->content = ft_realloc(map->content,
				sizeof(char *) * i, sizeof(char *) * (i + 1));
	if (line[length - 1] == '\n')
		length--;
	if (length > map->longest_row)
		map->longest_row = row_update(map, length);
	map->content[i] = malloc(length + 1);
	j = -1;
	while (++j < length)
	{
		map->content[i][j] = line[j];
		map->spawn_dir = player_spawn(map, i, j, line[j]);
	}
	map->content[i][j] = '\0';
	map->rows++;
	return (1);
}

int	do_shit(t_input *input, char *current_line)
{
	char	*str_1;

	str_1 = ft_strdup(current_line);
	if (input->complete < NUM_OF_ELEMENTS)
	{
		input->element_type = discover_element_type(str_1);
		ceiling_floor_branch(input, str_1, input->element_type);
	}
	else if (input->complete == NUM_OF_ELEMENTS)
		init_map(&input->map, current_line);
	if (input->element_type == -1)
		return (-1);
	return (0);
}

t_input	init_cub_file(char *file_name)
{
	int			fd;
	char		*current_line;
	t_input		input;
	t_coords	loc;

	ft_memset(&input, 0, sizeof(t_input));
	ft_memset(&input.map, 0, sizeof(t_map));
	ft_memset(&loc, 0, sizeof(t_coords));
	input.map.spawn_loc = loc;
	fd = open_cub_file(file_name);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		while (current_line[0] == '\n')
			current_line = get_next_line(fd);
		if (do_shit(&input, current_line) < 0)
			break ;
		current_line = get_next_line(fd);
	}
	free(current_line);
	close(fd);
	return (input);
}
