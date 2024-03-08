/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:21:16 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:21:17 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>
# include "structs.h"

// maths.c
void	normalize_angle(float *ray_angle);
float	distance_between_points(float x1, float y1, float x2, float y2);

#endif
