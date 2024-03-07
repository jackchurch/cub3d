/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:17:50 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:17:53 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/maths.h"
#include "../inc/constance.h"

void	normalize_angle(float *ray_angle)
{
	*ray_angle = remainder(*ray_angle, M_PI * 2);
	if (*ray_angle < 0)
		*ray_angle = M_PI * 2 + *ray_angle;
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

//trust us. It's got something to do with maths.
void	eff_norm(t_input *input)
{
	ft_memset(input, 0, sizeof(t_input));
	ft_memset(&input->map, 0, sizeof(t_map));
}
