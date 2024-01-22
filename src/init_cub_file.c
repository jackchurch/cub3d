#include <fcntl.h>

#include "../inc/map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"

char	*isolate_element_path(char *current_line, int *i)
{
	char	*head_removed;
	char	*element_path;

	find_first_char(current_line, i);
	if (*i == -1)
		return ("error");
	head_removed = ft_substr(current_line, *i, ft_strlen(current_line));
	element_path = remove_tail_whitespace(head_removed);
	free(head_removed);
	return (element_path);
}

int	find_element_path(char *current_line, int *i, int element_type)
{
	char	*file_name;

	file_name = isolate_element_path(current_line, i);
	if (*i == -1)
		return (-1);
	if (element_type == CELING || element_type == FLOOR)
		celing_floor_branch();
	else if (element_type == NORTH || element_type == SOUTH
		|| element_type == WEST || element_type == EAST)
	{
		walls_branch();
	}
	else
		return (-1);
	return (1);
}

int	discover_element_type(char *current_line, int *i)
{ 
	if (current_line[*i] == 'C' && is_white_space(current_line[*i + 1]))
		find_element_path(current_line, *i + 1, CELING);
	else if (current_line[*i] == 'F' && is_white_space(current_line[*i + 1]))
		find_element_path(current_line, *i + 1, FLOOR);
	else if (current_line[*i] == 'N' && current_line[*i + 1] == 'O' && is_white_space(current_line[*i + 2]))
		find_element_path(current_line, *i + 2, NORTH);
	else if (current_line[*i] == 'S' && current_line[*i + 1] == 'O' && is_white_space(current_line[*i + 2]))
		find_element_path(current_line, *i + 2, SOUTH);
	else if (current_line[*i] == 'E' && current_line[*i + 1] == 'A' && is_white_space(current_line[*i + 2]))
		find_element_path(current_line, *i + 2, EAST);
	else if (current_line[*i] == 'W' && current_line[*i + 1] == 'E' && is_white_space(current_line[*i + 2]))
		find_element_path(current_line, *i + 2, WEST);
	else
		return (-1);
	return (1);
}

int	get_elements(int *fd, char *current_line, int *elements_found)
{
	int	first_char_index;

	first_char_index = 0;
	if (*elements_found >= 6)
		return (-1);
	while (current_line != '\0' && current_line[0] != '\n')
	{
		find_first_char(current_line, &first_char_index);
		if (first_char_index == -1)
			return -1;
		if (discover_element_type(current_line, &first_char_index) == -1)
			return -1;
	}
}

bool	init_cub_file(char *file_name)
{
	int		fd;
	char	*current_line;
	int		elements_found;

	elements_found = 0;
	fd = open_cub_file(file_name);
	current_line = "temp";
	while (current_line != NULL)
	{
		current_line = get_next_line(fd);
		if (current_line[0] == '\n')
			continue ;
		if (elements_found < 6)
			get_elements(&fd, current_line, &elements_found);
	}
	find_first_line(&fd, current_line);
	get_elements(&fd, current_line);
	current_line = get_next_line(fd);
	return (true);
}
