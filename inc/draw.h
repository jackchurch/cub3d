/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:20:59 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:21:00 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "cub3d.h"

void	draw_rect(t_game *game, t_rectangle *rect);
void	draw_line(t_game *game, const t_line *line);
void	draw_walls(t_game *game, t_image *wall, int dir);
int		find_texture_pixel(t_game *game, int dir, int x, int y);

#endif
