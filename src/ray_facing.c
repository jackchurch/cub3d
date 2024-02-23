/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_facing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:18:16 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:18:18 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/maths.h"
#include "../inc/ray.h"

int	is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < M_PI);
}

int	is_ray_facing_up(float angle)
{
	return (!is_ray_facing_down(angle));
}

int	is_ray_facing_right(float angle)
{
	return (angle < (M_PI / 2) || angle > (M_PI * 1.5));
}

int	is_ray_facing_left(float angle)
{
	return (!is_ray_facing_right(angle));
}
