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
