/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:15:52 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:04 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_only_one(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return (1);
	while (line[++i] != '\n' && line[i] != '\0')
	{
		if (!(is_white_space(line[i]) || line[i] == '1'))
			return (0);
	}
	return (1);
}

char	*remove_tail_whitespace(char *in_string)
{
	int		len;
	char	*temp;

	len = ft_strlen(in_string);
	if (is_white_space(in_string[len - 1]))
	{
		while (is_white_space(in_string[len - 1]))
			len--;
		temp = malloc(len + 1);
		ft_strlcpy(temp, in_string, len);
		return (temp);
	}
	return (in_string);
}

bool	is_xpm_file(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] == 'm' && file_name[len - 2] == 'p'
		&& file_name[len - 3] == 'x' && file_name[len - 4] == '.')
		return (true);
	else
		return (false);
}

int	open_cub_file(char *file_name)
{
	int	fd;

	if (file_name == NULL)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1 || !fd)
		return (-1);
	return (fd);
}
