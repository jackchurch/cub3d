#include <fcntl.h>

#include "../inc/map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"



/*
Return element type only if element has a space or tab after the last valid char.
ie C345,654,344 will fail.
C   645,421,334 will pass
*/
int	discover_element_type(char *current_line)
{ 
	int	j;
	int	*i;

	j = 0;
	i = &j;
	if (current_line[*i] == 'C' && is_white_space(current_line[*i + 1]))
		return (CELING);
	else if (current_line[*i] == 'F' && is_white_space(current_line[*i + 1]))
		return (FLOOR);
	else if (current_line[*i] == 'N' && current_line[*i + 1] == 'O'	&& is_white_space(current_line[*i + 2]))
		return (NORTH);
	else if (current_line[*i] == 'S' && current_line[*i + 1] == 'O' && is_white_space(current_line[*i + 2]))
		return (SOUTH);
	else if (current_line[*i] == 'E' && current_line[*i + 1] == 'A' && is_white_space(current_line[*i + 2]))
		return (EAST);
	else if (current_line[*i] == 'W' && current_line[*i + 1] == 'E' && is_white_space(current_line[*i + 2]))
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



int	do_shit(char *current_line)
{
	char	*str_1;
	int		element_type;

	// On this line, remove leading and tailing spaces and tabs (this will need not happen for the map part)
	str_1 = ft_strtrim(current_line, " 	");
	// Set element type and error if element type identifyer is invalid. 
	element_type = discover_element_type(str_1);
	if (element_type == -1)
		return (-1);
	// If a wall (shorter to use not celing and not floor than if NO and SO and WE and EA)
	if (element_type != CELING && element_type != FLOOR)
		celing_floor_branch(str_1, element_type);
	else // Is celing or
		celing_floor_branch(str_1, element_type);
	free(str_1);
	return (0);
}

bool	init_cub_file(char *file_name)
{
	int		fd;
	char	*current_line;

	fd = open_cub_file(file_name);
	current_line = "temp";
	while (current_line != NULL)
	{
		current_line = get_next_line(fd);
		// Skip over any blank lines
		if (current_line[0] == '\n')
			continue ;
		// Do things if the line isn't blank
		do_shit(current_line);
	}

	return (true);
}
