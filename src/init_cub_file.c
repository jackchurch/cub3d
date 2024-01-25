#include <fcntl.h>

#include "../inc/map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"



int	discover_element_type(char *current_line)
{ 
	int	j;
	int	*i;

	j = 0;
	*i = &j;
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

	str_1 = ft_strtrim(current_line, " 	");
	element_type = discover_element_type(str_1);
	if (element_type == -1)
		return (-1);
	if (element_type != CELING && element_type != FLOOR)
		celing_floor_branch(str_1, element_type);
	else
		celing_floor_branch(str_1, element_type);
	free(str_1);
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
		if (current_line[0] == '\n')
			continue ;
		do_shit(current_line);
	}
	find_first_line(&fd, current_line);
	get_elements(&fd, current_line);
	current_line = get_next_line(fd);
	return (true);
}
