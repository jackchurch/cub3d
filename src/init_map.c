#include <fcntl.h>

#include "../inc/map.h"
#include "constance.h"
#include "cub3d.h"

bool	is_white_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

void	find_first_char(char *current_line, int *i)
{
	int i = 0;
	while (is_white_space(current_line[*i]))
		*i++;
	if (current_line[*i] == '\0')
		*i = -1;
}

char	*remove_tail_whitespace(char *in_string)
{
	int		len;
	char	*temp;

	len = ft_strlen(in_string);
	if (is_white_space(in_string[len - 1]))
	{
		while (is_white_space(in_string[len - 1]))
		{
			len--;
		}
		ft_strlcpy(temp, in_string, ft_strlen(in_string) - len);
		return (temp);
	}
	return (in_string);
}

bool	is_xpm_file(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] == 'm' && file_name[len - 2] == 'p' && 
		file_name[len - 3] == 'x' && file_name[len - 4] == '.')
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

char	*isolate_element_path(char *current_line, int *i)
{
	char	*head_removed;
	char	*element_path;

	find_first_char(current_line, i);
	if (*i == -1)
		return (-1);
	head_removed = ft_substr(current_line, *i, ft_strlen(current_line));
	element_path = remove_tail_whitespace(head_removed);
	free(head_removed);
}

int	find_element_path(char *current_line, int *i, int element_type)
{
	char	*file_name;

	file_name = isolate_element_path(current_line, i);
	if (element_type == CELING || element_type == FLOOR)
	{
		// TODO set_celing_or_floor(element_type)
		return (1);
	}
	else if (is_xpm_file(file_name) == true)
	{
		// TODO check_xpm_file(file_name)

	}
	else
		return (-1);
	

	
}

// assign things here maybe
int	discover_element_type(char *current_line, int *i)
{ 
	int	element_type;

	if (current_line[*i] == 'C' && is_white_space(current_line[*i + 1]))
		element_type = CELING;
	else if (current_line[*i] == 'F' && is_white_space(current_line[*i + 1]))
		element_type = FLOOR;
	else if (current_line[*i] == 'N' && current_line[*i + 1] == 'O' && is_white_space(current_line[*i + 2]))
		element_type = NORTH;
	else if (current_line[*i] == 'S' && current_line[*i + 1] == 'O' && is_white_space(current_line[*i + 2]))
		element_type = SOUTH;
	else if (current_line[*i] == 'E' && current_line[*i + 1] == 'A' && is_white_space(current_line[*i + 2]))
		element_type = EAST;
	else if (current_line[*i] == 'W' && current_line[*i + 1] == 'E' && is_white_space(current_line[*i + 2]))
		element_type = WEST;
	else
		return (-1);
	*i++;
	if (element_type != CELING && element_type != FLOOR)
		*i++;
	find_element_path(current_line, i, element_type);
	return (element_type);
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
		discover_element_type(current_line, &first_char_index);

		
		// if char is C or F or NO or SO or EA or WE do function for element
		// else nope
	}
}

int	open_cub_file(char *file_name)
{
	int	fd;

	if (file_name == NULL)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1 || fd == NULL)
		return (-1);
	return (fd);
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
