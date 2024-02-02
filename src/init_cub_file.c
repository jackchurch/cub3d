#include <fcntl.h>

#include "../inc/map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"

int	is_only_one(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (is_white_space(line[i]) || line[i] == '1')
			i++;
		else
			return (0);
	}
	return (1);
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
	// On this line, remove leading and tailing spaces and tabs (this will need not happen for the map part)
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

/*Remove the C or F from the return string and then remove any leading white space.*/
char	*isolate_element_path(char *str, int i)
{
	char	*temp;
	char	*ret;
	
	temp = ft_substr(str, i, ft_strlen(str));
	ret = ft_strtrim(str, " 	");
	free(temp);
	free(str);
	return (ret);
}

int	init_map(t_map *map, char *line, int i)
{
	int	length;
	int	j;

	j = 0;
	length = ft_strlen(line);
	map->map[i] = malloc(length + 1);
	if (length > map->longest_row)
		map->longest_row = length;
	while (line[j] && line[j] != '\n')
	{
		map->map[i][j] = line[j];
		j++;
	}
	map->rows++;
	if (is_only_one(line))
		return (0);
	return (1);
}

int	do_shit(t_input *input, char *current_line, int i)
{
	char	*str_1;
	int		element_type;

	// Set element type and error if element type identifyer is invalid.
	str_1 = ft_strdup(current_line);
	element_type = discover_element_type(str_1);
	if (element_type == -1)
		return (-1);
	// If a wall (shorter to use not celing and not floor than if NO and SO and WE and EA)
	if (element_type == MAP)
	{
		if (!(init_map(&input->map, current_line, i)))
			return (0);
	}
	else if (element_type != CEILING && element_type != FLOOR)
		ceiling_floor_branch(input, str_1, element_type);
	else // Is ceiling or
		ceiling_floor_branch(input, str_1, element_type);
	free(str_1);
	return (0);
}

t_input	init_cub_file(char *file_name)
{
	int		fd;
	char	*current_line;
	int		i;
	t_input input;

	i = 0;
	ft_memset(&input, 0, sizeof(t_input));
	fd = open_cub_file(file_name);
	current_line = "temp";
	while (current_line != NULL)
	{
		current_line = get_next_line(fd);
		// Skip over any blank lines
		if (current_line[0] == '\n')
			continue ;
		// Do things if the line isn't blank
		do_shit(&input, current_line, i);
		i++;
	}
	close(fd);
	return (input);
}
