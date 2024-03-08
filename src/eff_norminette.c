/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eff_norminette.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:41:49 by rkabzins          #+#    #+#             */
/*   Updated: 2024/03/08 13:41:51 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	color_range(int *rgb)
{
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0
		|| rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255)
		return (-1);
	return (0);
}

void	eff_norm(t_input *input)
{
	ft_memset(input, 0, sizeof(t_input));
	ft_memset(&input->map, 0, sizeof(t_map));
}

int	seriously_hate_norm(char **values)
{
	char	*temp;

	if (!*values)
		return (-1);
	temp = *values;
	*values = ft_strtrim(temp, " 	");
	free(temp);
	if (any_invalid_chars(*values))
		return (-1);
	return (1);
}
