/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:21:12 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:21:13 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "cub3d.h"
# include "constance.h"
# include "draw.h"

void	render_map(t_game *game);
char	map_content_at(t_game *game, float x, float y);
void	tile_rect_init(t_rectangle *map_tile_rect, const t_tile tile);
bool	is_inside_map(t_game *game, float x, float y);

#endif
