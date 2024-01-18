#include <fcntl.h>

#include "map.h"
#include "cub3d.h"

bool	is_white_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

int	find_first_char(char *current_line)
{
	int i = 0;
	while (current_line[i] != '\0' && is_white_space(current_line[i]))
		i++;
	if (current_line[i] == '\0')
		return (-1);
	printf("first char found: %s\n", current_line);
	return (i);
}

// assign things here maybe
int	element_found_is(int *i, char *current_line)
{ 
	if (current_line[*i] == 'C' && is_white_space(current_line[*i + 1]))
		return (1);
	else if (current_line[*i] == 'F' && is_white_space(current_line[*i + 1]))
		return (2);
	else if (current_line[*i] == 'N' && current_line[*i + 1] == 'O' && is_white_space(current_line[*i + 2]))
		return (3);
	else if (current_line[*i] == 'S' && current_line[*i + 1] == 'O' && is_white_space(current_line[*i + 2]))
		return (4);
	else if (current_line[*i] == 'E' && current_line[*i + 1] == 'A' && is_white_space(current_line[*i + 2]))
		return (5);
	else if (current_line[*i] == 'W' && current_line[*i + 1] == 'E' && is_white_space(current_line[*i + 2]))
		return (6);
	else
		return (-1);
}

int	get_elements(int *fd, char *current_line, int *elements_found
{
	int	first_char_index;

	if (*elements_found >= 6)
		return (-1);
	while (current_line != '\0' && current_line[0] != '\n')
	{
		first_char_index = find_first_char(current_line);
		if (first_char_index == -1)
			return -1;
		
		// if char is C or F or NO or SO or EA or WE do function for element
		// else nope
	}
}



bool	init_texture_and_map(char *file_name);
{
	int		fd;
	char	*current_line;
	int		elements_found;

	elements_found = 0;
	fd = open(file_name, O_RDONLY);
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
