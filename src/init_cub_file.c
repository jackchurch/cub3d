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
#include "maths.h"

int	map_transfer(t_map *map, int i, int j, int temp_i)
{
	if (map->temp[temp_i] == '\n' && j < map->longest_row)
		map->content[i][j] = ' ';
	else if (j < map->longest_row)
	{
		map->content[i][j] = map->temp[temp_i];
		map->spawn_dir = player_spawn(map, i, j);
		temp_i++;
	}
	if (i == map->rows - 1 && map->content[i][j + 1] != '\0')
		map->content[i][j + 1] = '\0';
	return (temp_i);
}

void	finalize_map(t_map *map)
{
	int	i;
	int	j;
	int	temp_i;

	i = -1;
	temp_i = 0;
	if (map->count.map_exists == 0)
		return ;
	map->content = malloc(sizeof(char *) * map->rows + 1);
	while (++i < map->rows)
	{
		j = -1;
		map->content[i] = malloc(map->longest_row + 1);
		while (++j < map->longest_row && map->temp[temp_i] != '\0')
			temp_i = map_transfer(map, i, j, temp_i);
		temp_i++;
		map->content[i][map->longest_row] = '\0';
	}
	free(map->temp);
}

int	init_map(t_map *map, char *line)
{
	char	*content;
	int		len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (!map->temp)
	{
		map->temp = malloc(len + 1);
		ft_strlcpy(map->temp, line, len + 1);
	}
	else
	{
		content = ft_strjoin(map->temp, line);
		free(map->temp);
		map->temp = malloc(ft_strlen(content) + 1);
		ft_strlcpy(map->temp, content, ft_strlen(content) + 1);
		free(content);
	}
	map->rows++;
	if (len > map->longest_row)
		map->longest_row = len;
	map->count.map_exists = 1;
	return (1);
}

int	do_shit(t_input *input, char *current_line)
{
	char	*str_1;

	if (input->complete < NUM_OF_ELEMENTS)
	{
		str_1 = ft_strdup(current_line);
		input->element_type = discover_element_type(str_1);
		ceiling_floor_branch(input, str_1, input->element_type);
	}
	else if (input->complete >= NUM_OF_ELEMENTS)
	{
		init_map(&input->map, current_line);
		input->complete++;
	}
	if (input->element_type < 0)
	{
		input->map.count.invalid_char++;
		return (-1);
	}
	free(current_line);
	return (0);
}

t_input	init_cub_file(t_game *game, char *file_name)
{
	int			fd;
	char		*current_line;
	t_input		input;

	eff_norm(&input);
	if (open_cub_file(file_name, &fd) < 0)
		bad_file(game);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		while (current_line[0] == '\n' && input.complete <= NUM_OF_ELEMENTS)
		{
			free(current_line);
			current_line = get_next_line(fd);
		}
		if (do_shit(&input, current_line) < 0)
			break ;
		current_line = get_next_line(fd);
	}
	free(current_line);
	finalize_map(&input.map);
	if (map_parsing(&input, input.map.content))
		safe_exit(game);
	close(fd);
	return (input);
}
