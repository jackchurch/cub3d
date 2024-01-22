#include <fcntl.h>

#include "../inc/map.h"
#include "cub_file.h"
#include "constance.h"
#include "cub3d.h"


void	celing_floor_branch(char *current_line, int element_type)
{
	char	temp[9];
	int		i;
	bool	expect_comma;
	int		comma_number;
	int		t;

	i = 0;
	t = 0;
	expect = false;
	while (*current_line != '\0')
	{
		if (ft_isdigit(current_line[i]))
		{
			temp[t] = current_line[i];
			t++;
			expect_comma = true;
			continue ;
		}
		else if (is_white_space(current_line[i]))
		{
			i++;
			continue ;
			next_must_be_;
		}
	}

}