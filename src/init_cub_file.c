#include <fcntl.h>

#include "../inc/map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"

void	*reallocate(void *ptr, int size)
{
	void	*ret;

	if (!ptr)
		return (NULL);
	ret = malloc(size);
	ret = ft_memcpy(ret, ptr, size);
	free(ptr);
	return (ret);
}

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
	{
		printf("Map Element Retrieved\n");
		return (MAP);
	}
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

int	count_rows(int fd)
{
	int		rows;
	char	*line;

	rows = 1;
	line = get_next_line(fd);
	while (!(is_only_one(line)))
	{
		rows++;
		line = get_next_line(fd);
	}
	rows++;
	return (rows);
}

int	init_map(t_map *map, char *line, int fd)
{
	int		length;
	int		j;
	int		i;
	char	*read_line;

	length = ft_strlen(line);
	read_line = malloc(length + 1);
	ft_strlcpy(read_line, line, length);
	i = 0;
	map->rows = count_rows(fd);
	map->map = malloc(sizeof(char *) * map->rows);
	printf("i = %d\n", i);
	length = ft_strlen(read_line);
	printf("length: %d\n", length);
	if (length > map->longest_row)
		map->longest_row = length;
	map->map[i] = malloc(length + 1);
	j = 0;
	while (j < length)
	{
		printf("line: %s j = %d\n", read_line, j);
		map->map[i][j] = read_line[j];
		j++;
	}
	map->map[i][j] = '\0';
	return (1);
}

int	do_shit(t_input *input, char *current_line, int fd)
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
		printf("Map Type Retrieved\n");
		init_map(&input->map, current_line, fd);
	}
	else if (element_type != CEILING && element_type != FLOOR)
	{
		printf("Wall Type Retrieved\n");
		ceiling_floor_branch(input, str_1, element_type);
	}
	else // Is ceiling or
	{
		printf("Floor Type Retrieved\n");
		ceiling_floor_branch(input, str_1, element_type);
	}
	//free(str_1);
	return (0);
}


t_input	init_cub_file(char *file_name)
{
	int		fd;
	char	*current_line;
	t_input input;

	ft_memset(&input, 0, sizeof(t_input));
	ft_memset(&input.map, 0, sizeof(t_map));
	fd = open_cub_file(file_name);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		// Skip over any blank lines
		while (current_line[0] == '\n')
			current_line = get_next_line(fd);
		// Do things if the line isn't blank
		printf("Current Line:%s\n", current_line);
		do_shit(&input, current_line, fd);
		current_line = get_next_line(fd);
	}
	close(fd);
	return (input);
}
